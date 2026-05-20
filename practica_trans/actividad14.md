# Escalado de Puntuaciones de Atención (Scaled Dot-Product)

## Simulación Numérica del Efecto del Escalado

A continuación se muestra el impacto de la magnitud de las puntuaciones sobre la distribución de pesos de Softmax:

### Escenario 1: Distribución sin Escalar `[8, 2, 2, 2]`
Al aplicar la función Softmax a valores grandes con diferencias marcadas:
* $e^8 \approx 2980.96$
* $e^2 \approx 7.39$
* Suma total de exponenciales $\approx 3003.13$
* **Distribución de pesos:** **`[99.26%, 0.25%, 0.25%, 0.25%]`**

**Consecuencia (Saturación):** El primer elemento absorbe casi la totalidad de la probabilidad. Esto provoca que el modelo ignore por completo las demás palabras y que las gradientes se vuelvan extremadamente pequeñas (desvanecimiento del gradiente), impidiendo el aprendizaje de relaciones matizadas durante el entrenamiento.

### Escenario 2: Distribución Escalada `[4, 1, 1, 1]` (Valores divididos por un factor de 2)
Al aplicar Softmax sobre valores reducidos que mantienen la misma relación de proporción:
* $e^4 \approx 54.60$
* $e^1 \approx 2.72$
* Suma total de exponenciales $\approx 62.76$
* **Distribución de pesos:** **`[87.0%, 4.33%, 4.33%, 4.33%]`**

**Consecuencia:** El primer elemento continúa liderando de manera clara la distribución, pero el resto de las palabras conservan un peso significativo (pasando del 0.25% al 4.33%). Esto permite que sus vectores de contenido aporten matices importantes a la mezcla final y que la información fluya sin saturación numérica.

## Conclusión Técnica

El factor de escalado (dividir el producto punto entre la raíz cuadrada de la dimensión de las claves, $\sqrt{d_k}$) es vital en el mecanismo de atención de los Transformers. Impide que las puntuaciones alcancen magnitudes excesivas al trabajar con vectores de alta dimensión, previniendo la saturación de la función Softmax y garantizando un entrenamiento numéricamente estable.
