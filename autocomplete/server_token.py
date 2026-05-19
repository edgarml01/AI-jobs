"""
SERVIDOR FLASK PARA MODELO RNN TOKEN-LEVEL
==================================================================
Versión del servidor diseñada para el modelo entrenado con
tokenización a nivel de token (rnn_token.py) en lugar de carácter.

Soporta los mismos endpoints:
  1. /predict           -> Extensión de VSCode
  2. /v1/chat/completions -> Zed / OpenAI API compatible
  3. /v1/completions      -> Clientes OpenAI legacy
  4. /v1/models           -> Descubrimiento de modelos

Requisitos:
    - Flask
    - TensorFlow / Keras
    - Archivo 'corpus.c' (para reconstruir el tokenizador)
    - Archivo 'vocabulario_tokens.json' (vocabulario guardado)
    - Archivo 'modelo_token_rnn.h5' (modelo token-level entrenado)

Uso:
    source .venv/bin/activate
    python server_token.py
==================================================================
"""

import os
import re
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

SEQUENCE_LENGTH = 64
CORPUS_PATH = "corpus.c"
MODEL_PATH = "modelo_token_rnn.h5"
VOCAB_PATH = "vocabulario_tokens.json"

# Variables globales
token_to_idx = {}
idx_to_token = {}
vocab_size = 0
modelo = None

# =========================================================
# 2. TOKENIZADOR LÉXICO PARA CÓDIGO C
# =========================================================
# Mismo patrón regex usado durante el entrenamiento (rnn_token.py)
# para garantizar consistencia perfecta entre entrenamiento e inferencia.
# =========================================================

TOKEN_PATTERN = re.compile(
    r'//[^\n]*'
    r'|"[^"]*"'
    r"|'[^']*'"
    r'|\d+'
    r'|[a-zA-Z_]\w*'
    r'|==|!=|>=|<=|&&|\|\||<<|>>'
    r'|\+\+|--|->|\+=|-=|\*=|/='
    r'|[+\-*/%=<>!&|^~]'
    r'|[{}()\[\];,.]'
    r'|\n'
    r'|    '
    r'| '
)


def tokenizar_codigo_c(codigo_fuente):
    """Divide el código fuente C en una lista de tokens léxicos."""
    return TOKEN_PATTERN.findall(codigo_fuente)

# =========================================================
# 3. CARGA DE VOCABULARIO Y MODELO
# =========================================================

def inicializar_servidor():
    global token_to_idx, idx_to_token, vocab_size, modelo

    print("\n" + "="*60)
    print("SERVIDOR TOKEN-LEVEL PARA AUTOCOMPLETADO DE CÓDIGO C (RNN)")
    print("="*60)

    # 1. Cargar vocabulario de tokens
    if not os.path.exists(VOCAB_PATH):
        print(f"❌ Error: No se encontró '{VOCAB_PATH}'.")
        print("Ejecuta 'python rnn_token.py' primero para generar el vocabulario.")
        exit(1)

    with open(VOCAB_PATH, "r", encoding="utf-8") as f:
        vocabulario = json.load(f)

    token_to_idx = vocabulario["token_to_idx"]
    # Las claves JSON son siempre strings, convertir a int
    idx_to_token = {int(k): v for k, v in vocabulario["idx_to_token"].items()}
    vocab_size = vocabulario["vocab_size"]

    print(f"✓ Vocabulario cargado: {vocab_size} tokens únicos.")

    # 2. Cargar modelo Keras
    if not os.path.exists(MODEL_PATH):
        print(f"❌ Error: No se encontró el modelo '{MODEL_PATH}'.")
        print("Ejecuta 'python rnn_token.py' primero para entrenar el modelo.")
        exit(1)

    print(f"\n📦 Cargando modelo token-level desde '{MODEL_PATH}'...")
    try:
        modelo = load_model(MODEL_PATH)
        print("✓ Modelo cargado correctamente en memoria.")
    except Exception as e:
        print(f"❌ Error al cargar el modelo: {e}")
        exit(1)

    print("="*60)
    print("🚀 Servidor token-level listo en http://127.0.0.1:5001")
    print("   - VSCode Endpoint:  http://127.0.0.1:5001/predict")
    print("   - Zed/OpenAI API:   http://127.0.0.1:5001/v1")
    print("="*60 + "\n")

# =========================================================
# 4. FUNCIONES DE PREDICCIÓN Y MUESTREO
# =========================================================

def sample_with_temperature(preds, temperature=0.7):
    """Muestrea un índice a partir de un vector de probabilidades con temperatura."""
    preds = np.asarray(preds).astype("float64")

    if temperature <= 0:
        return np.argmax(preds)

    log_preds = np.log(preds + 1e-8) / temperature
    exp_preds = np.exp(log_preds)
    probas = exp_preds / np.sum(exp_preds)

    return np.random.multinomial(1, probas, 1).argmax()


def generar_autocompletado(prompt, num_tokens=30, temperature=0.7):
    """
    Genera la predicción de tokens siguientes a partir de un prompt.
    
    A diferencia del servidor char-level que genera N caracteres,
    este genera N tokens completos (palabras, operadores, etc.).
    """
    if not prompt:
        prompt = "int "

    # Tokenizar el prompt de entrada
    prompt_tokens = tokenizar_codigo_c(prompt)
    generated_tokens = list(prompt_tokens)

    for _ in range(num_tokens):
        # Tomar los últimos SEQUENCE_LENGTH tokens como contexto
        context = generated_tokens[-SEQUENCE_LENGTH:]

        # Convertir a índices (usar 0 para tokens desconocidos/OOV)
        sequence = [token_to_idx.get(t, 0) for t in context]
        sequence = pad_sequences([sequence], maxlen=SEQUENCE_LENGTH)

        # Predecir siguiente token
        prediction = modelo.predict(sequence, verbose=0)[0]
        predicted_index = sample_with_temperature(prediction, temperature)
        predicted_token = idx_to_token.get(predicted_index, " ")

        generated_tokens.append(predicted_token)

    # Reconstruir el texto: unir todos los tokens generados (sin el prompt original)
    completion_tokens = generated_tokens[len(prompt_tokens):]
    return "".join(completion_tokens)


def generar_stream_openai(prompt, num_tokens=30, temperature=0.7, is_chat=True):
    """Generador SSE compatible con OpenAI streaming para Zed."""
    if not prompt:
        prompt = "int "

    prompt_tokens = tokenizar_codigo_c(prompt)
    generated_tokens = list(prompt_tokens)

    cmpl_id = f"chatcmpl-token-{int(time.time())}" if is_chat else f"cmpl-token-{int(time.time())}"
    created_time = int(time.time())

    for _ in range(num_tokens):
        context = generated_tokens[-SEQUENCE_LENGTH:]
        sequence = [token_to_idx.get(t, 0) for t in context]
        sequence = pad_sequences([sequence], maxlen=SEQUENCE_LENGTH)

        prediction = modelo.predict(sequence, verbose=0)[0]
        predicted_index = sample_with_temperature(prediction, temperature)
        predicted_token = idx_to_token.get(predicted_index, " ")

        generated_tokens.append(predicted_token)

        # Enviar cada token como un chunk SSE
        if is_chat:
            chunk = {
                "id": cmpl_id,
                "object": "chat.completion.chunk",
                "created": created_time,
                "model": "rnn-token-autocomplete",
                "choices": [{
                    "index": 0,
                    "delta": {"content": predicted_token},
                    "finish_reason": None
                }]
            }
        else:
            chunk = {
                "id": cmpl_id,
                "object": "text_completion",
                "created": created_time,
                "model": "rnn-token-autocomplete",
                "choices": [{
                    "text": predicted_token,
                    "index": 0,
                    "logprobs": None,
                    "finish_reason": None
                }]
            }

        yield f"data: {json.dumps(chunk)}\n\n"

    # Chunk final
    if is_chat:
        final = {
            "id": cmpl_id, "object": "chat.completion.chunk",
            "created": created_time, "model": "rnn-token-autocomplete",
            "choices": [{"index": 0, "delta": {}, "finish_reason": "stop"}]
        }
    else:
        final = {
            "id": cmpl_id, "object": "text_completion",
            "created": created_time, "model": "rnn-token-autocomplete",
            "choices": [{"text": "", "index": 0, "logprobs": None, "finish_reason": "length"}]
        }

    yield f"data: {json.dumps(final)}\n\n"
    yield "data: [DONE]\n\n"

# =========================================================
# 5. MIDDLEWARE CORS
# =========================================================

@app.after_request
def add_cors_headers(response):
    response.headers['Access-Control-Allow-Origin'] = '*'
    response.headers['Access-Control-Allow-Methods'] = 'GET, POST, OPTIONS'
    response.headers['Access-Control-Allow-Headers'] = 'Content-Type, Authorization'
    return response

# =========================================================
# 6. ENDPOINTS DE LA API
# =========================================================

@app.route('/', methods=['GET'])
def index():
    return jsonify({
        "status": "online",
        "service": "C Code Autocomplete TOKEN-LEVEL RNN API",
        "tokenization": "token-level (word/lexeme)",
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
# ENDPOINT VSCODE (Nativo)
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
        num_tokens = int(data.get("num_tokens", data.get("num_chars", 30)))
        temperature = float(data.get("temperature", 0.7))

        num_tokens = max(1, min(num_tokens, 200))
        temperature = max(0.1, min(temperature, 2.0))

        completion = generar_autocompletado(prompt, num_tokens, temperature)

        return jsonify({
            "success": True,
            "prompt": prompt,
            "completion": completion,
            "full_text": prompt + completion,
            "parameters": {
                "num_tokens": num_tokens,
                "temperature": temperature
            }
        })

    except Exception as e:
        print(f"❌ Error en /predict: {e}")
        return jsonify({"error": str(e)}), 500

# ---------------------------------------------------------
# ENDPOINTS OPENAI API COMPATIBLE (ZED)
# ---------------------------------------------------------

@app.route('/v1/models', methods=['GET', 'OPTIONS'])
def list_models():
    if request.method == 'OPTIONS':
        return jsonify({"status": "ok"}), 200

    return jsonify({
        "object": "list",
        "data": [{
            "id": "rnn-token-autocomplete",
            "object": "model",
            "created": int(time.time()),
            "owned_by": "local-rnn-token",
            "permission": [],
            "root": "rnn-token-autocomplete",
            "parent": None
        }]
    })


@app.route('/v1/chat/completions', methods=['POST', 'OPTIONS'])
def chat_completions():
    if request.method == 'OPTIONS':
        return jsonify({"status": "ok"}), 200

    try:
        data = request.get_json()
        if not data:
            return jsonify({"error": "Cuerpo JSON inválido"}), 400

        messages = data.get("messages", [])
        prompt = ""
        if isinstance(messages, list):
            for msg in messages:
                if isinstance(msg, dict) and msg.get("content"):
                    prompt += msg.get("content", "") + "\n"
            prompt = prompt.rstrip("\n")
        elif isinstance(messages, str):
            prompt = messages

        max_tokens = int(data.get("max_tokens", data.get("max_completion_tokens", 30)))
        temperature = float(data.get("temperature", 0.7))
        stream = data.get("stream", False)

        max_tokens = max(1, min(max_tokens, 200))
        temperature = max(0.1, min(temperature, 2.0))

        if stream:
            return Response(
                generar_stream_openai(prompt, max_tokens, temperature, is_chat=True),
                mimetype='text/event-stream'
            )

        completion = generar_autocompletado(prompt, max_tokens, temperature)
        cmpl_id = f"chatcmpl-token-{int(time.time())}"

        return jsonify({
            "id": cmpl_id,
            "object": "chat.completion",
            "created": int(time.time()),
            "model": "rnn-token-autocomplete",
            "choices": [{
                "index": 0,
                "message": {"role": "assistant", "content": completion},
                "finish_reason": "stop"
            }],
            "usage": {
                "prompt_tokens": len(tokenizar_codigo_c(prompt)),
                "completion_tokens": len(tokenizar_codigo_c(completion)),
                "total_tokens": len(tokenizar_codigo_c(prompt)) + len(tokenizar_codigo_c(completion))
            }
        })

    except Exception as e:
        print(f"❌ Error en /v1/chat/completions: {e}")
        return jsonify({"error": str(e)}), 500


@app.route('/v1/completions', methods=['POST', 'OPTIONS'])
def text_completions():
    if request.method == 'OPTIONS':
        return jsonify({"status": "ok"}), 200

    try:
        data = request.get_json()
        if not data:
            return jsonify({"error": "Cuerpo JSON inválido"}), 400

        prompt = data.get("prompt", "")
        if isinstance(prompt, list):
            prompt = "".join(prompt)

        max_tokens = int(data.get("max_tokens", data.get("max_completion_tokens", 30)))
        temperature = float(data.get("temperature", 0.7))
        stream = data.get("stream", False)

        max_tokens = max(1, min(max_tokens, 200))
        temperature = max(0.1, min(temperature, 2.0))

        if stream:
            return Response(
                generar_stream_openai(prompt, max_tokens, temperature, is_chat=False),
                mimetype='text/event-stream'
            )

        completion = generar_autocompletado(prompt, max_tokens, temperature)
        cmpl_id = f"cmpl-token-{int(time.time())}"

        return jsonify({
            "id": cmpl_id,
            "object": "text_completion",
            "created": int(time.time()),
            "model": "rnn-token-autocomplete",
            "choices": [{
                "text": completion,
                "index": 0,
                "logprobs": None,
                "finish_reason": "length"
            }],
            "usage": {
                "prompt_tokens": len(tokenizar_codigo_c(prompt)),
                "completion_tokens": len(tokenizar_codigo_c(completion)),
                "total_tokens": len(tokenizar_codigo_c(prompt)) + len(tokenizar_codigo_c(completion))
            }
        })

    except Exception as e:
        print(f"❌ Error en /v1/completions: {e}")
        return jsonify({"error": str(e)}), 500

# =========================================================
# 7. EJECUCIÓN DEL SERVIDOR
# =========================================================

if __name__ == '__main__':
    inicializar_servidor()
    # Puerto 5001 para no conflictuar con el servidor char-level (5000)
    app.run(host='127.0.0.1', port=5000, debug=False)
