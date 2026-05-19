"""
SERVIDOR FLASK UNIVERSAL (VSCODE & ZED / OPENAI API COMPATIBLE)
==================================================================
Este script expone el modelo de red neuronal recurrente (RNN) entrenado
a través de una API REST dual:
  1. Endpoint nativo (/predict) para la extensión de VSCode.
  2. Endpoints compatibles con OpenAI (/v1/chat/completions, /v1/completions, /v1/models)
     para integrarse nativamente con el editor ZED o cualquier cliente OpenAI.

Requisitos:
    - Flask (instalado en el entorno virtual)
    - TensorFlow / Keras
    - Archivo 'corpus.c' (para reconstruir el vocabulario)
    - Archivo 'modelo_autocompletado_rnn.h5' (modelo entrenado)

==================================================================
CONFIGURACIÓN PARA ZED (settings.json):
==================================================================
Añade el siguiente bloque a tu archivo de configuración en Zed (Cmd + ,):

{
  "language_models": {
    "openai": {
      "version": "1",
      "api_url": "http://127.0.0.1:5000/v1",
      "available_models": [
        {
          "name": "rnn-autocomplete",
          "display_name": "C Autocomplete (RNN)",
          "max_tokens": 500
        }
      ]
    }
  },
  "assistant": {
    "default_model": {
      "provider": "openai",
      "model": "rnn-autocomplete"
    }
  }
}
==================================================================
"""

import os
import time
import json
import numpy as np
import tensorflow as tf
from flask import Flask, request, jsonify, Response
from tensorflow.keras.models import load_model
from tensorflow.keras.preprocessing.sequence import pad_sequences

# =========================================================
# 1. CONFIGURACIÓN E INICIALIZACIÓN DE FLASK
# =========================================================

app = Flask(__name__)

# Configuración de longitud de secuencia (debe coincidir con rnn.py)
SEQUENCE_LENGTH = 64
CORPUS_PATH = "corpus.c"
MODEL_PATH = "modelo_autocompletado_rnn.h5"

# Variables globales para almacenar el vocabulario y el modelo
char_to_idx = {}
idx_to_char = {}
vocab_size = 0
modelo = None

# =========================================================
# 2. CARGA DE VOCABULARIO Y MODELO
# =========================================================

def inicializar_servidor():
    global char_to_idx, idx_to_char, vocab_size, modelo

    print("\n" + "="*60)
    print("INICIALIZANDO SERVIDOR UNIVERSAL DE AUTOCOMPLETADO (RNN)")
    print("Soporte para VSCode (/predict) y ZED / OpenAI API (/v1)")
    print("="*60)

    # 1. Cargar corpus y construir vocabulario
    if not os.path.exists(CORPUS_PATH):
        print(f"❌ Error: No se encontró el archivo de corpus '{CORPUS_PATH}'.")
        exit(1)

    with open(CORPUS_PATH, "r", encoding="utf-8") as f:
        text = f.read()

    chars = sorted(list(set(text)))
    char_to_idx = {c: i for i, c in enumerate(chars)}
    idx_to_char = {i: c for i, c in enumerate(chars)}
    vocab_size = len(chars)

    print(f"✓ Corpus cargado exitosamente ({len(text)} caracteres).")
    print(f"✓ Vocabulario construido: {vocab_size} caracteres distintos.")

    # 2. Cargar modelo Keras
    if not os.path.exists(MODEL_PATH):
        print(f"❌ Error: No se encontró el modelo entrenado '{MODEL_PATH}'.")
        print("Asegúrate de haber ejecutado 'rnn.py' previamente para entrenarlo.")
        exit(1)

    print(f"\n📦 Cargando modelo desde '{MODEL_PATH}'...")
    try:
        modelo = load_model(MODEL_PATH)
        print("✓ Modelo cargado correctamente en memoria.")
    except Exception as e:
        print(f"❌ Error al cargar el modelo: {e}")
        exit(1)

    print("="*60)
    print("🚀 Servidor listo en http://127.0.0.1:5000")
    print("   - VSCode Endpoint: http://127.0.0.1:5000/predict")
    print("   - Zed/OpenAI API:  http://127.0.0.1:5000/v1")
    print("="*60 + "\n")

# =========================================================
# 3. FUNCIONES DE PREDICCIÓN Y MUESTREO
# =========================================================

def sample_with_temperature(preds, temperature=0.7):
    """Muestrea un índice a partir de un vector de probabilidades con temperatura."""
    preds = np.asarray(preds).astype("float64")
    
    # Evitar log(0) o división por cero
    if temperature <= 0:
        return np.argmax(preds)

    log_preds = np.log(preds + 1e-8) / temperature
    exp_preds = np.exp(log_preds)
    probas = exp_preds / np.sum(exp_preds)
    
    return np.random.multinomial(1, probas, 1).argmax()


def generar_autocompletado(prompt, num_chars=50, temperature=0.7):
    """Genera la predicción completa de caracteres siguientes (modo sin streaming)."""
    if not prompt:
        prompt = "int "

    generated_completion = ""
    current_text = prompt

    for _ in range(num_chars):
        sequence = [char_to_idx.get(c, 0) for c in current_text[-SEQUENCE_LENGTH:]]
        sequence = pad_sequences([sequence], maxlen=SEQUENCE_LENGTH)

        prediction = modelo.predict(sequence, verbose=0)[0]
        predicted_index = sample_with_temperature(prediction, temperature)
        predicted_char = idx_to_char[predicted_index]

        generated_completion += predicted_char
        current_text += predicted_char

    return generated_completion


def generar_stream_openai(prompt, num_chars=50, temperature=0.7, is_chat=True):
    """Generador para Server-Sent Events (SSE) compatible con OpenAI stream: true para Zed."""
    if not prompt:
        prompt = "int "

    current_text = prompt
    cmpl_id = f"chatcmpl-rnn-{int(time.time())}" if is_chat else f"cmpl-rnn-{int(time.time())}"
    created_time = int(time.time())
    
    for _ in range(num_chars):
        sequence = [char_to_idx.get(c, 0) for c in current_text[-SEQUENCE_LENGTH:]]
        sequence = pad_sequences([sequence], maxlen=SEQUENCE_LENGTH)

        prediction = modelo.predict(sequence, verbose=0)[0]
        predicted_index = sample_with_temperature(prediction, temperature)
        predicted_char = idx_to_char[predicted_index]

        current_text += predicted_char

        # Estructura del chunk SSE de OpenAI
        if is_chat:
            chunk = {
                "id": cmpl_id,
                "object": "chat.completion.chunk",
                "created": created_time,
                "model": "rnn-autocomplete",
                "choices": [
                    {
                        "index": 0,
                        "delta": {"content": predicted_char},
                        "finish_reason": None
                    }
                ]
            }
        else:
            chunk = {
                "id": cmpl_id,
                "object": "text_completion",
                "created": created_time,
                "model": "rnn-autocomplete",
                "choices": [
                    {
                        "text": predicted_char,
                        "index": 0,
                        "logprobs": None,
                        "finish_reason": None
                    }
                ]
            }
        
        yield f"data: {json.dumps(chunk)}\n\n"

    # Chunk final indicando finalización (finish_reason)
    if is_chat:
        final_chunk = {
            "id": cmpl_id,
            "object": "chat.completion.chunk",
            "created": created_time,
            "model": "rnn-autocomplete",
            "choices": [
                {
                    "index": 0,
                    "delta": {},
                    "finish_reason": "stop"
                }
            ]
        }
        yield f"data: {json.dumps(final_chunk)}\n\n"
    else:
        final_chunk = {
            "id": cmpl_id,
            "object": "text_completion",
            "created": created_time,
            "model": "rnn-autocomplete",
            "choices": [
                {
                    "text": "",
                    "index": 0,
                    "logprobs": None,
                    "finish_reason": "length"
                }
            ]
        }
        yield f"data: {json.dumps(final_chunk)}\n\n"

    yield "data: [DONE]\n\n"

# =========================================================
# 4. MIDDLEWARE PARA CORS (Cross-Origin Resource Sharing)
# =========================================================

@app.after_request
def add_cors_headers(response):
    """Añade cabeceras CORS para permitir peticiones desde VSCode, Zed y Webviews."""
    response.headers['Access-Control-Allow-Origin'] = '*'
    response.headers['Access-Control-Allow-Methods'] = 'GET, POST, OPTIONS'
    response.headers['Access-Control-Allow-Headers'] = 'Content-Type, Authorization'
    return response

# =========================================================
# 5. ENDPOINTS DE LA API (VSCODE & OPENAI / ZED)
# =========================================================

@app.route('/', methods=['GET'])
def index():
    """Endpoint de estado e información general de la API."""
    return jsonify({
        "status": "online",
        "service": "C Code Autocomplete Universal RNN API",
        "vocab_size": vocab_size,
        "sequence_length": SEQUENCE_LENGTH,
        "endpoints": {
            "vscode_predict": "POST /predict",
            "openai_models": "GET /v1/models",
            "openai_chat": "POST /v1/chat/completions",
            "openai_completions": "POST /v1/completions"
        }
    })

# ---------------------------------------------------------
# ENDPOINT VSCODE (Heredado / Nativo)
# ---------------------------------------------------------
@app.route('/predict', methods=['POST', 'OPTIONS'])
@app.route('/autocomplete', methods=['POST', 'OPTIONS'])
def predict():
    if request.method == 'OPTIONS':
        return jsonify({"status": "ok"}), 200

    try:
        data = request.get_json()
        if not data:
            return jsonify({"error": "No se proporcionó un cuerpo JSON válido"}), 400

        prompt = data.get("prompt", "")
        num_chars = int(data.get("num_chars", 50))
        temperature = float(data.get("temperature", 0.7))

        num_chars = max(1, min(num_chars, 500))
        temperature = max(0.1, min(temperature, 2.0))

        completion = generar_autocompletado(prompt, num_chars, temperature)

        return jsonify({
            "success": True,
            "prompt": prompt,
            "completion": completion,
            "full_text": prompt + completion,
            "parameters": {
                "num_chars": num_chars,
                "temperature": temperature
            }
        })

    except Exception as e:
        print(f"❌ Error en /predict: {e}")
        return jsonify({"error": str(e)}), 500

# ---------------------------------------------------------
# ENDPOINTS OPENAI API COMPATIBLE (Para ZED Editor)
# ---------------------------------------------------------

@app.route('/v1/models', methods=['GET', 'OPTIONS'])
def list_models():
    """Endpoint para que Zed descubra y valide el modelo disponible."""
    if request.method == 'OPTIONS':
        return jsonify({"status": "ok"}), 200

    return jsonify({
        "object": "list",
        "data": [
            {
                "id": "rnn-autocomplete",
                "object": "model",
                "created": int(time.time()),
                "owned_by": "antigravity-rnn",
                "permission": [],
                "root": "rnn-autocomplete",
                "parent": None
            }
        ]
    })


@app.route('/v1/chat/completions', methods=['POST', 'OPTIONS'])
def chat_completions():
    """Endpoint OpenAI para Chat Completions (Usado por el Assistant y Autocomplete de Zed)."""
    if request.method == 'OPTIONS':
        return jsonify({"status": "ok"}), 200

    try:
        data = request.get_json()
        if not data:
            return jsonify({"error": "Cuerpo JSON inválido"}), 400

        # Extraer el prompt de los mensajes enviados por Zed
        messages = data.get("messages", [])
        prompt = ""
        if isinstance(messages, list):
            # Extraer el contenido del último mensaje del usuario o concatenar
            for msg in messages:
                if isinstance(msg, dict) and msg.get("content"):
                    prompt += msg.get("content", "") + "\n"
            prompt = prompt.rstrip("\n")
        elif isinstance(messages, str):
            prompt = messages

        # Configuración de parámetros OpenAI -> RNN
        max_tokens = int(data.get("max_tokens", data.get("max_completion_tokens", 50)))
        temperature = float(data.get("temperature", 0.7))
        stream = data.get("stream", False)

        max_tokens = max(1, min(max_tokens, 500))
        temperature = max(0.1, min(temperature, 2.0))

        # Modo Streaming (SSE) solicitado por Zed
        if stream:
            return Response(
                generar_stream_openai(prompt, max_tokens, temperature, is_chat=True),
                mimetype='text/event-stream'
            )

        # Modo Normal (JSON estático)
        completion = generar_autocompletado(prompt, max_tokens, temperature)
        cmpl_id = f"chatcmpl-rnn-{int(time.time())}"

        return jsonify({
            "id": cmpl_id,
            "object": "chat.completion",
            "created": int(time.time()),
            "model": "rnn-autocomplete",
            "choices": [
                {
                    "index": 0,
                    "message": {
                        "role": "assistant",
                        "content": completion
                    },
                    "finish_reason": "stop"
                }
            ],
            "usage": {
                "prompt_tokens": len(prompt),
                "completion_tokens": len(completion),
                "total_tokens": len(prompt) + len(completion)
            }
        })

    except Exception as e:
        print(f"❌ Error en /v1/chat/completions: {e}")
        return jsonify({"error": str(e)}), 500


@app.route('/v1/completions', methods=['POST', 'OPTIONS'])
def text_completions():
    """Endpoint OpenAI para Text Completions (Legacy, usado por ciertos modos de Zed)."""
    if request.method == 'OPTIONS':
        return jsonify({"status": "ok"}), 200

    try:
        data = request.get_json()
        if not data:
            return jsonify({"error": "Cuerpo JSON inválido"}), 400

        prompt = data.get("prompt", "")
        if isinstance(prompt, list):
            prompt = "".join(prompt)

        max_tokens = int(data.get("max_tokens", data.get("max_completion_tokens", 50)))
        temperature = float(data.get("temperature", 0.7))
        stream = data.get("stream", False)

        max_tokens = max(1, min(max_tokens, 500))
        temperature = max(0.1, min(temperature, 2.0))

        # Modo Streaming (SSE)
        if stream:
            return Response(
                generar_stream_openai(prompt, max_tokens, temperature, is_chat=False),
                mimetype='text/event-stream'
            )

        # Modo Normal (JSON estático)
        completion = generar_autocompletado(prompt, max_tokens, temperature)
        cmpl_id = f"cmpl-rnn-{int(time.time())}"

        return jsonify({
            "id": cmpl_id,
            "object": "text_completion",
            "created": int(time.time()),
            "model": "rnn-autocomplete",
            "choices": [
                {
                    "text": completion,
                    "index": 0,
                    "logprobs": None,
                    "finish_reason": "length"
                }
            ],
            "usage": {
                "prompt_tokens": len(prompt),
                "completion_tokens": len(completion),
                "total_tokens": len(prompt) + len(completion)
            }
        })

    except Exception as e:
        print(f"❌ Error en /v1/completions: {e}")
        return jsonify({"error": str(e)}), 500

# =========================================================
# 6. EJECUCIÓN DEL SERVIDOR
# =========================================================

if __name__ == '__main__':
    inicializar_servidor()
    # Ejecutar en el puerto 5000 (accesible localmente)
    app.run(host='127.0.0.1', port=5000, debug=False)
