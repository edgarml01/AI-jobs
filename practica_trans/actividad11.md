# Predicción de Palabras Enmascaradas (BERT)

## Contexto: **EL GATO `[MASK]` PESCADO**

### Respuestas al Cuestionario de Análisis

1. **¿Por qué el verbo "COME" resulta superior a la palabra "VERDE"?**
   Porque "COME" cumple con los requisitos sintácticos y semánticos de la oración: proporciona un verbo transitivo que vincula lógicamente al sujeto ("GATO") con su objeto ("PESCADO"). La palabra "VERDE" no tiene sentido gramatical ni lógica semántica en esa posición.

2. **¿Por qué el término "DUERME" no es una opción adecuada en este caso?**
   Aunque la frase *"EL GATO DUERME"* tiene sentido por sí sola, "DUERME" es un verbo intransitivo. Introducirlo en la oración causaría una colisión sintáctica con la palabra *"PESCADO"*, ya que no se puede "dormir un pescado".

3. **¿Por qué es crucial que el modelo pueda analizar la palabra "PESCADO" (situada después de la máscara)?**
   Porque la información del contexto posterior es la que define la naturaleza de la acción. Si solo mirásemos hacia atrás (*"EL GATO..."*), cualquier verbo de acción podría ser candidato viable (correr, saltar, maullar). Visualizar el texto a ambos lados de la máscara (bidireccionalidad) permite a modelos como BERT deducir con exactitud el término faltante.
