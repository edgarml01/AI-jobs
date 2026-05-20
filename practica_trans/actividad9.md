# Máscara de Relleno (Padding Mask)

## Análisis del Mecanismo de Enmascaramiento

### 1. ¿Por qué la Frase 2 no necesita celdas enmascaradas (o tachadas) en su procesamiento?
Porque la frase aprovecha la longitud máxima permitida en su totalidad con palabras que poseen contenido real. Dado que no contiene tokens de relleno (`[PAD]`), no hay celdas que el mecanismo de atención deba bloquear u ocultar.

### 2. ¿Qué consecuencias tendría que el modelo permitiera la atención hacia los tokens `[PAD]`?
Si se desactivara la máscara de padding y las palabras reales atendieran a los elementos `[PAD]`, se generarían los siguientes efectos negativos:
* **Contaminación de la semántica:** El vector resultante de las palabras reales se combinaría con la representación del token de relleno (que carece de significado), devaluando y distorsionando la riqueza del vector contextual final.
* **Sesgo y ruido en el entrenamiento:** El modelo intentaría extraer correlaciones y patrones lingüísticos inexistentes con los espacios en blanco, reduciendo significativamente la precisión y la calidad de las predicciones en tareas posteriores.
