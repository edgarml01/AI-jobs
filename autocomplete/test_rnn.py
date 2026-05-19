"""
SCRIPT DE TESTING PARA MODELO DE AUTOCOMPLETADO RNN
Carga el modelo guardado y realiza pruebas de predicción
"""

import numpy as np
from tensorflow.keras.models import load_model
from tensorflow.keras.preprocessing.sequence import pad_sequences

# =========================================================
# CARGAR CORPUS PARA OBTENER VOCABULARIO
# =========================================================

with open("corpus.c", "r", encoding="utf-8") as f:
    text = f.read()

chars = sorted(list(set(text)))
char_to_idx = {c: i for i, c in enumerate(chars)}
idx_to_char = {i: c for i, c in enumerate(chars)}
vocab_size = len(chars)
sequence_length = 64

print("✓ Corpus cargado")
print(f"✓ Vocabulario: {vocab_size} caracteres")

# =========================================================
# CARGAR MODELO GUARDADO
# =========================================================

print("\n📦 Cargando modelo entrenado...")
try:
    modelo = load_model("modelo_autocompletado_rnn.h5")
    print("✓ Modelo cargado exitosamente")
    modelo.summary()
except FileNotFoundError:
    print("❌ Error: No se encontró el modelo 'modelo_autocompletado_rnn.h5'")
    exit(1)

# =========================================================
# FUNCIÓN DE GENERACIÓN CON MODELO CARGADO
# =========================================================

def generar_codigo_test(seed_text, num_chars=200):
    """Genera código usando el modelo guardado"""
    generated = seed_text

    for _ in range(num_chars):
        sequence = [char_to_idx.get(c, 0) for c in generated[-sequence_length:]]
        sequence = pad_sequences([sequence], maxlen=sequence_length)
        prediction = modelo.predict(sequence, verbose=0)
        predicted_index = np.argmax(prediction)
        predicted_char = idx_to_char[predicted_index]
        generated += predicted_char

    return generated

# =========================================================
# EJECUTAR PRUEBAS
# =========================================================

print("\n" + "="*60)
print("PRUEBAS DE GENERACIÓN DE CÓDIGO")
print("="*60)

pruebas = [
    ("// Func", 20),
    ("for ",20),
    ("if (", (20))
    
]

for i, (seed, num_chars) in enumerate(pruebas, 1):
    print(f"\n[Test {i}] Seed: '{seed}'")
    print("-" * 60)
    resultado = generar_codigo_test(seed, num_chars)
    print(resultado)
    print()

print("="*60)
print("✓ TODAS LAS PRUEBAS COMPLETADAS")
print("="*60)