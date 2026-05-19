# =========================================================
# MODELO BÁSICO DE AUTOCOMPLETADO DE CÓDIGO CON RNN VANILLA
# TensorFlow / Keras
# =========================================================
# Optimizaciones aplicadas:
#   - Entrenamiento con 150 epochs (rango 100-200)
#   - Generación de texto con temperatura (default 0.7)
#   - Contexto de entrada ampliado a 100 caracteres
#   - Reducción de redundancia con stride (step=3)
# =========================================================

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

print("Longitud del corpus:", len(text))

# =========================================================
# 2. TOKENIZACIÓN A NIVEL CARÁCTER
# =========================================================

chars = sorted(list(set(text)))

char_to_idx = {c: i for i, c in enumerate(chars)}
idx_to_char = {i: c for i, c in enumerate(chars)}

vocab_size = len(chars)

print("Tamaño del vocabulario:", vocab_size)

# =========================================================
# 3. CREAR SECUENCIAS DE ENTRENAMIENTO
# =========================================================
# Se usa sequence_length=100 para mayor contexto y
# step=3 (stride) para reducir redundancia en el dataset.
# =========================================================

sequence_length = 64  # Aumentado de 40 a 100 para mayor contexto
step = 3               # Stride para reducir redundancia del dataset

X = []
y = []

# El stride (step) reduce el número de secuencias generadas,
# avanzando de 3 en 3 en lugar de 1 en 1.
for i in range(0, len(text) - sequence_length, step):

    input_seq = text[i:i + sequence_length]
    target_char = text[i + sequence_length]

    X.append([char_to_idx[c] for c in input_seq])
    y.append(char_to_idx[target_char])

X = np.array(X)
y = np.array(y)

# One-hot para las salidas
y = to_categorical(y, num_classes=vocab_size)

print("Shape X:", X.shape)
print("Shape y:", y.shape)
print(f"Secuencias generadas con step={step} (stride)")

# =========================================================
# 4. CREAR EL MODELO RNN VANILLA
# =========================================================

model = Sequential([
    
    Embedding(
        input_dim=vocab_size,
        output_dim=64,
        input_length=sequence_length
    ),

    SimpleRNN(
        128,
        activation='tanh'
    ),

    Dense(
        vocab_size,
        activation='softmax'
    )
])

# =========================================================
# 5. COMPILAR
# =========================================================

model.compile(
    loss='categorical_crossentropy',
    optimizer='adam',
    metrics=['accuracy']
)

model.summary()

# =========================================================
# 6. ENTRENAMIENTO
# =========================================================
# Entrenamiento con 150 epochs (rango recomendado: 100-200).
# Se mantiene batch_size=64 y se muestran métricas de
# pérdida (loss) y accuracy durante el entrenamiento.
# =========================================================

model.fit(
    X,
    y,
    epochs=150,        # Incrementado de 20 a 150 (rango 100-200)
    batch_size=64,
    verbose=1          # Mostrar métricas de pérdida y accuracy por epoch
)

# =========================================================
# 7. GUARDAR EL MODELO
# =========================================================

model.save("modelo_autocompletado_rnn.h5")

print("Modelo guardado.")

# =========================================================
# 8. FUNCIÓN DE MUESTREO CON TEMPERATURA
# =========================================================
# La temperatura controla la aleatoriedad de la generación:
#   - Temperatura baja (0.2): texto más conservador y repetitivo
#   - Temperatura media (0.7): balance entre creatividad y coherencia
#   - Temperatura alta (1.5): texto más creativo pero menos coherente
# =========================================================

def sample_with_temperature(preds, temperature=1.0):
    """
    Muestrea un índice de un vector de probabilidades
    aplicando temperatura para controlar la aleatoriedad.

    Args:
        preds (np.array): Vector de probabilidades (salida softmax).
        temperature (float): Factor de temperatura.
            - < 1.0: distribución más concentrada (menos aleatoriedad)
            - = 1.0: distribución original
            - > 1.0: distribución más uniforme (más aleatoriedad)

    Returns:
        int: Índice muestreado del vocabulario.
    """
    preds = np.asarray(preds).astype("float64")

    # Aplicar temperatura: re-escalar los log-probabilities
    log_preds = np.log(preds + 1e-8) / temperature
    exp_preds = np.exp(log_preds)

    # Normalizar para obtener una distribución de probabilidad válida
    probas = exp_preds / np.sum(exp_preds)

    # Muestreo probabilístico (en lugar de argmax determinístico)
    return np.random.multinomial(1, probas, 1).argmax()

# =========================================================
# 9. FUNCIÓN DE GENERACIÓN DE TEXTO
# =========================================================
# Ahora usa sampling con temperatura en lugar de np.argmax().
# La temperatura por defecto es 0.7 para un buen balance.
# =========================================================

def generar_codigo(seed_text, num_chars=200, temperature=0.7):
    """
    Genera código a partir de un texto semilla usando el modelo entrenado.

    Args:
        seed_text (str): Texto semilla para iniciar la generación.
        num_chars (int): Número de caracteres a generar.
        temperature (float): Temperatura para el muestreo (default: 0.7).

    Returns:
        str: Texto generado completo (semilla + generación).
    """
    generated = seed_text

    for _ in range(num_chars):

        # Convertir a índices (últimos sequence_length caracteres)
        sequence = [char_to_idx.get(c, 0) for c in generated[-sequence_length:]]

        # Padding si la secuencia es más corta que sequence_length
        sequence = pad_sequences(
            [sequence],
            maxlen=sequence_length
        )

        # Predicción
        prediction = model.predict(sequence, verbose=0)[0]

        # Muestreo con temperatura (reemplaza np.argmax)
        predicted_index = sample_with_temperature(prediction, temperature)

        predicted_char = idx_to_char[predicted_index]

        generated += predicted_char

    return generated

# =========================================================
# 10. FUNCIÓN PARA TESTEAR CON MODELO GUARDADO
# =========================================================

def cargar_y_testear_modelo(modelo_path="modelo_autocompletado_rnn.h5"):
    """
    Carga el modelo guardado y prepara funciones para testeo.
    
    Args:
        modelo_path (str): Ruta al modelo guardado
    
    Returns:
        tuple: (modelo cargado, función de generación)
    """
    from tensorflow.keras.models import load_model
    
    # Cargar el modelo entrenado
    modelo_cargado = load_model(modelo_path)
    print(f"✓ Modelo cargado desde: {modelo_path}")
    
    def generar_codigo_cargado(seed_text, num_chars=200, temperature=0.7):
        """Genera texto usando el modelo cargado con temperatura"""
        generated = seed_text

        for _ in range(num_chars):
            sequence = [char_to_idx.get(c, 0) for c in generated[-sequence_length:]]
            sequence = pad_sequences([sequence], maxlen=sequence_length)
            prediction = modelo_cargado.predict(sequence, verbose=0)[0]

            # Muestreo con temperatura (reemplaza np.argmax)
            predicted_index = sample_with_temperature(prediction, temperature)

            predicted_char = idx_to_char[predicted_index]
            generated += predicted_char

        return generated
    
    return modelo_cargado, generar_codigo_cargado


def testear_modelo_completo(modelo_path="modelo_autocompletado_rnn.h5"):
    """
    Realiza pruebas completas del modelo guardado.
    
    Args:
        modelo_path (str): Ruta al modelo guardado
    """
    print("\n" + "="*50)
    print("INICIANDO PRUEBAS DEL MODELO")
    print("="*50)
    
    # Cargar modelo
    modelo_test, generar_func = cargar_y_testear_modelo(modelo_path)
    
    # Ver resumen del modelo
    print("\n📋 RESUMEN DEL MODELO:")
    modelo_test.summary()
    
    # Pruebas de generación con distintas temperaturas
    pruebas = [
        ("int ", 100),
        ("void ", 100),
        ("if (", 80),
        ("for (", 100),
        ("return ", 60),
    ]
    
    temperaturas = [0.5, 0.7, 1.0]  # Probar con distintas temperaturas
    
    print("\n" + "="*50)
    print("PRUEBAS DE GENERACIÓN DE CÓDIGO")
    print("="*50)
    
    for seed, num_chars in pruebas:
        print(f"\n🔹 Seed: '{seed}'")
        for temp in temperaturas:
            print(f"\n   🌡️  Temperatura: {temp}")
            print(f"   Generando {num_chars} caracteres...")
            resultado = generar_func(seed, num_chars, temperature=temp)
            print(f"   Resultado:\n{resultado}\n")
    
    print("="*50)
    print("✓ PRUEBAS COMPLETADAS")
    print("="*50)


# =========================================================
# 11. PROBAR EL MODELO
# =========================================================

# Ejecutar si es el archivo principal
if __name__ == "__main__":
    # Usar el modelo entrenado directamente con temperatura 0.7
    seed = "int math_"
    resultado = generar_codigo(seed, 300, temperature=0.7)

    print("\n===== TEXTO GENERADO (Modelo en Memoria, temp=0.7) =====\n")
    print(resultado)

    # Comparación con temperatura baja (más determinístico)
    resultado_low = generar_codigo(seed, 300, temperature=0.3)
    print("\n===== TEXTO GENERADO (Modelo en Memoria, temp=0.3) =====\n")
    print(resultado_low)

    # Descomenta la siguiente línea para probar con el modelo guardado
    # testear_modelo_completo()