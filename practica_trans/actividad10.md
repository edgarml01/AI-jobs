# Atención Cruzada (Cross-Attention)

## Matriz de Atención para el Token en Generación ("COFFEE")

| Desde (Inglés / Decoder) ↓ / Hacia (Español / Encoder) → | YO | QUIERO | CAFE |
| :--- | :---: | :---: | :---: |
| **Palabra 3 (Posición en proceso)** | 5% | 15% | **80%** |

## Respuestas de Análisis

1. **¿Por qué la palabra "CAFE" debe recibir la mayor atención de la columna?**
   Porque "CAFE" es la traducción semántica directa de lo que el decodificador se prepara para escribir a continuación ("COFFEE"). Al prestarle el 80% de atención, el decodificador extrae los detalles del concepto del idioma original para plasmarlos correctamente en el idioma de salida.

2. **¿Tiene sentido lógico que al traducir el pronombre "I" el modelo mire a "YO"?**
   Sí, tiene todo el sentido. Para lograr una alineación lingüística correcta, los elementos equivalentes de la oración de origen y destino deben enlazarse de forma estrecha, y el pronombre personal es la referencia inicial.

3. **¿Cuál es la diferencia clave entre Autoatención (Self-Attention) y Atención Cruzada (Cross-Attention)?**
   * **Autoatención (Self-Attention):** Relaciona los tokens de una única secuencia entre sí (por ejemplo, analizar el contexto de una oración en español dentro del propio codificador).
   * **Atención Cruzada (Cross-Attention):** Relaciona elementos de dos secuencias distintas (el decodificador consulta la información procesada por el codificador) para transferir y alinear significados entre oraciones de origen y destino.
