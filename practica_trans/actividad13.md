# Arquitecturas Recurrentes (RNN) vs. Transformers

## 1. Ruta de Conectividad (Saltos de Información entre "A" y "E")
* **RNN (Secuencial):** Necesita realizar **4 transiciones consecutivas** para propagar la información del token A al token E, procesando cada elemento intermedio uno por uno.
* **Transformer (Atención):** Requiere **1 único salto**. La matriz de atención establece un canal de comunicación directo entre A y E, eliminando intermediarios.

## 2. Escalabilidad con Secuencias de 100 Palabras
* **RNN:** Su secuencia temporal escala de manera **lineal** ($O(N)$) en términos de pasos de procesamiento secuencial.
* **Transformer:** El cálculo de la matriz de atención escala de forma **cuadrática** ($O(N^2)$), demandando el procesamiento de 10,000 interacciones posibles de atención.

## 3. Ventajas Competitivas de los Transformers
* **Procesamiento en Paralelo (Paralelización):** Las RNNs están obligadas a esperar la salida del paso de tiempo anterior para calcular el siguiente. Los Transformers evalúan toda la frase al mismo tiempo en una sola operación matricial, optimizando el rendimiento en hardware acelerador (GPUs/TPUs).
* **Resolución del Desvanecimiento del Gradiente:** Al reducir la distancia de comunicación entre cualquier par de palabras a un solo paso directo, se previene la pérdida de información a largo plazo ("olvido" o amnesia sintáctica) que sufren las RNNs en textos de gran longitud.
