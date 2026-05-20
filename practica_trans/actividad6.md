# Matriz de Atención Completa

## Tabla de Atención Normalizada (%)

| Desde ↓ / Hacia → | LA | NIÑA | PEQUEÑA | COME | FRUTA |
| :--- | :---: | :---: | :---: | :---: | :---: |
| **LA** | 10% | **60%** | 10% | 10% | 10% |
| **NIÑA** | 10% | 10% | 20% | **50%** | 10% |
| **PEQUEÑA** | 10% | **60%** | 10% | 10% | 10% |
| **COME** | 5% | 35% | 10% | 10% | **40%** |
| **FRUTA** | 5% | 10% | 5% | **60%** | 20% |

## Análisis y Preguntas de Reflexión

1. **¿Existe similitud entre la distribución de atención de "COME" y "FRUTA"?**
   No, presentan comportamientos muy distintos. La palabra **COME** (que actúa como verbo transitivo) reparte su atención de manera más dispersa para vincular al sujeto (**NIÑA**, con 35%) y al objeto (**FRUTA**, con 40%). Por su parte, la palabra **FRUTA** concentra la mayor parte de su atención (60%) de forma directa en el verbo **COME** para entender el contexto de la acción que recae sobre ella.

2. **¿Qué fila presenta una distribución de atención más dispersa y por qué?**
   La fila del verbo **COME**. Como núcleo de la acción, necesita conectar activamente con los distintos participantes de la oración (quién realiza la acción y qué es lo que se consume) para poder enriquecer su significado con el contexto de la frase.

3. **Si la secuencia tuviera una longitud de 100 palabras, ¿cuántas celdas tendría la matriz y qué implicaciones conlleva esto?**
   La matriz tendría **10,000 celdas** ($100 \times 100$). Esto demuestra que la complejidad espacial y temporal de la atención completa crece de forma **cuadrática** ($O(N^2)$) respecto al tamaño del texto, lo que genera un gran consumo de memoria RAM/VRAM en los modelos a medida que las secuencias se vuelven más largas.
