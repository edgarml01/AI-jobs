# ACTIVIDAD 2: EL ENIGMA DEL ORÁCULO SECUENCIAL
## ANATOMÍA DE UNA VANILLA RNN - Respuestas

---

## Actividad 2.1: Mapeo de Variables

Dada la ecuación fundamental: $h_t = \tanh(W_{hx} x_t + W_{hh} h_{t-1} + b)$

Identifica y escribe la frase exacta del poema que hace referencia a cada componente:

**$x_t$ - Soy la novedad pura, el pulso del instante, la matriz de características que el mundo me da en este segundo.**

**$h_{t-1}$ - Pero soy ciego sin mi compañero, el fantasma del pasado, que trae consigo el resumen de todo lo que hemos vivido hasta ayer.**

**$W_{hx}, W_{hh}$ - Para unirnos, cruzamos por peajes inmutables, barreras que multiplican nuestra importancia y deciden qué tanto valemos.**

**$b$ - Juntos, sumados a un pequeño desvío inevitable.**

**$\tanh$ - Chocamos contra un muro curvo que nos comprime entre el -1 y el 1, evitando que nuestra energía explote hacia el infinito.**

**$h_t$ - Al salir de esa curva, nazco yo, una nueva identidad. Soy tu estado actual, la respuesta de hoy.**

---

## Actividad 2.2: El Análisis de Dimensionalidad

Dados:
- $x_t \in \mathbb{R}^{20}$ (características de entrada)
- $h_{t-1} \in \mathbb{R}^{64}$ (estado oculto del paso anterior)

Calcula y justifica las dimensiones:

### 1. Dimensiones de la matriz $W_{hx}$

$W_{hx}$ debe transformar la entrada $x_t$ de dimensión 20 al espacio oculto de dimensión 64.

**Dimensiones: $W_{hx} \in \mathbb{R}^{64 \times 20}$**

Justificación: En la operación $W_{hx} x_t$, para obtener un vector de salida de 64 elementos a partir de un vector de entrada de 20 elementos, la matriz debe tener 64 filas (una para cada neurona oculta) y 20 columnas (una para cada característica de entrada).

### 2. Dimensiones de la matriz $W_{hh}$

$W_{hh}$ debe transformar el estado oculto anterior $h_{t-1}$ de dimensión 64 al espacio oculto de dimensión 64.

**Dimensiones: $W_{hh} \in \mathbb{R}^{64 \times 64}$**

Justificación: La operación $W_{hh} h_{t-1}$ combina el estado anterior (64 elementos) consigo mismo. Tanto la entrada como la salida están en el espacio de 64 dimensiones, por lo que la matriz es cuadrada con 64 filas y 64 columnas.

### 3. Dimensión del vector resultante $h_t$

**Dimensión: $h_t \in \mathbb{R}^{64}$**

Justificación: La suma $W_{hx} x_t + W_{hh} h_{t-1} + b$ produce:
- $W_{hx} x_t \in \mathbb{R}^{64}$
- $W_{hh} h_{t-1} \in \mathbb{R}^{64}$
- $b \in \mathbb{R}^{64}$

Todas las operaciones son vectoriales de 64 elementos. Al aplicar $\tanh$, que es una función elemento a elemento, se preserva la dimensionalidad de 64.

---

## Actividad 2.3: La Estrofa Perdida

**Estrofa que describe el parámetro $b$ (bias):**

Soy el ancla invisible, el guardián del desplazamiento,
aquel que tira la función hacia nuevos horizontes,
liberándola de pasar eternamente por el cero.
Sin mí, la transformación sería rígida y cautiva,
pero con mis pequeños ajustes en cada neurona,
permito que la red encuentre el punto exacto donde despertar.
Soy el silencio que habla, el sesgo que recentra,
el lienzo blanco sobre el cual se pinta la capacidad de aprendizaje.

---

## Actividad 2.4: El Límite del Muro Curvo

### 1. Gráfica conceptual de $f(z) = \tanh(z)$ y $f'(z) = 1 - \tanh^2(z)$

La función $\tanh(z)$:
- Pasa por el origen (0, 0)
- Tiene un rango de [-1, 1]
- Tiene pendiente máxima en z = 0 (valor de derivada = 1)
- Se aplana cuando z tiende a infinito (positive o negativo)

La derivada $f'(z) = 1 - \tanh^2(z)$:
- Alcanza su valor máximo de 1 cuando z = 0
- Disminuye a medida que |z| aumenta
- Se acerca a 0 cuando z tiende a ±infinito

### 2. Comportamiento cuando $z = 500$

Si $z = 500$:
- $\tanh(500) \approx 1$ (se satura en el límite superior)
- $f'(500) = 1 - \tanh^2(500) \approx 1 - 1^2 = 0$ (la derivada se anula)

**El valor de la derivada es prácticamente 0.**

### 3. Por qué la saturación es catastrófica para el aprendizaje

La saturación en $\tanh$ causa lo que se conoce como el problema del "vanishing gradient" (gradiente que se desvanece):

- Durante el backpropagation, los gradientes se multiplican por $f'(z) \approx 0$
- Un gradiente multiplicado por 0 se convierte en 0
- El error no puede propagarse hacia atrás efectivamente
- Los pesos más antiguos en la red reciben actualizaciones infinitesimales
- El aprendizaje se ralentiza o se detiene completamente
- La red no puede aprender dependencias a largo plazo

Este fenómeno es particularmente problemático en RNNs porque los gradientes se multiplican múltiples veces al propagarse hacia atrás en el tiempo (BPTT), causando que se desvanezcan exponencialmente.

---

## Actividad 2.5: El Eco del Castigo

**Descripción del viaje del error en reversa:**

El error comienza en $h_t$ (la salida actual donde la red se equivocó).

El gradiente debe atravesar los siguientes "peajes" y "muros" en orden inverso:

1. **El muro curvo en reversa**: El error primero atraviesa la derivada de $\tanh$:
   $$\frac{\partial h_t}{\partial z} = f'(z) = 1 - \tanh^2(z)$$

2. **El peaje de la combinación**: El error se distribuye entre sus dos componentes:
   - Hacia el peaje $W_{hx}$ (afecta los pesos de entrada)
   - Hacia el peaje $W_{hh}$ (afecta los pesos recurrentes)
   - Hacia el fantasma del pasado $h_{t-1}$ (continúa el viaje temporal)

3. **El segundo peaje recurrente**: El error que va hacia $h_{t-1}$ debe atravesar nuevamente $W_{hh}$ multiplicándose:
   $$\frac{\partial L}{\partial h_{t-1}} = \frac{\partial L}{\partial h_t} \cdot \frac{\partial h_t}{\partial h_{t-1}} = \frac{\partial L}{\partial h_t} \cdot W_{hh}^T \cdot f'(z)$$

4. **El ciclo recursivo**: En el paso temporal anterior, el error nuevamente atraviesa el muro curvo y los peajes.

**Operación matemática que representa este viaje en reversa:**

La **regla de la cadena del cálculo diferencial** es lo que fundamenta este viaje en reversa. Específicamente:

$$\frac{\partial L}{\partial W_{hh}} = \frac{\partial L}{\partial h_t} \cdot \frac{\partial h_t}{\partial W_{hh}}$$

Y multiplicando hacia atrás en múltiples pasos temporales:

$$\frac{\partial L}{\partial h_0} = \prod_{k=0}^{t} \left( W_{hh}^T \cdot \text{diag}(1 - \tanh^2(z_k)) \right)$$

Este producto de derivadas es lo que causa el problema del vanishing/exploding gradient, porque los gradientes se multiplican repetidamente.

---

## Actividad 2.6: Depuración del Oráculo

### 1. Error matemático exacto

**El error:** Usar el operador `*` en NumPy realiza multiplicación elemento a elemento (Hadamard product), no multiplicación matricial.

Cuando escribes:
```python
combinacion = (W_hx * x_t) + (W_hh * h_prev) + b
```

- `W_hx` tiene dimensión (64, 20)
- `x_t` tiene dimensión (20,)
- `W_hx * x_t` intenta multiplicación elemento a elemento, lo que resulta en broadcasting erróneo
- Se produciría un error de dimensionalidad o un resultado matemáticamente incorrecto

**El álgebra lineal requiere** el producto punto (multiplicación matricial), no elemento a elemento.

### 2. Código corregido

```python
def paso_rnn_correcto(x_t, h_prev, W_hx, W_hh, b):
    # Operación correcta usando multiplicación matricial
    combinacion = np.dot(W_hx, x_t) + np.dot(W_hh, h_prev) + b
    return np.tanh(combinacion)
```

O alternativamente, usando el operador `@` de Python 3.5+ para multiplicación matricial:

```python
def paso_rnn_correcto_v2(x_t, h_prev, W_hx, W_hh, b):
    # Usando @ para multiplicación matricial explícita
    combinacion = (W_hx @ x_t) + (W_hh @ h_prev) + b
    return np.tanh(combinacion)
```

**Verificación de dimensionalidad:**
- `W_hx @ x_t`: (64, 20) @ (20,) = (64,)
- `W_hh @ h_prev`: (64, 64) @ (64,) = (64,)
- Suma vectorial: (64,) + (64,) + (64,) = (64,)
- `np.tanh()`: mantiene dimensionalidad (64,)

El resultado correcto es un vector de 64 elementos que representa el nuevo estado oculto $h_t$.

---

## Resumen

Las actividades exploran los componentes fundamentales de una Vanilla RNN a través de una narrativa poética, desarrollando:

- Comprensión conceptual del flujo de datos
- Análisis riguroso de dimensionalidad matricial
- Pensamiento creativo manteniendo precisión matemática
- Identificación del problema del vanishing gradient
- Aplicación del cálculo diferencial en backpropagation
- Debugging de errores comunes en implementaciones NumPy

Estos elementos son cruciales para comprender por qué las RNNs vanilla tienen limitaciones que llevaron al desarrollo de arquitecturas como LSTM y GRU.
