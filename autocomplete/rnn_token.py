# =========================================================
# MODELO DE AUTOCOMPLETADO CON RNN - TOKENIZACIÓN A NIVEL
# DE TOKEN (Word/Token-Level) EN LUGAR DE CARÁCTER
# TensorFlow / Keras
# =========================================================
# Ventajas sobre character-level:
#   - Cada token es una unidad semántica completa (keyword,
#     identificador, operador, literal numérico, etc.)
#   - Con sequence_length=64 tokens, el modelo recuerda ~64
#     palabras de contexto (vs 64 caracteres = ~2 líneas)
#   - Menos pasos de inferencia para generar una función
#     completa (1 paso = 1 token, no 1 carácter)
# =========================================================

import re
import json
import pickle
import numpy as np
import tensorflow as tf
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import SimpleRNN, Dense, Embedding
from tensorflow.keras.preprocessing.sequence import pad_sequences
from tensorflow.keras.utils import to_categorical

# =========================================================
# 1. CARGAR EL CORPUS
# =========================================================

with open("corpus.c", "r", encoding="utf-8") as f:
    text = f.read()

print("Longitud del corpus:", len(text), "caracteres")

# =========================================================
# 2. TOKENIZADOR LÉXICO PARA CÓDIGO C
# =========================================================
# En lugar de tratar cada carácter como un token,
# dividimos el código fuente en unidades léxicas reales:
#   - Palabras clave de C (int, void, return, if, for...)
#   - Identificadores (nombres de funciones y variables)
#   - Operadores simples y compuestos (==, !=, >=, +=, ++)
#   - Literales numéricos (42, 0, 100)
#   - Puntuación ({, }, (, ), ;, ,)
#   - Comentarios de línea (// ...)
#   - Saltos de línea (\n) e indentación (    )
# =========================================================

# Patrón regex que captura los tokens de C en orden de prioridad
TOKEN_PATTERN = re.compile(
    r'//[^\n]*'         # Comentarios de línea completos
    r'|"[^"]*"'         # Cadenas entre comillas dobles
    r"|'[^']*'"         # Caracteres entre comillas simples
    r'|\d+'             # Literales numéricos enteros
    r'|[a-zA-Z_]\w*'    # Identificadores y palabras clave
    r'|==|!=|>=|<=|&&|\|\||<<|>>'  # Operadores compuestos de 2 caracteres
    r'|\+\+|--|->|\+=|-=|\*=|/='   # Más operadores compuestos
    r'|[+\-*/%=<>!&|^~]'          # Operadores simples de 1 carácter
    r'|[{}()\[\];,.]'   # Puntuación y delimitadores
    r'|\n'              # Saltos de línea (preservar estructura)
    r'|    '            # Indentación de 4 espacios (como un token)
    r'| '               # Espacios simples
)


def tokenizar_codigo_c(codigo_fuente):
    """
    Divide el código fuente C en una lista de tokens léxicos.

    Args:
        codigo_fuente (str): Código C como cadena de texto.

    Returns:
        list[str]: Lista ordenada de tokens.
    """
    return TOKEN_PATTERN.findall(codigo_fuente)


# Tokenizar todo el corpus
tokens = tokenizar_codigo_c(text)

print(f"Total de tokens generados: {len(tokens)}")

# =========================================================
# 3. CONSTRUIR VOCABULARIO DE TOKENS
# =========================================================

# Obtener tokens únicos y ordenarlos para reproducibilidad
unique_tokens = sorted(list(set(tokens)))

# Mapeos bidireccionales token <-> índice
token_to_idx = {t: i for i, t in enumerate(unique_tokens)}
idx_to_token = {i: t for i, t in enumerate(unique_tokens)}

vocab_size = len(unique_tokens)

print(f"Tamaño del vocabulario (tokens únicos): {vocab_size}")
print(f"Ratio de compresión: {len(text)} chars -> {len(tokens)} tokens "
      f"({len(text)/len(tokens):.1f}x)")

# Guardar el vocabulario y tokenizador para uso en el servidor
vocabulario = {
    "token_to_idx": token_to_idx,
    "idx_to_token": {str(k): v for k, v in idx_to_token.items()},
    "vocab_size": vocab_size,
    "unique_tokens": unique_tokens
}

with open("vocabulario_tokens.json", "w", encoding="utf-8") as f:
    json.dump(vocabulario, f, ensure_ascii=False, indent=2)

print("✓ Vocabulario guardado en 'vocabulario_tokens.json'")

# =========================================================
# 4. CREAR SECUENCIAS DE ENTRENAMIENTO
# =========================================================
# Cada secuencia contiene sequence_length tokens consecutivos
# y la etiqueta es el token inmediatamente siguiente.
# Se usa step=2 (stride) para reducir redundancia.
# =========================================================

sequence_length = 64  # 64 tokens de contexto (~64 palabras/símbolos)
step = 2              # Stride para reducir redundancia

X = []
y = []

for i in range(0, len(tokens) - sequence_length, step):
    input_seq = tokens[i:i + sequence_length]
    target_token = tokens[i + sequence_length]

    X.append([token_to_idx[t] for t in input_seq])
    y.append(token_to_idx[target_token])

X = np.array(X)
y = np.array(y)

# One-hot encoding para las salidas
y = to_categorical(y, num_classes=vocab_size)

print(f"\nShape X: {X.shape}")
print(f"Shape y: {y.shape}")
print(f"Secuencias generadas con step={step} (stride)")

# =========================================================
# 5. CREAR EL MODELO RNN VANILLA
# =========================================================
# La capa Embedding ahora tiene input_dim = vocab_size
# (número de tokens únicos, ~cientos) en lugar de 89 chars.
# El output_dim del Embedding se aumenta a 128 para dar
# más espacio de representación a cada token.
# =========================================================

model = Sequential([

    Embedding(
        input_dim=vocab_size,
        output_dim=128,          # Mayor dimensión para tokens semánticos
        input_length=sequence_length
    ),

    SimpleRNN(
        256,                     # Más unidades para capturar patrones de tokens
        activation='tanh'
    ),

    Dense(
        vocab_size,
        activation='softmax'
    )
])

# =========================================================
# 6. COMPILAR
# =========================================================

model.compile(
    loss='categorical_crossentropy',
    optimizer='adam',
    metrics=['accuracy']
)

model.summary()

# =========================================================
# 7. ENTRENAMIENTO
# =========================================================

model.fit(
    X,
    y,
    epochs=60,
    batch_size=64,
    verbose=1
)

# =========================================================
# 8. GUARDAR EL MODELO
# =========================================================

model.save("modelo_token_rnn.h5")

print("\n✓ Modelo token-level guardado en 'modelo_token_rnn.h5'")

# =========================================================
# 9. FUNCIÓN DE MUESTREO CON TEMPERATURA
# =========================================================

def sample_with_temperature(preds, temperature=1.0):
    """
    Muestrea un índice de un vector de probabilidades
    aplicando temperatura para controlar la aleatoriedad.

    Args:
        preds (np.array): Vector de probabilidades (salida softmax).
        temperature (float): Factor de temperatura.

    Returns:
        int: Índice muestreado del vocabulario.
    """
    preds = np.asarray(preds).astype("float64")

    if temperature <= 0:
        return np.argmax(preds)

    log_preds = np.log(preds + 1e-8) / temperature
    exp_preds = np.exp(log_preds)
    probas = exp_preds / np.sum(exp_preds)

    return np.random.multinomial(1, probas, 1).argmax()

# =========================================================
# 10. FUNCIÓN DE GENERACIÓN DE TEXTO (TOKEN-LEVEL)
# =========================================================

def generar_codigo(seed_text, num_tokens=50, temperature=0.7):
    """
    Genera código a partir de un texto semilla usando el modelo
    entrenado con tokenización a nivel de token.

    Args:
        seed_text (str): Texto semilla para iniciar la generación.
        num_tokens (int): Número de tokens a generar.
        temperature (float): Temperatura para el muestreo.

    Returns:
        str: Texto generado completo (semilla + generación).
    """
    # Tokenizar la semilla con el mismo tokenizador
    seed_tokens = tokenizar_codigo_c(seed_text)

    generated_tokens = list(seed_tokens)

    for _ in range(num_tokens):

        # Tomar los últimos sequence_length tokens
        context = generated_tokens[-sequence_length:]

        # Convertir a índices (usar 0 para tokens desconocidos)
        sequence = [token_to_idx.get(t, 0) for t in context]

        # Padding si la secuencia es más corta
        sequence = pad_sequences(
            [sequence],
            maxlen=sequence_length
        )

        # Predicción
        prediction = model.predict(sequence, verbose=0)[0]

        # Muestreo con temperatura
        predicted_index = sample_with_temperature(prediction, temperature)
        predicted_token = idx_to_token[predicted_index]

        generated_tokens.append(predicted_token)

    # Reconstruir el texto uniendo los tokens
    return "".join(generated_tokens)

# =========================================================
# 11. PRUEBAS DE GENERACIÓN
# =========================================================

if __name__ == "__main__":
    print("\n" + "="*60)
    print("PRUEBAS DE GENERACIÓN (TOKEN-LEVEL)")
    print("="*60)

    seeds = [
        ("// Función:", 30),
        ("int ", 25),
        ("for (", 30),
        ("if (", 20),
        ("return ", 10),
    ]

    for seed, num in seeds:
        print(f"\n🔹 Seed: '{seed}' ({num} tokens)")
        print("-" * 60)
        resultado = generar_codigo(seed, num, temperature=0.7)
        print(resultado)
        print()

    print("="*60)
    print("✓ PRUEBAS COMPLETADAS")
    print("="*60)
