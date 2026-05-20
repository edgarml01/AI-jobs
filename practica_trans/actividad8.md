# Mezcla de Vectores de Contenido (Value Vectors)

## Cálculo de la Suma Ponderada para la Palabra "COME"

A continuación se calcula el vector de contexto mediante la combinación lineal de los vectores de contenido (Values) multiplicados por su respectivo coeficiente de atención:

* **LA:** $0.05 \times (1, 1) = (0.05, 0.05)$
* **NIÑA:** $0.35 \times (4, 5) = (1.40, 1.75)$
* **PEQUEÑA:** $0.10 \times (3, 4) = (0.30, 0.40)$
* **COME:** $0.10 \times (5, 1) = (0.50, 0.10)$
* **FRUTA:** $0.40 \times (6, 3) = (2.40, 1.20)$

## Vector Resultante

Sumamos los componentes en cada dimensión para hallar la representación final de la palabra:

* **Dimensión X:** $0.05 + 1.40 + 0.30 + 0.50 + 2.40 = \mathbf{4.65}$
* **Dimensión Y:** $0.05 + 1.75 + 0.40 + 0.10 + 1.20 = \mathbf{3.50}$

### **Vector de Salida Contextualizado: $(4.65, 3.50)$**

## Interpretación Geométrica y Semántica

En un espacio vectorial o mapa de embeddings, este nuevo vector se posiciona en una zona intermedia entre **FRUTA** y **NIÑA**. Esto demuestra que el Transformer ha enriquecido el significado abstracto del verbo "COME" inyectándole información de las entidades relacionadas en la oración: quién realiza la acción (la niña) y qué cosa es comida (la fruta).
