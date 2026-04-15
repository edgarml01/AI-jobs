# Conclusiones Críticas - Fase 3

## 1. Estacionariedad de la serie temporal
Observando la gráfica temporal generada por el script (sección 2 del código en EDA.ipynb), la serie de tiempo **no es estacionaria**. La media no es constante: hay una tendencia lineal ascendente (de ~10 a ~50) debido a `np.linspace(10, 50, 500)`, y la varianza parece relativamente constante, pero la oscilación sinusoidal y el ruido gaussiano introducen variabilidad. Esto se confirma visualmente en el plot, donde la señal no fluctúa alrededor de un valor fijo.

Esto es un factor crítico antes de entrenar un modelo predictivo porque muchos algoritmos (como ARIMA o redes neuronales recurrentes) asumen estacionariedad para evitar sesgos. Si no se corrige (e.g., mediante diferenciación o transformación), el modelo podría aprender la tendencia en lugar de patrones reales, llevando a predicciones inexactas o sobreajuste.

## 2. Factores físicos que generan outliers en el Escenario B
Si yo hubiera construido el circuito para capturar este dataset (Escenario B: predicción térmica de una estructura metálica bajo soldadura), factores físicos del entorno que podrían generar picos atípicos incluyen:
- **Interferencias electromagnéticas**: La máquina de soldar genera campos EM que distorsionan las lecturas de termopares, causando spikes repentinos.
- **Cambios ambientales**: Variaciones en temperatura ambiente o humedad que afectan la conductividad térmica, produciendo outliers durante transiciones.
- **Fallos en el hardware**: Desconexiones temporales en sensores o ruido en cables, simulables como valores extremos en el código (e.g., agregando `np.random.uniform(-20, 20)` a índices aleatorios).
- **Estrés mecánico**: Vibraciones o deformaciones que alteran la posición del sensor, generando lecturas erráticas.

Estos outliers se reflejarían en métricas como un aumento en la desviación estándar y asimetría en el histograma.

## 3. Riesgos de saltar la fase de EDA
Como ingenieros, saltar esta fase de análisis y conectar datos crudos directamente a una Red Neuronal conlleva riesgos significativos:
- **Sobreajuste a ruido o tendencias**: Sin inspeccionar la distribución o estacionariedad, el modelo aprendería patrones espurios (e.g., la tendencia lineal), fallando en datos nuevos.
- **Falta de detección de anomalías**: Outliers no identificados (como en la gráfica temporal) podrían distorsionar el entrenamiento, reduciendo la precisión en predicciones reales.
- **Problemas de escalabilidad**: Métricas como media/varianza inconsistentes llevarían a gradientes inestables en el entrenamiento, aumentando el tiempo de convergencia o causando divergencia.
- **Errores en producción**: En aplicaciones críticas (e.g., monitoreo industrial), esto podría resultar en fallos costosos, como predicciones térmicas inexactas que ignoran interferencias físicas.

En resumen, el EDA es esencial para "sanity check" y preprocesamiento, asegurando modelos robustos y fiables.