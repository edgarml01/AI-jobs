# Softmax Paso a Paso

## Normalización de Exponenciales (Suma Total = 25.68)

| Palabra | Valor Exponencial ($e^{x_i}$) | Operación ($e^{x_i} / \sum e^{x_j}$) | Probabilidad Aproximada (%) |
| :--- | :---: | :---: | :---: |
| **NIÑA** | 20.09 | $20.09 / 25.68$ | **78%** |
| **PEQUEÑA**| 1.65 | $1.65 / 25.68$ | **6%** |
| **COME** | 1.22 | $1.22 / 25.68$ | **5%** |
| **FRUTA** | 2.72 | $2.72 / 25.68$ | **11%** |

## Análisis Conceptual: ¿Por qué usar Softmax y no una normalización directa?

Si dividiéramos las puntuaciones de atención directamente entre su suma, nos enfrentaríamos a varios problemas que la función Softmax resuelve eficientemente:

1. **Soporte para números negativos:** Las puntuaciones de atención originales pueden ser negativas. La función exponencial ($e^x$) convierte cualquier número real en un valor estrictamente positivo, haciendo posible calcular porcentajes válidos que sumen 100%.
2. **Amplificación del contraste (Decisiones nítidas):** Al elevar los valores a una potencia exponencial, las diferencias pequeñas en las puntuaciones originales se agrandan notablemente en la salida. Esto genera un comportamiento tipo *"el ganador se lleva casi todo"*, facilitando que el modelo concentre su atención de forma clara en la opción más relevante en lugar de dudar de manera indefinida entre valores similares.
