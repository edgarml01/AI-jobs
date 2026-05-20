# Transmisión de Información en Capas Profundas de Atención

## Análisis del Vector "FRUTA" en la Capa 2

A medida que el texto asciende a través de las capas de un Transformer, la representación de las palabras evoluciona drásticamente:

1. **Vectores de Contexto Enriquecidos:** En la Capa 2, los vectores de cada palabra ya no representan únicamente su definición aislada en el vocabulario. Por ejemplo, el vector de **COME** ya ha absorbido y amalgamado información clave sobre el sujeto (**NIÑA**) durante el paso por la Capa 1.
2. **Integración de Escenarios Globales:** Cuando **FRUTA** interactúa con **COME** en esta segunda capa, su mecanismo de atención asimila una estructura de datos semántica refinada. En lugar de limitarse a "asociarse con un verbo", adquiere la comprensión de que *"hay un agente femenino que ejecuta la acción de comer"*.
3. **Representación Final:** Este proceso iterativo por capas permite al Transformer construir una comprensión abstracta y jerárquica de la escena completa, posibilitando que un objeto inanimado como la fruta reconozca su rol dentro del evento global: *ser consumida por la niña*.
