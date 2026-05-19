// Función: mate_sumar
// Devuelve la suma de dos enteros.
int mate_sumar(int a, int b) {
    return a + b;
}

// Función: mate_restar
// Devuelve la diferencia entre dos enteros.
int mate_restar(int a, int b) {
    return a - b;
}

// Función: mate_multiplicar
// Devuelve el producto de dos enteros.
int mate_multiplicar(int a, int b) {
    return a * b;
}

// Función: mate_dividir
// Devuelve la división entera de dos números.
int mate_dividir(int a, int b) {
    if (b == 0) {
        return 0;
    }
    return a / b;
}

// Función: mate_modulo
// Devuelve el residuo de la división.
int mate_modulo(int a, int b) {
    if (b == 0) {
        return 0;
    }
    return a % b;
}

// Función: mate_incrementar
// Aumenta un número en uno.
int mate_incrementar(int a) {
    return a + 1;
}

// Función: mate_decrementar
// Disminuye un número en uno.
int mate_decrementar(int a) {
    return a - 1;
}

// Función: mate_absoluto
// Devuelve el valor absoluto.
int mate_absoluto(int a) {
    if (a < 0) {
        return -a;
    }
    return a;
}

// Función: mate_maximo
// Devuelve el mayor de dos enteros.
int mate_maximo(int a, int b) {
    if (a > b) {
        return a;
    }
    return b;
}

// Función: mate_minimo
// Devuelve el menor de dos enteros.
int mate_minimo(int a, int b) {
    if (a < b) {
        return a;
    }
    return b;
}

// Función: mate_es_par
// Comprueba si un número es par.
int mate_es_par(int a) {
    return (a % 2) == 0;
}

// Función: mate_es_impar
// Comprueba si un número es impar.
int mate_es_impar(int a) {
    return (a % 2) != 0;
}

// Función: mate_limitar
// Restringe un valor dentro de un rango.
int mate_limitar(int val, int min, int max) {
    if (val < min) {
        return min;
    }
    if (val > max) {
        return max;
    }
    return val;
}

// Función: mate_potencia
// Calcula la potencia de una base.
int mate_potencia(int base, int exp) {
    int resultado = 1;
    for (int i = 0; i < exp; i++) {
        resultado = resultado * base;
    }
    return resultado;
}

// Función: mate_factorial
// Calcula el factorial de un número.
int mate_factorial(int n) {
    if (n <= 1) {
        return 1;
    }
    return n * mate_factorial(n - 1);
}

// Función: mate_mcd
// Calcula el máximo común divisor.
int mate_mcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Función: mate_mcm
// Calcula el mínimo común múltiplo.
int mate_mcm(int a, int b) {
    if (a == 0 || b == 0) {
        return 0;
    }
    return mate_absoluto(a * b) / mate_mcd(a, b);
}

// Función: mate_signo
// Devuelve el signo de un número.
int mate_signo(int a) {
    if (a > 0) {
        return 1;
    }
    if (a < 0) {
        return -1;
    }
    return 0;
}

// Función: mate_cuadrado
// Devuelve el cuadrado de un número.
int mate_cuadrado(int a) {
    return a * a;
}

// Función: mate_cubo
// Devuelve el cubo de un número.
int mate_cubo(int a) {
    return a * a * a;
}

// Función: arr_suma
// Calcula la suma de los elementos del arreglo.
int arr_suma(int arr[], int tamano) {
    int suma = 0;
    for (int i = 0; i < tamano; i++) {
        suma = suma + arr[i];
    }
    return suma;
}

// Función: arr_promedio
// Calcula el promedio de los elementos del arreglo.
int arr_promedio(int arr[], int tamano) {
    if (tamano == 0) {
        return 0;
    }
    return arr_suma(arr, tamano) / tamano;
}

// Función: arr_maximo
// Encuentra el valor máximo en un arreglo.
int arr_maximo(int arr[], int tamano) {
    int val_max = arr[0];
    for (int i = 1; i < tamano; i++) {
        if (arr[i] > val_max) {
            val_max = arr[i];
        }
    }
    return val_max;
}

// Función: arr_minimo
// Encuentra el valor mínimo en un arreglo.
int arr_minimo(int arr[], int tamano) {
    int val_min = arr[0];
    for (int i = 1; i < tamano; i++) {
        if (arr[i] < val_min) {
            val_min = arr[i];
        }
    }
    return val_min;
}

// Función: arr_contar_pares
// Cuenta los números pares en un arreglo.
int arr_contar_pares(int arr[], int tamano) {
    int cuenta = 0;
    for (int i = 0; i < tamano; i++) {
        if (arr[i] % 2 == 0) {
            cuenta = cuenta + 1;
        }
    }
    return cuenta;
}

// Función: arr_contar_impares
// Cuenta los números impares en un arreglo.
int arr_contar_impares(int arr[], int tamano) {
    int cuenta = 0;
    for (int i = 0; i < tamano; i++) {
        if (arr[i] % 2 != 0) {
            cuenta = cuenta + 1;
        }
    }
    return cuenta;
}

// Función: arr_contar_no_ceros
// Cuenta los elementos que no son cero en un arreglo.
int arr_contar_no_ceros(int arr[], int tamano) {
    int cuenta = 0;
    for (int i = 0; i < tamano; i++) {
        if (arr[i] != 0) {
            cuenta = cuenta + 1;
        }
    }
    return cuenta;
}

// Función: arr_contiene
// Comprueba si un valor existe en un arreglo.
int arr_contiene(int arr[], int tamano, int objetivo) {
    for (int i = 0; i < tamano; i++) {
        if (arr[i] == objetivo) {
            return 1;
        }
    }
    return 0;
}

// Función: arr_buscar_indice
// Devuelve el índice de un valor objetivo.
int arr_buscar_indice(int arr[], int tamano, int objetivo) {
    for (int i = 0; i < tamano; i++) {
        if (arr[i] == objetivo) {
            return i;
        }
    }
    return -1;
}

// Función: arr_llenar_ceros
// Llena un arreglo con ceros.
void arr_llenar_ceros(int arr[], int tamano) {
    for (int i = 0; i < tamano; i++) {
        arr[i] = 0;
    }
}

// Función: arr_llenar_unos
// Llena un arreglo con unos.
void arr_llenar_unos(int arr[], int tamano) {
    for (int i = 0; i < tamano; i++) {
        arr[i] = 1;
    }
}

// Función: arr_llenar_valor
// Llena un arreglo con un valor específico.
void arr_llenar_valor(int arr[], int tamano, int valor) {
    for (int i = 0; i < tamano; i++) {
        arr[i] = valor;
    }
}

// Función: arr_copiar
// Copia elementos de origen a destino.
void arr_copiar(int origen[], int destino[], int tamano) {
    for (int i = 0; i < tamano; i++) {
        destino[i] = origen[i];
    }
}

// Función: arr_invertir
// Invierte los elementos de un arreglo en su lugar.
void arr_invertir(int arr[], int tamano) {
    int inicio = 0;
    int fin = tamano - 1;
    while (inicio < fin) {
        int temp = arr[inicio];
        arr[inicio] = arr[fin];
        arr[fin] = temp;
        inicio++;
        fin--;
    }
}

// Función: arr_esta_ordenado
// Comprueba si un arreglo está ordenado ascendentemente.
int arr_esta_ordenado(int arr[], int tamano) {
    for (int i = 0; i < tamano - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            return 0;
        }
    }
    return 1;
}

// Función: arr_escalar
// Multiplica todos los elementos por un escalar.
void arr_escalar(int arr[], int tamano, int factor) {
    for (int i = 0; i < tamano; i++) {
        arr[i] = arr[i] * factor;
    }
}

// Función: arr_sumar_escalar
// Suma un escalar a todos los elementos del arreglo.
void arr_sumar_escalar(int arr[], int tamano, int cantidad) {
    for (int i = 0; i < tamano; i++) {
        arr[i] = arr[i] + cantidad;
    }
}

// Función: arr_intercambiar_elementos
// Intercambia dos elementos en un arreglo.
void arr_intercambiar_elementos(int arr[], int indice1, int indice2) {
    int temp = arr[indice1];
    arr[indice1] = arr[indice2];
    arr[indice2] = temp;
}

// Función: arr_primer_elemento
// Devuelve el primer elemento de un arreglo.
int arr_primer_elemento(int arr[]) {
    return arr[0];
}

// Función: arr_ultimo_elemento
// Devuelve el último elemento de un arreglo.
int arr_ultimo_elemento(int arr[], int tamano) {
    if (tamano == 0) {
        return 0;
    }
    return arr[tamano - 1];
}

// Función: cad_longitud
// Calcula la longitud de una cadena de texto.
int cad_longitud(char *cad) {
    int longi = 0;
    while (cad[longi] != '\0') {
        longi++;
    }
    return longi;
}

// Función: cad_esta_vacia
// Comprueba si una cadena de texto está vacía.
int cad_esta_vacia(char *cad) {
    if (cad[0] == '\0') {
        return 1;
    }
    return 0;
}

// Función: cad_contar_caracter
// Cuenta las ocurrencias de un carácter en una cadena.
int cad_contar_caracter(char *cad, char objetivo) {
    int cuenta = 0;
    int i = 0;
    while (cad[i] != '\0') {
        if (cad[i] == objetivo) {
            cuenta++;
        }
        i++;
    }
    return cuenta;
}

// Función: cad_contiene_caracter
// Comprueba si un carácter existe en una cadena.
int cad_contiene_caracter(char *cad, char objetivo) {
    int i = 0;
    while (cad[i] != '\0') {
        if (cad[i] == objetivo) {
            return 1;
        }
        i++;
    }
    return 0;
}

// Función: cad_es_letra
// Comprueba si un carácter es una letra.
int cad_es_letra(char c) {
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
        return 1;
    }
    return 0;
}

// Función: cad_es_digito
// Comprueba si un carácter es un número.
int cad_es_digito(char c) {
    if (c >= '0' && c <= '9') {
        return 1;
    }
    return 0;
}

// Función: cad_a_mayuscula
// Convierte un carácter a mayúscula.
char cad_a_mayuscula(char c) {
    if (c >= 'a' && c <= 'z') {
        return c - 32;
    }
    return c;
}

// Función: cad_a_minuscula
// Convierte un carácter a minúscula.
char cad_a_minuscula(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c + 32;
    }
    return c;
}

// Función: bit_establecer
// Establece un bit específico en un entero.
int bit_establecer(int num, int posicion) {
    return num | (1 << posicion);
}

// Función: bit_limpiar
// Limpia un bit específico en un entero.
int bit_limpiar(int num, int posicion) {
    return num & ~(1 << posicion);
}

// Función: bit_alternar
// Alterna un bit específico en un entero.
int bit_alternar(int num, int posicion) {
    return num ^ (1 << posicion);
}

// Función: bit_comprobar
// Comprueba si un bit específico está establecido.
int bit_comprobar(int num, int posicion) {
    return (num >> posicion) & 1;
}

// Función: ptr_es_nulo
// Comprueba si un puntero es nulo.
int ptr_es_nulo(void *ptr) {
    if (ptr == 0) {
        return 1;
    }
    return 0;
}

// Función: ptr_intercambiar
// Intercambia dos valores enteros usando punteros.
void ptr_intercambiar(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Función: ptr_incrementar_val
// Incrementa el valor al que se apunta.
void ptr_incrementar_val(int *a) {
    *a = *a + 1;
}

// Función: ptr_decrementar_val
// Decrementa el valor al que se apunta.
void ptr_decrementar_val(int *a) {
    *a = *a - 1;
}

// Función: bool_y
// Realiza AND lógico en dos enteros.
int bool_y(int a, int b) {
    if (a != 0 && b != 0) {
        return 1;
    }
    return 0;
}

// Función: bool_o
// Realiza OR lógico en dos enteros.
int bool_o(int a, int b) {
    if (a != 0 || b != 0) {
        return 1;
    }
    return 0;
}

// Función: bool_no
// Realiza NOT lógico en un entero.
int bool_no(int a) {
    if (a == 0) {
        return 1;
    }
    return 0;
}

// Función: bool_xor
// Realiza XOR lógico en dos enteros.
int bool_xor(int a, int b) {
    int bool_a = (a != 0);
    int bool_b = (b != 0);
    if (bool_a != bool_b) {
        return 1;
    }
    return 0;
}

// Función: math_raiz_cuadrada
// Calcula la raíz cuadrada entera aproximada.
int math_raiz_cuadrada(int n) {
    if (n <= 0) {
        return 0;
    }
    int i = 1;
    while (i * i <= n) {
        i++;
    }
    return i - 1;
}

// Función: math_es_primo
// Comprueba si un número entero es primo.
int math_es_primo(int n) {
    if (n <= 1) {
        return 0;
    }
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}

// Función: math_sumatoria
// Calcula la suma de los primeros n números naturales.
int math_sumatoria(int n) {
    if (n <= 0) {
        return 0;
    }
    return (n * (n + 1)) / 2;
}

// Función: math_progresion_aritmetica
// Calcula el n-ésimo término de una progresión aritmética.
int math_progresion_aritmetica(int primer_termino, int diferencia, int n) {
    if (n < 1) {
        return primer_termino;
    }
    return primer_termino + (n - 1) * diferencia;
}

// Función: math_progresion_geometrica
// Calcula el n-ésimo término de una progresión geométrica.
int math_progresion_geometrica(int primer_termino, int razon, int n) {
    if (n < 1) {
        return primer_termino;
    }
    int resultado = primer_termino;
    for (int i = 1; i < n; i++) {
        resultado = resultado * razon;
    }
    return resultado;
}

// Función: math_porcentaje
// Calcula el porcentaje de una cantidad.
int math_porcentaje(int total, int porcentaje) {
    return (total * porcentaje) / 100;
}

// Función: math_variacion_porcentual
// Calcula la variación porcentual entre dos valores.
int math_variacion_porcentual(int valor_inicial, int valor_final) {
    if (valor_inicial == 0) {
        return 0;
    }
    return ((valor_final - valor_inicial) * 100) / valor_inicial;
}

// Función: math_area_rectangulo
// Calcula el área de un rectángulo.
int math_area_rectangulo(int base, int altura) {
    if (base < 0 || altura < 0) {
        return 0;
    }
    return base * altura;
}

// Función: math_perimetro_rectangulo
// Calcula el perímetro de un rectángulo.
int math_perimetro_rectangulo(int base, int altura) {
    if (base < 0 || altura < 0) {
        return 0;
    }
    return 2 * (base + altura);
}

// Función: math_area_triangulo
// Calcula el área de un triángulo.
int math_area_triangulo(int base, int altura) {
    if (base < 0 || altura < 0) {
        return 0;
    }
    return (base * altura) / 2;
}

// Función: math_perimetro_triangulo
// Calcula el perímetro de un triángulo.
int math_perimetro_triangulo(int lado_a, int lado_b, int lado_c) {
    if (lado_a < 0 || lado_b < 0 || lado_c < 0) {
        return 0;
    }
    return lado_a + lado_b + lado_c;
}

// Función: math_area_cuadrado
// Calcula el área de un cuadrado.
int math_area_cuadrado(int lado) {
    if (lado < 0) {
        return 0;
    }
    return lado * lado;
}

// Función: math_perimetro_cuadrado
// Calcula el perímetro de un cuadrado.
int math_perimetro_cuadrado(int lado) {
    if (lado < 0) {
        return 0;
    }
    return 4 * lado;
}

// Función: math_volumen_cubo
// Calcula el volumen de un cubo.
int math_volumen_cubo(int lado) {
    if (lado < 0) {
        return 0;
    }
    return lado * lado * lado;
}

// Función: math_volumen_prisma
// Calcula el volumen de un prisma rectangular.
int math_volumen_prisma(int largo, int ancho, int alto) {
    if (largo < 0 || ancho < 0 || alto < 0) {
        return 0;
    }
    return largo * ancho * alto;
}

// Función: math_hipotenusa_cuadrado
// Calcula el cuadrado de la hipotenusa de un triángulo rectángulo.
int math_hipotenusa_cuadrado(int cateto_a, int cateto_b) {
    return (cateto_a * cateto_a) + (cateto_b * cateto_b);
}

// Función: math_es_multiplo
// Comprueba si un número es múltiplo de otro.
int math_es_multiplo(int numero, int multiplo) {
    if (multiplo == 0) {
        return numero == 0;
    }
    return (numero % multiplo) == 0;
}

// Función: math_es_divisible
// Comprueba si un número es divisible por otro.
int math_es_divisible(int dividendo, int divisor) {
    if (divisor == 0) {
        return 0;
    }
    return (dividendo % divisor) == 0;
}

// Función: math_es_positivo
// Comprueba si un número es estrictamente positivo.
int math_es_positivo(int numero) {
    return numero > 0;
}

// Función: math_es_negativo
// Comprueba si un número es estrictamente negativo.
int math_es_negativo(int numero) {
    return numero < 0;
}

// Función: math_es_cero
// Comprueba si un número es igual a cero.
int math_es_cero(int numero) {
    return numero == 0;
}

// Función: math_diferencia_absoluta
// Calcula la diferencia absoluta entre dos números.
int math_diferencia_absoluta(int a, int b) {
    int diferencia = a - b;
    if (diferencia < 0) {
        return -diferencia;
    }
    return diferencia;
}

// Función: math_media_armonica_simple
// Calcula la media armónica aproximada de dos enteros.
int math_media_armonica_simple(int a, int b) {
    if (a + b == 0) {
        return 0;
    }
    return (2 * a * b) / (a + b);
}

// Función: math_casi_iguales
// Comprueba si dos números están dentro de un margen de tolerancia.
int math_casi_iguales(int a, int b, int tolerancia) {
    int diferencia = a - b;
    if (diferencia < 0) {
        diferencia = -diferencia;
    }
    return diferencia <= tolerancia;
}

// Función: math_redondear_multiplo
// Redondea un número al múltiplo de m más cercano hacia abajo.
int math_redondear_multiplo(int numero, int multiplo) {
    if (multiplo == 0) {
        return numero;
    }
    return numero - (numero % multiplo);
}

// Función: arr_contar_coincidencias
// Cuenta cuántas veces aparece un valor en un arreglo.
int arr_contar_coincidencias(int arr[], int tamano, int objetivo) {
    int cuenta = 0;
    for (int i = 0; i < tamano; i++) {
        if (arr[i] == objetivo) {
            cuenta++;
        }
    }
    return cuenta;
}

// Función: arr_buscar_ultimo_indice
// Devuelve el último índice donde aparece un valor objetivo.
int arr_buscar_ultimo_indice(int arr[], int tamano, int objetivo) {
    int ultimo_indice = -1;
    for (int i = 0; i < tamano; i++) {
        if (arr[i] == objetivo) {
            ultimo_indice = i;
        }
    }
    return ultimo_indice;
}

// Función: arr_contar_mayores_que
// Cuenta los elementos mayores que un umbral especificado.
int arr_contar_mayores_que(int arr[], int tamano, int umbral) {
    int cuenta = 0;
    for (int i = 0; i < tamano; i++) {
        if (arr[i] > umbral) {
            cuenta++;
        }
    }
    return cuenta;
}

// Función: arr_contar_menores_que
// Cuenta los elementos menores que un umbral especificado.
int arr_contar_menores_que(int arr[], int tamano, int umbral) {
    int cuenta = 0;
    for (int i = 0; i < tamano; i++) {
        if (arr[i] < umbral) {
            cuenta++;
        }
    }
    return cuenta;
}

// Función: arr_contar_en_rango
// Cuenta los elementos que están dentro de un rango.
int arr_contar_en_rango(int arr[], int tamano, int limite_inf, int limite_sup) {
    int cuenta = 0;
    for (int i = 0; i < tamano; i++) {
        if (arr[i] >= limite_inf && arr[i] <= limite_sup) {
            cuenta++;
        }
    }
    return cuenta;
}

// Función: arr_reemplazar_valor
// Reemplaza todas las ocurrencias de un valor viejo por uno nuevo.
void arr_reemplazar_valor(int arr[], int tamano, int valor_viejo, int valor_nuevo) {
    for (int i = 0; i < tamano; i++) {
        if (arr[i] == valor_viejo) {
            arr[i] = valor_nuevo;
        }
    }
}

// Función: arr_clonar_subarreglo
// Copia una porción de un arreglo origen a un arreglo destino.
void arr_clonar_subarreglo(int origen[], int destino[], int inicio, int fin) {
    int indice_destino = 0;
    for (int i = inicio; i <= fin; i++) {
        destino[indice_destino] = origen[i];
        indice_destino++;
    }
}

// Función: arr_rotar_izquierda
// Rota los elementos de un arreglo una posición hacia la izquierda.
void arr_rotar_izquierda(int arr[], int tamano) {
    if (tamano <= 1) {
        return;
    }
    int primer_val = arr[0];
    for (int i = 0; i < tamano - 1; i++) {
        arr[i] = arr[i + 1];
    }
    arr[tamano - 1] = primer_val;
}

// Función: arr_rotar_derecha
// Rota los elementos de un arreglo una posición hacia la derecha.
void arr_rotar_derecha(int arr[], int tamano) {
    if (tamano <= 1) {
        return;
    }
    int ultimo_val = arr[tamano - 1];
    for (int i = tamano - 1; i > 0; i--) {
        arr[i] = arr[i - 1];
    }
    arr[0] = ultimo_val;
}

// Función: arr_ordenar_burbuja
// Ordena un arreglo en orden ascendente usando el método de burbuja.
void arr_ordenar_burbuja(int arr[], int tamano) {
    for (int i = 0; i < tamano - 1; i++) {
        for (int j = 0; j < tamano - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Función: arr_ordenar_seleccion
// Ordena un arreglo en orden ascendente usando selección.
void arr_ordenar_seleccion(int arr[], int tamano) {
    for (int i = 0; i < tamano - 1; i++) {
        int indice_min = i;
        for (int j = i + 1; j < tamano; j++) {
            if (arr[j] < arr[indice_min]) {
                indice_min = j;
            }
        }
        int temp = arr[i];
        arr[i] = arr[indice_min];
        arr[indice_min] = temp;
    }
}

// Función: arr_ordenar_insercion
// Ordena un arreglo en orden ascendente usando inserción.
void arr_ordenar_insercion(int arr[], int tamano) {
    for (int i = 1; i < tamano; i++) {
        int clave = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > clave) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = clave;
    }
}

// Función: arr_busqueda_binaria
// Busca un valor en un arreglo ordenado usando búsqueda binaria.
int arr_busqueda_binaria(int arr[], int tamano, int objetivo) {
    int inicio = 0;
    int fin = tamano - 1;
    while (inicio <= fin) {
        int medio = inicio + (fin - inicio) / 2;
        if (arr[medio] == objetivo) {
            return medio;
        }
        if (arr[medio] < objetivo) {
            inicio = medio + 1;
        } else {
            fin = medio - 1;
        }
    }
    return -1;
}

// Función: arr_son_iguales
// Comprueba si dos arreglos tienen los mismos elementos en el mismo orden.
int arr_son_iguales(int arr_a[], int arr_b[], int tamano) {
    for (int i = 0; i < tamano; i++) {
        if (arr_a[i] != arr_b[i]) {
            return 0;
        }
    }
    return 1;
}

// Función: arr_producto_punto
// Calcula el producto punto de dos arreglos.
int arr_producto_punto(int arr_a[], int arr_b[], int tamano) {
    int producto = 0;
    for (int i = 0; i < tamano; i++) {
        producto = producto + (arr_a[i] * arr_b[i]);
    }
    return producto;
}

// Función: arr_sumar_vectores
// Suma dos arreglos elemento por elemento y guarda el resultado.
void arr_sumar_vectores(int arr_a[], int arr_b[], int destino[], int tamano) {
    for (int i = 0; i < tamano; i++) {
        destino[i] = arr_a[i] + arr_b[i];
    }
}

// Función: arr_restar_vectores
// Resta dos arreglos elemento por elemento y guarda el resultado.
void arr_restar_vectores(int arr_a[], int arr_b[], int destino[], int tamano) {
    for (int i = 0; i < tamano; i++) {
        destino[i] = arr_a[i] - arr_b[i];
    }
}

// Función: arr_multiplicar_vectores
// Multiplica dos arreglos elemento por elemento y guarda el resultado.
void arr_multiplicar_vectores(int arr_a[], int arr_b[], int destino[], int tamano) {
    for (int i = 0; i < tamano; i++) {
        destino[i] = arr_a[i] * arr_b[i];
    }
}

// Función: arr_diferencia_maxima
// Encuentra la mayor diferencia entre dos elementos adyacentes.
int arr_diferencia_maxima(int arr[], int tamano) {
    if (tamano < 2) {
        return 0;
    }
    int dif_max = 0;
    for (int i = 0; i < tamano - 1; i++) {
        int dif = arr[i + 1] - arr[i];
        if (dif < 0) {
            dif = -dif;
        }
        if (dif > dif_max) {
            dif_max = dif;
        }
    }
    return dif_max;
}

// Función: arr_tiene_duplicados
// Comprueba si hay al menos un elemento duplicado en el arreglo.
int arr_tiene_duplicados(int arr[], int tamano) {
    for (int i = 0; i < tamano - 1; i++) {
        for (int j = i + 1; j < tamano; j++) {
            if (arr[i] == arr[j]) {
                return 1;
            }
        }
    }
    return 0;
}

// Función: arr_frecuencia_maxima
// Encuentra la frecuencia del elemento que más se repite.
int arr_frecuencia_maxima(int arr[], int tamano) {
    int max_frecuencia = 0;
    for (int i = 0; i < tamano; i++) {
        int frecuencia = 0;
        for (int j = 0; j < tamano; j++) {
            if (arr[i] == arr[j]) {
                frecuencia++;
            }
        }
        if (frecuencia > max_frecuencia) {
            max_frecuencia = frecuencia;
        }
    }
    return max_frecuencia;
}

// Función: arr_eliminar_elemento
// Desplaza elementos para sobrescribir un índice específico.
void arr_eliminar_elemento(int arr[], int tamano, int indice) {
    if (indice < 0 || indice >= tamano) {
        return;
    }
    for (int i = indice; i < tamano - 1; i++) {
        arr[i] = arr[i + 1];
    }
    arr[tamano - 1] = 0;
}

// Función: arr_insertar_elemento
// Desplaza elementos e inserta un valor en un índice específico.
void arr_insertar_elemento(int arr[], int tamano, int indice, int valor) {
    if (indice < 0 || indice >= tamano) {
        return;
    }
    for (int i = tamano - 1; i > indice; i--) {
        arr[i] = arr[i - 1];
    }
    arr[indice] = valor;
}

// Función: arr_mediana_ordenado
// Devuelve el elemento central de un arreglo previamente ordenado.
int arr_mediana_ordenado(int arr[], int tamano) {
    if (tamano == 0) {
        return 0;
    }
    return arr[tamano / 2];
}

// Función: arr_rango_valores
// Calcula la diferencia entre el valor máximo y el valor mínimo del arreglo.
int arr_rango_valores(int arr[], int tamano) {
    if (tamano == 0) {
        return 0;
    }
    int val_min = arr[0];
    int val_max = arr[0];
    for (int i = 1; i < tamano; i++) {
        if (arr[i] < val_min) {
            val_min = arr[i];
        }
        if (arr[i] > val_max) {
            val_max = arr[i];
        }
    }
    return val_max - val_min;
}

// Función: str_copiar
// Copia el contenido de una cadena origen a una cadena destino.
void str_copiar(char *origen, char *destino) {
    int i = 0;
    while (origen[i] != '\0') {
        destino[i] = origen[i];
        i++;
    }
    destino[i] = '\0';
}

// Función: str_concatenar
// Agrega el contenido de una cadena al final de otra cadena destino.
void str_concatenar(char *destino, char *origen) {
    int i = 0;
    while (destino[i] != '\0') {
        i++;
    }
    int j = 0;
    while (origen[j] != '\0') {
        destino[i] = origen[j];
        i++;
        j++;
    }
    destino[i] = '\0';
}

// Función: str_comparar
// Compara dos cadenas alfabéticamente.
int str_comparar(char *cad_a, char *cad_b) {
    int i = 0;
    while (cad_a[i] != '\0' && cad_b[i] != '\0') {
        if (cad_a[i] != cad_b[i]) {
            return cad_a[i] - cad_b[i];
        }
        i++;
    }
    return cad_a[i] - cad_b[i];
}

// Función: str_son_iguales
// Comprueba si dos cadenas son exactamente iguales.
int str_son_iguales(char *cad_a, char *cad_b) {
    int i = 0;
    while (cad_a[i] != '\0' && cad_b[i] != '\0') {
        if (cad_a[i] != cad_b[i]) {
            return 0;
        }
        i++;
    }
    if (cad_a[i] == '\0' && cad_b[i] == '\0') {
        return 1;
    }
    return 0;
}

// Función: str_invertir
// Invierte los caracteres de una cadena en su propio lugar.
void str_invertir(char *cad) {
    int longi = 0;
    while (cad[longi] != '\0') {
        longi++;
    }
    int inicio = 0;
    int fin = longi - 1;
    while (inicio < fin) {
        char temp = cad[inicio];
        cad[inicio] = cad[fin];
        cad[fin] = temp;
        inicio++;
        fin--;
    }
}

// Función: str_a_mayusculas
// Convierte todos los caracteres de una cadena a mayúsculas.
void str_a_mayusculas(char *cad) {
    int i = 0;
    while (cad[i] != '\0') {
        if (cad[i] >= 'a' && cad[i] <= 'z') {
            cad[i] = cad[i] - 32;
        }
        i++;
    }
}

// Función: str_a_minusculas
// Convierte todos los caracteres de una cadena a minúsculas.
void str_a_minusculas(char *cad) {
    int i = 0;
    while (cad[i] != '\0') {
        if (cad[i] >= 'A' && cad[i] <= 'Z') {
            cad[i] = cad[i] + 32;
        }
        i++;
    }
}

// Función: str_reemplazar_caracter
// Reemplaza un carácter específico por otro en toda la cadena.
void str_reemplazar_caracter(char *cad, char viejo, char nuevo) {
    int i = 0;
    while (cad[i] != '\0') {
        if (cad[i] == viejo) {
            cad[i] = nuevo;
        }
        i++;
    }
}

// Función: str_limpiar_espacios
// Reemplaza espacios por guiones bajos en una cadena.
void str_limpiar_espacios(char *cad) {
    int i = 0;
    while (cad[i] != '\0') {
        if (cad[i] == ' ') {
            cad[i] = '_';
        }
        i++;
    }
}

// Función: str_contar_vocales
// Cuenta el número de vocales en una cadena.
int str_contar_vocales(char *cad) {
    int cuenta = 0;
    int i = 0;
    while (cad[i] != '\0') {
        char c = cad[i];
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
            c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') {
            cuenta++;
        }
        i++;
    }
    return cuenta;
}

// Función: str_contar_consonantes
// Cuenta el número de consonantes en una cadena.
int str_contar_consonantes(char *cad) {
    int cuenta = 0;
    int i = 0;
    while (cad[i] != '\0') {
        char c = cad[i];
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
            if (!(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
                  c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U')) {
                cuenta++;
            }
        }
        i++;
    }
    return cuenta;
}

// Función: str_contar_espacios
// Cuenta cuántos espacios en blanco hay en una cadena.
int str_contar_espacios(char *cad) {
    int cuenta = 0;
    int i = 0;
    while (cad[i] != '\0') {
        if (cad[i] == ' ') {
            cuenta++;
        }
        i++;
    }
    return cuenta;
}

// Función: str_contar_digitos
// Cuenta cuántos caracteres numéricos hay en una cadena.
int str_contar_digitos(char *cad) {
    int cuenta = 0;
    int i = 0;
    while (cad[i] != '\0') {
        if (cad[i] >= '0' && cad[i] <= '9') {
            cuenta++;
        }
        i++;
    }
    return cuenta;
}

// Función: str_contar_letras
// Cuenta cuántos caracteres alfabéticos hay en una cadena.
int str_contar_letras(char *cad) {
    int cuenta = 0;
    int i = 0;
    while (cad[i] != '\0') {
        char c = cad[i];
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
            cuenta++;
        }
        i++;
    }
    return cuenta;
}

// Función: str_es_palindromo
// Comprueba si una cadena se lee igual de izquierda a derecha que al revés.
int str_es_palindromo(char *cad) {
    int longi = 0;
    while (cad[longi] != '\0') {
        longi++;
    }
    int inicio = 0;
    int fin = longi - 1;
    while (inicio < fin) {
        if (cad[inicio] != cad[fin]) {
            return 0;
        }
        inicio++;
        fin--;
    }
    return 1;
}

// Función: str_buscar_caracter
// Devuelve el primer índice donde aparece un carácter.
int str_buscar_caracter(char *cad, char objetivo) {
    int i = 0;
    while (cad[i] != '\0') {
        if (cad[i] == objetivo) {
            return i;
        }
        i++;
    }
    return -1;
}

// Función: str_buscar_ultimo_caracter
// Devuelve el último índice donde aparece un carácter.
int str_buscar_ultimo_caracter(char *cad, char objetivo) {
    int ultimo_indice = -1;
    int i = 0;
    while (cad[i] != '\0') {
        if (cad[i] == objetivo) {
            ultimo_indice = i;
        }
        i++;
    }
    return ultimo_indice;
}

// Función: str_prefijo
// Comprueba si una cadena comienza con un prefijo específico.
int str_prefijo(char *cad, char *prefijo) {
    int i = 0;
    while (prefijo[i] != '\0') {
        if (cad[i] == '\0' || cad[i] != prefijo[i]) {
            return 0;
        }
        i++;
    }
    return 1;
}

// Función: str_sufijo
// Comprueba si una cadena termina con un sufijo específico.
int str_sufijo(char *cad, char *sufijo) {
    int long_cad = 0;
    while (cad[long_cad] != '\0') {
        long_cad++;
    }
    int long_suf = 0;
    while (sufijo[long_suf] != '\0') {
        long_suf++;
    }
    if (long_suf > long_cad) {
        return 0;
    }
    int inicio = long_cad - long_suf;
    for (int i = 0; i < long_suf; i++) {
        if (cad[inicio + i] != sufijo[i]) {
            return 0;
        }
    }
    return 1;
}

// Función: str_recortar_fin
// Elimina los espacios en blanco al final de una cadena.
void str_recortar_fin(char *cad) {
    int longi = 0;
    while (cad[longi] != '\0') {
        longi++;
    }
    while (longi > 0 && cad[longi - 1] == ' ') {
        longi--;
        cad[longi] = '\0';
    }
}

// Función: char_es_vocal
// Comprueba si un carácter individual es una vocal.
int char_es_vocal(char c) {
    if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
        c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') {
        return 1;
    }
    return 0;
}

// Función: char_es_consonante
// Comprueba si un carácter individual es una consonante.
int char_es_consonante(char c) {
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
        if (!char_es_vocal(c)) {
            return 1;
        }
    }
    return 0;
}

// Función: char_es_espacio
// Comprueba si un carácter es un espacio en blanco o tabulación.
int char_es_espacio(char c) {
    if (c == ' ' || c == '\t' || c == '\n' || c == '\r') {
        return 1;
    }
    return 0;
}

// Función: char_es_alfanumerico
// Comprueba si un carácter es letra o dígito.
int char_es_alfanumerico(char c) {
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')) {
        return 1;
    }
    return 0;
}

// Función: char_a_entero
// Convierte un carácter numérico a su valor entero.
int char_a_entero(char c) {
    if (c >= '0' && c <= '9') {
        return c - '0';
    }
    return -1;
}

// Función: bit_conteo_unos
// Cuenta cuántos bits están establecidos en 1 en un entero.
int bit_conteo_unos(int num) {
    int cuenta = 0;
    unsigned int u_num = (unsigned int)num;
    while (u_num > 0) {
        if (u_num & 1) {
            cuenta++;
        }
        u_num = u_num >> 1;
    }
    return cuenta;
}

// Función: bit_conteo_ceros
// Cuenta cuántos bits están en 0 en los 32 bits de un entero.
int bit_conteo_ceros(int num) {
    int cuenta = 0;
    unsigned int u_num = (unsigned int)num;
    for (int i = 0; i < 32; i++) {
        if ((u_num & 1) == 0) {
            cuenta++;
        }
        u_num = u_num >> 1;
    }
    return cuenta;
}

// Función: bit_desplazar_izquierda
// Desplaza los bits de un número hacia la izquierda.
int bit_desplazar_izquierda(int num, int posiciones) {
    return num << posiciones;
}

// Función: bit_desplazar_derecha
// Desplaza los bits de un número hacia la derecha.
int bit_desplazar_derecha(int num, int posiciones) {
    return num >> posiciones;
}

// Función: bit_mas_significativo
// Encuentra la posición del bit 1 más significativo.
int bit_mas_significativo(int num) {
    if (num == 0) {
        return -1;
    }
    unsigned int u_num = (unsigned int)num;
    int posicion = 0;
    while (u_num > 1) {
        u_num = u_num >> 1;
        posicion++;
    }
    return posicion;
}

// Función: bit_menos_significativo
// Encuentra la posición del bit 1 menos significativo.
int bit_menos_significativo(int num) {
    if (num == 0) {
        return -1;
    }
    unsigned int u_num = (unsigned int)num;
    int posicion = 0;
    while ((u_num & 1) == 0) {
        u_num = u_num >> 1;
        posicion++;
    }
    return posicion;
}

// Función: bit_es_potencia_de_dos
// Comprueba si un entero positivo es una potencia de dos.
int bit_es_potencia_de_dos(int num) {
    if (num <= 0) {
        return 0;
    }
    return (num & (num - 1)) == 0;
}

// Función: bit_mascara_inferior
// Genera una máscara con los n bits inferiores establecidos en 1.
int bit_mascara_inferior(int n) {
    if (n <= 0) {
        return 0;
    }
    if (n >= 32) {
        return -1;
    }
    return (1 << n) - 1;
}

// Función: bit_combinar
// Combina los 16 bits inferiores de dos números en un solo entero.
int bit_combinar(int parte_alta, int parte_baja) {
    int alta_limpia = parte_alta & 0xFFFF;
    int baja_limpia = parte_baja & 0xFFFF;
    return (alta_limpia << 16) | baja_limpia;
}

// Función: bit_extraer_rango
// Extrae un rango de bits especificado de un número entero.
int bit_extraer_rango(int num, int inicio, int longitud) {
    int mascara = (1 << longitud) - 1;
    return (num >> inicio) & mascara;
}

// Función: ptr_sumar_desplazamiento
// Suma un desplazamiento a un puntero entero y devuelve el nuevo puntero.
int *ptr_sumar_desplazamiento(int *ptr, int desplazamiento) {
    return ptr + desplazamiento;
}

// Función: ptr_asignar_valor
// Asigna un valor entero a la dirección de memoria apuntada.
void ptr_asignar_valor(int *ptr, int valor) {
    *ptr = valor;
}

// Función: ptr_obtener_valor
// Devuelve el valor entero almacenado en la dirección apuntada.
int ptr_obtener_valor(int *ptr) {
    return *ptr;
}

// Función: ptr_son_direcciones_iguales
// Comprueba si dos punteros apuntan a la misma dirección de memoria.
int ptr_son_direcciones_iguales(int *ptr_a, int *ptr_b) {
    if (ptr_a == ptr_b) {
        return 1;
    }
    return 0;
}

// Función: ptr_copiar_valor
// Copia el valor de una dirección de memoria a otra.
void ptr_copiar_valor(int *origen, int *destino) {
    *destino = *origen;
}

// Función: bool_equivalencia
// Comprueba si dos valores de verdad son equivalentes.
int bool_equivalencia(int a, int b) {
    int bool_a = (a != 0);
    int bool_b = (b != 0);
    if (bool_a == bool_b) {
        return 1;
    }
    return 0;
}

// Función: bool_implicacion
// Realiza la implicación lógica.
int bool_implicacion(int a, int b) {
    int bool_a = (a != 0);
    int bool_b = (b != 0);
    if (bool_a == 0 || bool_b != 0) {
        return 1;
    }
    return 0;
}

// Función: bool_nand
// Realiza la operación NAND lógica entre dos enteros.
int bool_nand(int a, int b) {
    if (a != 0 && b != 0) {
        return 0;
    }
    return 1;
}

// Función: bool_nor
// Realiza la operación NOR lógica entre dos enteros.
int bool_nor(int a, int b) {
    if (a != 0 || b != 0) {
        return 0;
    }
    return 1;
}

// Función: bool_mayoria
// Devuelve 1 si la mayoría de tres valores booleanos son verdaderos.
int bool_mayoria(int a, int b, int c) {
    int cuenta = 0;
    if (a != 0) {
        cuenta++;
    }
    if (b != 0) {
        cuenta++;
    }
    if (c != 0) {
        cuenta++;
    }
    if (cuenta >= 2) {
        return 1;
    }
    return 0;
}

// Función: bool_al_menos_uno
// Devuelve 1 si al menos uno de tres valores booleanos es verdadero.
int bool_al_menos_uno(int a, int b, int c) {
    if (a != 0 || b != 0 || c != 0) {
        return 1;
    }
    return 0;
}

// Función: bool_todos_verdaderos
// Devuelve 1 si tres valores booleanos son todos verdaderos.
int bool_todos_verdaderos(int a, int b, int c) {
    if (a != 0 && b != 0 && c != 0) {
        return 1;
    }
    return 0;
}

// Función: mem_establecer_bloque
// Establece un valor en un bloque de memoria simulado con un arreglo.
void mem_establecer_bloque(int bloque[], int tamano, int valor) {
    for (int i = 0; i < tamano; i++) {
        bloque[i] = valor;
    }
}

// Función: mem_copiar_bloque
// Copia datos de un bloque origen a un destino simulado con arreglos.
void mem_copiar_bloque(int origen[], int destino[], int tamano) {
    for (int i = 0; i < tamano; i++) {
        destino[i] = origen[i];
    }
}

// Función: mem_comparar_bloque
// Compara dos bloques de memoria simulados entero a entero.
int mem_comparar_bloque(int bloque_a[], int bloque_b[], int tamano) {
    for (int i = 0; i < tamano; i++) {
        if (bloque_a[i] != bloque_b[i]) {
            return bloque_a[i] - bloque_b[i];
        }
    }
    return 0;
}

// Función: math_area_rombo
// Calcula el área de un rombo.
int math_area_rombo(int diagonal_mayor, int diagonal_menor) {
    if (diagonal_mayor < 0 || diagonal_menor < 0) {
        return 0;
    }
    return (diagonal_mayor * diagonal_menor) / 2;
}

// Función: math_area_trapecio
// Calcula el área de un trapecio.
int math_area_trapecio(int base_mayor, int base_menor, int altura) {
    if (base_mayor < 0 || base_menor < 0 || altura < 0) {
        return 0;
    }
    return (((base_mayor + base_menor) * altura) / 2);
}

// Función: math_perimetro_rombo
// Calcula el perímetro de un rombo.
int math_perimetro_rombo(int lado) {
    if (lado < 0) {
        return 0;
    }
    return 4 * lado;
}

// Función: math_perimetro_trapecio
// Calcula el perímetro de un trapecio.
int math_perimetro_trapecio(int base_mayor, int base_menor, int lado_a, int lado_b) {
    if (base_mayor < 0 || base_menor < 0 || lado_a < 0 || lado_b < 0) {
        return 0;
    }
    return base_mayor + base_menor + lado_a + lado_b;
}

// Función: math_volumen_cilindro_aprox
// Calcula el volumen aproximado de un cilindro usando pi como 3.
int math_volumen_cilindro_aprox(int radio, int altura) {
    if (radio < 0 || altura < 0) {
        return 0;
    }
    return 3 * radio * radio * altura;
}

// Función: math_volumen_esfera_aprox
// Calcula el volumen aproximado de una esfera usando pi como 3.
int math_volumen_esfera_aprox(int radio) {
    if (radio < 0) {
        return 0;
    }
    return (4 * 3 * radio * radio * radio) / 3;
}

// Función: math_area_circulo_aprox
// Calcula el área aproximada de un círculo usando pi como 3.
int math_area_circulo_aprox(int radio) {
    if (radio < 0) {
        return 0;
    }
    return 3 * radio * radio;
}

// Función: math_perimetro_circulo_aprox
// Calcula el perímetro aproximado de un círculo usando pi como 3.
int math_perimetro_circulo_aprox(int radio) {
    if (radio < 0) {
        return 0;
    }
    return 2 * 3 * radio;
}

// Función: math_area_pentagono
// Calcula el área de un pentágono regular.
int math_area_pentagono(int perimetro, int apotema) {
    if (perimetro < 0 || apotema < 0) {
        return 0;
    }
    return (perimetro * apotema) / 2;
}

// Función: math_area_hexagono
// Calcula el área de un hexágono regular.
int math_area_hexagono(int perimetro, int apotema) {
    if (perimetro < 0 || apotema < 0) {
        return 0;
    }
    return (perimetro * apotema) / 2;
}

// Función: math_suma_angulos_internos
// Calcula la suma de los ángulos internos de un polígono de n lados.
int math_suma_angulos_internos(int n) {
    if (n < 3) {
        return 0;
    }
    return (n - 2) * 180;
}

// Función: math_angulo_interno_regular
// Calcula el ángulo interno de un polígono regular de n lados.
int math_angulo_interno_regular(int n) {
    if (n < 3) {
        return 0;
    }
    return ((n - 2) * 180) / n;
}

// Función: math_numero_diagonales
// Calcula el número de diagonales de un polígono de n lados.
int math_numero_diagonales(int n) {
    if (n < 3) {
        return 0;
    }
    return (n * (n - 3)) / 2;
}

// Función: math_es_cuadrado_perfecto
// Comprueba si un número entero es un cuadrado perfecto.
int math_es_cuadrado_perfecto(int n) {
    if (n < 0) {
        return 0;
    }
    for (int i = 0; i * i <= n; i++) {
        if (i * i == n) {
            return 1;
        }
    }
    return 0;
}

// Función: math_es_cubo_perfecto
// Comprueba si un número entero es un cubo perfecto.
int math_es_cubo_perfecto(int n) {
    if (n < 0) {
        n = -n;
    }
    for (int i = 0; i * i * i <= n; i++) {
        if (i * i * i == n) {
            return 1;
        }
    }
    return 0;
}

// Función: math_discriminante_cuadradico
// Calcula el discriminante de una ecuación de segundo grado.
int math_discriminante_cuadradico(int a, int b, int c) {
    return (b * b) - (4 * a * c);
}

// Función: math_tiene_raices_reales
// Comprueba si una ecuación cuadrática tiene raíces reales.
int math_tiene_raices_reales(int a, int b, int c) {
    int disc = math_discriminante_cuadradico(a, b, c);
    return disc >= 0;
}

// Función: math_interes_simple
// Calcula el interés simple acumulado.
int math_interes_simple(int capital, int tasa, int tiempo) {
    if (capital < 0 || tasa < 0 || tiempo < 0) {
        return 0;
    }
    return (capital * tasa * tiempo) / 100;
}

// Función: math_monto_total_simple
// Calcula el monto total con interés simple.
int math_monto_total_simple(int capital, int tasa, int tiempo) {
    int interes = math_interes_simple(capital, tasa, tiempo);
    return capital + interes;
}

// Función: math_descuento_comercial
// Calcula el precio final tras aplicar un porcentaje de descuento.
int math_descuento_comercial(int precio, int descuento) {
    if (precio < 0 || descuento < 0 || descuento > 100) {
        return precio;
    }
    return precio - ((precio * descuento) / 100);
}

// Función: math_ganancia_neta
// Calcula la ganancia neta restando costos de ingresos.
int math_ganancia_neta(int ingresos, int costos) {
    return ingresos - costos;
}

// Función: math_es_rentable
// Comprueba si los ingresos superan estrictamente a los costos.
int math_es_rentable(int ingresos, int costos) {
    return ingresos > costos;
}

// Función: math_punto_equilibrio
// Calcula la cantidad de unidades para el punto de equilibrio.
int math_punto_equilibrio(int costos_fijos, int precio_venta, int costo_variable) {
    int margen = precio_venta - costo_variable;
    if (margen <= 0) {
        return 0;
    }
    return costos_fijos / margen;
}

// Función: stat_rango_intercuartilico
// Calcula la diferencia entre el tercer y primer cuartil.
int stat_rango_intercuartilico(int q3, int q1) {
    return q3 - q1;
}

// Función: stat_coeficiente_variacion
// Calcula el coeficiente de variación porcentual aproximado.
int stat_coeficiente_variacion(int desviacion, int media) {
    if (media == 0) {
        return 0;
    }
    return (desviacion * 100) / media;
}

// Función: arr_segundo_maximo
// Encuentra el segundo valor más grande en un arreglo.
int arr_segundo_maximo(int arr[], int tamano) {
    if (tamano < 2) {
        return 0;
    }
    int max1 = arr[0];
    int max2 = arr[1];
    if (max2 > max1) {
        max1 = arr[1];
        max2 = arr[0];
    }
    for (int i = 2; i < tamano; i++) {
        if (arr[i] > max1) {
            max2 = max1;
            max1 = arr[i];
        } else if (arr[i] > max2) {
            max2 = arr[i];
        }
    }
    return max2;
}

// Función: arr_segundo_minimo
// Encuentra el segundo valor más pequeño en un arreglo.
int arr_segundo_minimo(int arr[], int tamano) {
    if (tamano < 2) {
        return 0;
    }
    int min1 = arr[0];
    int min2 = arr[1];
    if (min2 < min1) {
        min1 = arr[1];
        min2 = arr[0];
    }
    for (int i = 2; i < tamano; i++) {
        if (arr[i] < min1) {
            min2 = min1;
            min1 = arr[i];
        } else if (arr[i] < min2) {
            min2 = arr[i];
        }
    }
    return min2;
}

// Función: arr_desplazar_izquierda_cero
// Desplaza elementos a la izquierda rellenando con cero al final.
void arr_desplazar_izquierda_cero(int arr[], int tamano) {
    if (tamano <= 1) {
        return;
    }
    for (int i = 0; i < tamano - 1; i++) {
        arr[i] = arr[i + 1];
    }
    arr[tamano - 1] = 0;
}

// Función: arr_desplazar_derecha_cero
// Desplaza elementos a la derecha rellenando con cero al inicio.
void arr_desplazar_derecha_cero(int arr[], int tamano) {
    if (tamano <= 1) {
        return;
    }
    for (int i = tamano - 1; i > 0; i--) {
        arr[i] = arr[i - 1];
    }
    arr[0] = 0;
}

// Función: arr_multiplicar_elementos
// Calcula el producto de todos los elementos de un arreglo.
int arr_multiplicar_elementos(int arr[], int tamano) {
    int producto = 1;
    for (int i = 0; i < tamano; i++) {
        producto = producto * arr[i];
    }
    return producto;
}

// Función: arr_contar_positivos
// Cuenta cuántos números estrictamente positivos hay en un arreglo.
int arr_contar_positivos(int arr[], int tamano) {
    int cuenta = 0;
    for (int i = 0; i < tamano; i++) {
        if (arr[i] > 0) {
            cuenta++;
        }
    }
    return cuenta;
}

// Función: arr_contar_negativos
// Cuenta cuántos números estrictamente negativos hay en un arreglo.
int arr_contar_negativos(int arr[], int tamano) {
    int cuenta = 0;
    for (int i = 0; i < tamano; i++) {
        if (arr[i] < 0) {
            cuenta++;
        }
    }
    return cuenta;
}

// Función: arr_contar_ceros
// Cuenta cuántos ceros hay en un arreglo.
int arr_contar_ceros(int arr[], int tamano) {
    int cuenta = 0;
    for (int i = 0; i < tamano; i++) {
        if (arr[i] == 0) {
            cuenta++;
        }
    }
    return cuenta;
}

// Función: arr_suma_pares_indices
// Suma los elementos que se encuentran en índices pares.
int arr_suma_pares_indices(int arr[], int tamano) {
    int suma = 0;
    for (int i = 0; i < tamano; i = i + 2) {
        suma = suma + arr[i];
    }
    return suma;
}

// Función: arr_suma_impares_indices
// Suma los elementos que se encuentran en índices impares.
int arr_suma_impares_indices(int arr[], int tamano) {
    int suma = 0;
    for (int i = 1; i < tamano; i = i + 2) {
        suma = suma + arr[i];
    }
    return suma;
}

// Función: arr_alternar_signos
// Multiplica por -1 los elementos en índices impares.
void arr_alternar_signos(int arr[], int tamano) {
    for (int i = 1; i < tamano; i = i + 2) {
        arr[i] = -arr[i];
    }
}

// Función: arr_primer_indice_positivo
// Devuelve el primer índice con un valor positivo.
int arr_primer_indice_positivo(int arr[], int tamano) {
    for (int i = 0; i < tamano; i++) {
        if (arr[i] > 0) {
            return i;
        }
    }
    return -1;
}

// Función: arr_primer_indice_negativo
// Devuelve el primer índice con un valor negativo.
int arr_primer_indice_negativo(int arr[], int tamano) {
    for (int i = 0; i < tamano; i++) {
        if (arr[i] < 0) {
            return i;
        }
    }
    return -1;
}

// Función: arr_ultimo_indice_positivo
// Devuelve el último índice con un valor positivo.
int arr_ultimo_indice_positivo(int arr[], int tamano) {
    for (int i = tamano - 1; i >= 0; i--) {
        if (arr[i] > 0) {
            return i;
        }
    }
    return -1;
}

// Función: arr_ultimo_indice_negativo
// Devuelve el último índice con un valor negativo.
int arr_ultimo_indice_negativo(int arr[], int tamano) {
    for (int i = tamano - 1; i >= 0; i--) {
        if (arr[i] < 0) {
            return i;
        }
    }
    return -1;
}

// Función: arr_es_simetrico
// Comprueba si el arreglo es simétrico.
int arr_es_simetrico(int arr[], int tamano) {
    int inicio = 0;
    int fin = tamano - 1;
    while (inicio < fin) {
        if (arr[inicio] != arr[fin]) {
            return 0;
        }
        inicio++;
        fin--;
    }
    return 1;
}

// Función: arr_fusionar_ordenados
// Fusiona dos arreglos ordenados en un tercer arreglo destino.
void arr_fusionar_ordenados(int arr_a[], int tam_a, int arr_b[], int tam_b, int destino[]) {
    int i = 0;
    int j = 0;
    int k = 0;
    while (i < tam_a && j < tam_b) {
        if (arr_a[i] < arr_b[j]) {
            destino[k] = arr_a[i];
            i++;
        } else {
            destino[k] = arr_b[j];
            j++;
        }
        k++;
    }
    while (i < tam_a) {
        destino[k] = arr_a[i];
        i++;
        k++;
    }
    while (j < tam_b) {
        destino[k] = arr_b[j];
        j++;
        k++;
    }
}

// Función: arr_interseccion_conteo
// Cuenta cuántos elementos en común tienen dos arreglos.
int arr_interseccion_conteo(int arr_a[], int tam_a, int arr_b[], int tam_b) {
    int cuenta = 0;
    for (int i = 0; i < tam_a; i++) {
        int encontrado = 0;
        for (int j = 0; j < tam_b; j++) {
            if (arr_a[i] == arr_b[j]) {
                encontrado = 1;
            }
        }
        if (encontrado != 0) {
            cuenta++;
        }
    }
    return cuenta;
}

// Función: arr_diferencia_conteo
// Cuenta cuántos elementos del primer arreglo no están en el segundo.
int arr_diferencia_conteo(int arr_a[], int tam_a, int arr_b[], int tam_b) {
    int cuenta = 0;
    for (int i = 0; i < tam_a; i++) {
        int encontrado = 0;
        for (int j = 0; j < tam_b; j++) {
            if (arr_a[i] == arr_b[j]) {
                encontrado = 1;
            }
        }
        if (encontrado == 0) {
            cuenta++;
        }
    }
    return cuenta;
}

// Función: arr_subarreglo_suma_maxima
// Calcula la suma máxima de un subarreglo contiguo.
int arr_subarreglo_suma_maxima(int arr[], int tamano) {
    if (tamano == 0) {
        return 0;
    }
    int max_actual = arr[0];
    int max_global = arr[0];
    for (int i = 1; i < tamano; i++) {
        if (arr[i] > max_actual + arr[i]) {
            max_actual = arr[i];
        } else {
            max_actual = max_actual + arr[i];
        }
        if (max_actual > max_global) {
            max_global = max_actual;
        }
    }
    return max_global;
}

// Función: mat_diagonal_principal_suma
// Suma los elementos de la diagonal principal de una matriz cuadrada.
int mat_diagonal_principal_suma(int mat[], int n) {
    int suma = 0;
    for (int i = 0; i < n; i++) {
        suma = suma + mat[i * n + i];
    }
    return suma;
}

// Función: mat_diagonal_secundaria_suma
// Suma los elementos de la diagonal secundaria de una matriz cuadrada.
int mat_diagonal_secundaria_suma(int mat[], int n) {
    int suma = 0;
    for (int i = 0; i < n; i++) {
        suma = suma + mat[i * n + (n - 1 - i)];
    }
    return suma;
}

// Función: mat_suma_total
// Suma todos los elementos de una matriz.
int mat_suma_total(int mat[], int filas, int columnas) {
    int suma = 0;
    int total = filas * columnas;
    for (int i = 0; i < total; i++) {
        suma = suma + mat[i];
    }
    return suma;
}

// Función: mat_es_matriz_cero
// Comprueba si todos los elementos de una matriz son cero.
int mat_es_matriz_cero(int mat[], int filas, int columnas) {
    int total = filas * columnas;
    for (int i = 0; i < total; i++) {
        if (mat[i] != 0) {
            return 0;
        }
    }
    return 1;
}

// Función: mat_es_identidad
// Comprueba si una matriz cuadrada es una matriz identidad.
int mat_es_identidad(int mat[], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int indice = i * n + j;
            if (i == j) {
                if (mat[indice] != 1) {
                    return 0;
                }
            } else {
                if (mat[indice] != 0) {
                    return 0;
                }
            }
        }
    }
    return 1;
}

// Función: str_contar_subcadenas
// Cuenta cuántas veces aparece una subcadena en una cadena principal.
int str_contar_subcadenas(char *cad, char *sub) {
    int cuenta = 0;
    int i = 0;
    int long_sub = 0;
    while (sub[long_sub] != '\0') {
        long_sub++;
    }
    if (long_sub == 0) {
        return 0;
    }
    while (cad[i] != '\0') {
        int coincidencia = 1;
        for (int j = 0; j < long_sub; j++) {
            if (cad[i + j] == '\0' || cad[i + j] != sub[j]) {
                coincidencia = 0;
            }
        }
        if (coincidencia != 0) {
            cuenta++;
            i = i + long_sub;
        } else {
            i++;
        }
    }
    return cuenta;
}

// Función: str_buscar_subcadena
// Devuelve el índice de inicio de la primera aparición de una subcadena.
int str_buscar_subcadena(char *cad, char *sub) {
    int i = 0;
    int long_sub = 0;
    while (sub[long_sub] != '\0') {
        long_sub++;
    }
    if (long_sub == 0) {
        return 0;
    }
    while (cad[i] != '\0') {
        int coincidencia = 1;
        for (int j = 0; j < long_sub; j++) {
            if (cad[i + j] == '\0' || cad[i + j] != sub[j]) {
                coincidencia = 0;
            }
        }
        if (coincidencia != 0) {
            return i;
        }
        i++;
    }
    return -1;
}

// Función: str_buscar_ultima_subcadena
// Devuelve el índice de la última aparición de una subcadena.
int str_buscar_ultima_subcadena(char *cad, char *sub) {
    int ultimo_indice = -1;
    int i = 0;
    int long_sub = 0;
    while (sub[long_sub] != '\0') {
        long_sub++;
    }
    if (long_sub == 0) {
        return -1;
    }
    while (cad[i] != '\0') {
        int coincidencia = 1;
        for (int j = 0; j < long_sub; j++) {
            if (cad[i + j] == '\0' || cad[i + j] != sub[j]) {
                coincidencia = 0;
            }
        }
        if (coincidencia != 0) {
            ultimo_indice = i;
        }
        i++;
    }
    return ultimo_indice;
}

// Función: str_contar_puntuacion
// Cuenta caracteres de puntuación en una cadena.
int str_contar_puntuacion(char *cad) {
    int cuenta = 0;
    int i = 0;
    while (cad[i] != '\0') {
        char c = cad[i];
        if (c == '.' || c == ',' || c == ';' || c == ':' || c == '!' || c == '?') {
            cuenta++;
        }
        i++;
    }
    return cuenta;
}

// Función: str_contar_mayusculas
// Cuenta cuántas letras mayúsculas hay en una cadena.
int str_contar_mayusculas(char *cad) {
    int cuenta = 0;
    int i = 0;
    while (cad[i] != '\0') {
        if (cad[i] >= 'A' && cad[i] <= 'Z') {
            cuenta++;
        }
        i++;
    }
    return cuenta;
}

// Función: str_contar_minusculas
// Cuenta cuántas letras minúsculas hay en una cadena.
int str_contar_minusculas(char *cad) {
    int cuenta = 0;
    int i = 0;
    while (cad[i] != '\0') {
        if (cad[i] >= 'a' && cad[i] <= 'z') {
            cuenta++;
        }
        i++;
    }
    return cuenta;
}

// Función: str_invertir_palabras_simples
// Invierte el orden de caracteres dentro de un rango especificado.
void str_invertir_palabras_simples(char *cad, int inicio, int fin) {
    while (inicio < fin) {
        char temp = cad[inicio];
        cad[inicio] = cad[fin];
        cad[fin] = temp;
        inicio++;
        fin--;
    }
}

// Función: str_es_anagrama
// Comprueba si dos cadenas tienen los mismos caracteres con la misma frecuencia.
int str_es_anagrama(char *cad_a, char *cad_b) {
    int cont_a[256] = {0};
    int cont_b[256] = {0};
    int i = 0;
    while (cad_a[i] != '\0') {
        cont_a[(unsigned char)cad_a[i]]++;
        i++;
    }
    int j = 0;
    while (cad_b[j] != '\0') {
        cont_b[(unsigned char)cad_b[j]]++;
        j++;
    }
    for (int k = 0; k < 256; k++) {
        if (cont_a[k] != cont_b[k]) {
            return 0;
        }
    }
    return 1;
}

// Función: str_es_isograma
// Comprueba si una cadena no tiene letras repetidas.
int str_es_isograma(char *cad) {
    int visto[256] = {0};
    int i = 0;
    while (cad[i] != '\0') {
        unsigned char c = (unsigned char)cad[i];
        if (c >= 'a' && c <= 'z') {
            if (visto[c] != 0) {
                return 0;
            }
            visto[c] = 1;
        } else if (c >= 'A' && c <= 'Z') {
            unsigned char min = c + 32;
            if (visto[min] != 0) {
                return 0;
            }
            visto[min] = 1;
        }
        i++;
    }
    return 1;
}

// Función: str_es_pangrama_aprox
// Comprueba si una cadena contiene al menos 26 letras alfabéticas distintas.
int str_es_pangrama_aprox(char *cad) {
    int letras[26] = {0};
    int i = 0;
    while (cad[i] != '\0') {
        char c = cad[i];
        if (c >= 'a' && c <= 'z') {
            letras[c - 'a'] = 1;
        } else if (c >= 'A' && c <= 'Z') {
            letras[c - 'A'] = 1;
        }
        i++;
    }
    int cuenta = 0;
    for (int j = 0; j < 26; j++) {
        if (letras[j] != 0) {
            cuenta++;
        }
    }
    return cuenta == 26;
}

// Función: str_cifrar_cesar
// Cifra una cadena aplicando un desplazamiento César a las letras minúsculas.
void str_cifrar_cesar(char *cad, int desplazamiento) {
    int i = 0;
    desplazamiento = desplazamiento % 26;
    if (desplazamiento < 0) {
        desplazamiento = desplazamiento + 26;
    }
    while (cad[i] != '\0') {
        if (cad[i] >= 'a' && cad[i] <= 'z') {
            cad[i] = 'a' + ((cad[i] - 'a' + desplazamiento) % 26);
        }
        i++;
    }
}

// Función: str_descifrar_cesar
// Descifra una cadena aplicando un desplazamiento César inverso a minúsculas.
void str_descifrar_cesar(char *cad, int desplazamiento) {
    int i = 0;
    desplazamiento = desplazamiento % 26;
    if (desplazamiento < 0) {
        desplazamiento = desplazamiento + 26;
    }
    while (cad[i] != '\0') {
        if (cad[i] >= 'a' && cad[i] <= 'z') {
            cad[i] = 'a' + ((cad[i] - 'a' - desplazamiento + 26) % 26);
        }
        i++;
    }
}

// Función: str_eliminar_caracter
// Elimina todas las ocurrencias de un carácter específico de una cadena.
void str_eliminar_caracter(char *cad, char objetivo) {
    int i = 0;
    int j = 0;
    while (cad[i] != '\0') {
        if (cad[i] != objetivo) {
            cad[j] = cad[i];
            j++;
        }
        i++;
    }
    cad[j] = '\0';
}

// Función: str_eliminar_digitos
// Elimina todos los caracteres numéricos de una cadena.
void str_eliminar_digitos(char *cad) {
    int i = 0;
    int j = 0;
    while (cad[i] != '\0') {
        if (!(cad[i] >= '0' && cad[i] <= '9')) {
            cad[j] = cad[i];
            j++;
        }
        i++;
    }
    cad[j] = '\0';
}

// Función: str_eliminar_puntuacion
// Elimina puntos y comas de una cadena.
void str_eliminar_puntuacion(char *cad) {
    int i = 0;
    int j = 0;
    while (cad[i] != '\0') {
        char c = cad[i];
        if (c != '.' && c != ',' && c != ';' && c != ':' && c != '!' && c != '?') {
            cad[j] = cad[i];
            j++;
        }
        i++;
    }
    cad[j] = '\0';
}

// Función: str_rellenar_izquierda
// Rellena una cadena por la izquierda con un carácter hasta alcanzar una longitud.
void str_rellenar_izquierda(char *cad, char relleno, int longitud_final) {
    int longi = 0;
    while (cad[longi] != '\0') {
        longi++;
    }
    if (longi >= longitud_final) {
        return;
    }
    int dif = longitud_final - longi;
    for (int i = longi; i >= 0; i--) {
        cad[i + dif] = cad[i];
    }
    for (int i = 0; i < dif; i++) {
        cad[i] = relleno;
    }
}

// Función: str_rellenar_derecha
// Rellena una cadena por la derecha con un carácter hasta alcanzar una longitud.
void str_rellenar_derecha(char *cad, char relleno, int longitud_final) {
    int longi = 0;
    while (cad[longi] != '\0') {
        longi++;
    }
    if (longi >= longitud_final) {
        return;
    }
    for (int i = longi; i < longitud_final; i++) {
        cad[i] = relleno;
    }
    cad[longitud_final] = '\0';
}

// Función: str_recortar_inicio
// Elimina los espacios en blanco al inicio de una cadena.
void str_recortar_inicio(char *cad) {
    int i = 0;
    while (cad[i] == ' ') {
        i++;
    }
    if (i == 0) {
        return;
    }
    int j = 0;
    while (cad[i + j] != '\0') {
        cad[j] = cad[i + j];
        j++;
    }
    cad[j] = '\0';
}

// Función: str_truncar
// Corta una cadena a una longitud máxima especificada.
void str_truncar(char *cad, int longitud_maxima) {
    int longi = 0;
    while (cad[longi] != '\0') {
        longi++;
    }
    if (longi > longitud_maxima) {
        cad[longitud_maxima] = '\0';
    }
}

// Función: str_copiar_n
// Copia como máximo n caracteres de origen a destino.
void str_copiar_n(char *origen, char *destino, int n) {
    int i = 0;
    while (i < n && origen[i] != '\0') {
        destino[i] = origen[i];
        i++;
    }
    destino[i] = '\0';
}

// Función: char_es_puntuacion
// Comprueba si un carácter es un signo de puntuación básico.
int char_es_puntuacion(char c) {
    if (c == '.' || c == ',' || c == ';' || c == ':' || c == '!' || c == '?') {
        return 1;
    }
    return 0;
}

// Función: char_es_mayuscula
// Comprueba si un carácter es una letra mayúscula.
int char_es_mayuscula(char c) {
    if (c >= 'A' && c <= 'Z') {
        return 1;
    }
    return 0;
}

// Función: char_es_minuscula
// Comprueba si un carácter es una letra minúscula.
int char_es_minuscula(char c) {
    if (c >= 'a' && c <= 'z') {
        return 1;
    }
    return 0;
}

// Función: char_es_hexadecimal
// Comprueba si un carácter es válido en base hexadecimal.
int char_es_hexadecimal(char c) {
    if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F')) {
        return 1;
    }
    return 0;
}

// Función: char_es_octal
// Comprueba si un carácter es un dígito octal válido.
int char_es_octal(char c) {
    if (c >= '0' && c <= '7') {
        return 1;
    }
    return 0;
}

// Función: bit_rotar_izquierda_8
// Rota un entero de 8 bits hacia la izquierda.
int bit_rotar_izquierda_8(int num, int posiciones) {
    int val = num & 0xFF;
    posiciones = posiciones % 8;
    return ((val << posiciones) | (val >> (8 - posiciones))) & 0xFF;
}

// Función: bit_rotar_derecha_8
// Rota un entero de 8 bits hacia la derecha.
int bit_rotar_derecha_8(int num, int posiciones) {
    int val = num & 0xFF;
    posiciones = posiciones % 8;
    return ((val >> posiciones) | (val << (8 - posiciones))) & 0xFF;
}

// Función: bit_rotar_izquierda_16
// Rota un entero de 16 bits hacia la izquierda.
int bit_rotar_izquierda_16(int num, int posiciones) {
    int val = num & 0xFFFF;
    posiciones = posiciones % 16;
    return ((val << posiciones) | (val >> (16 - posiciones))) & 0xFFFF;
}

// Función: bit_rotar_derecha_16
// Rota un entero de 16 bits hacia la derecha.
int bit_rotar_derecha_16(int num, int posiciones) {
    int val = num & 0xFFFF;
    posiciones = posiciones % 16;
    return ((val >> posiciones) | (val << (16 - posiciones))) & 0xFFFF;
}

// Función: bit_es_par_bitwise
// Comprueba si un número es par usando operaciones de bits.
int bit_es_par_bitwise(int num) {
    return (num & 1) == 0;
}

// Función: bit_es_impar_bitwise
// Comprueba si un número es impar usando operaciones de bits.
int bit_es_impar_bitwise(int num) {
    return (num & 1) != 0;
}

// Función: bit_multiplicar_por_dos
// Multiplica un número por dos usando desplazamiento de bits.
int bit_multiplicar_por_dos(int num) {
    return num << 1;
}

// Función: bit_dividir_por_dos
// Divide un número por dos usando desplazamiento de bits.
int bit_dividir_por_dos(int num) {
    return num >> 1;
}

// Función: bit_invertir_mascara
// Invierte los bits de un número aplicando una máscara XOR.
int bit_invertir_mascara(int num, int mascara) {
    return num ^ mascara;
}

// Función: bit_emparejar_bits
// Intercala los 8 bits inferiores de dos números.
int bit_emparejar_bits(int a, int b) {
    int resultado = 0;
    for (int i = 0; i < 8; i++) {
        int bit_a = (a >> i) & 1;
        int bit_b = (b >> i) & 1;
        resultado = resultado | (bit_a << (2 * i)) | (bit_b << (2 * i + 1));
    }
    return resultado;
}

// Función: ptr_sumar_valores
// Suma los valores de dos punteros y devuelve el resultado entero.
int ptr_sumar_valores(int *ptr_a, int *ptr_b) {
    return *ptr_a + *ptr_b;
}

// Función: ptr_restar_valores
// Resta los valores de dos punteros y devuelve el resultado entero.
int ptr_restar_valores(int *ptr_a, int *ptr_b) {
    return *ptr_a - *ptr_b;
}

// Función: ptr_multiplicar_valores
// Multiplica los valores apuntados por dos punteros.
int ptr_multiplicar_valores(int *ptr_a, int *ptr_b) {
    return (*ptr_a) * (*ptr_b);
}

// Función: ptr_dividir_valores
// Divide los valores apuntados por dos punteros.
int ptr_dividir_valores(int *ptr_a, int *ptr_b) {
    if (*ptr_b == 0) {
        return 0;
    }
    return (*ptr_a) / (*ptr_b);
}

// Función: ptr_modulo_valores
// Calcula el módulo de los valores apuntados por dos punteros.
int ptr_modulo_valores(int *ptr_a, int *ptr_b) {
    if (*ptr_b == 0) {
        return 0;
    }
    return (*ptr_a) % (*ptr_b);
}

// Función: bool_mux
// Simula un multiplexor booleano de dos entradas y una línea de selección.
int bool_mux(int entrada_a, int entrada_b, int seleccion) {
    if (seleccion == 0) {
        return entrada_a != 0;
    }
    return entrada_b != 0;
}

// Función: bool_demux_cero
// Simula la salida cero de un demultiplexor de una entrada.
int bool_demux_cero(int entrada, int seleccion) {
    if (seleccion == 0) {
        return entrada != 0;
    }
    return 0;
}

// Función: bool_demux_uno
// Simula la salida uno de un demultiplexor de una entrada.
int bool_demux_uno(int entrada, int seleccion) {
    if (seleccion != 0) {
        return entrada != 0;
    }
    return 0;
}

// Función: bool_semi_sumador_suma
// Calcula el bit de suma de un semisumador.
int bool_semi_sumador_suma(int a, int b) {
    int bool_a = (a != 0);
    int bool_b = (b != 0);
    if (bool_a != bool_b) {
        return 1;
    }
    return 0;
}

// Función: bool_semi_sumador_acarreo
// Calcula el bit de acarreo de un semisumador.
int bool_semi_sumador_acarreo(int a, int b) {
    if (a != 0 && b != 0) {
        return 1;
    }
    return 0;
}

// Función: mem_intercambiar_bloques
// Intercambia los elementos de dos bloques de memoria simulados.
void mem_intercambiar_bloques(int bloque_a[], int bloque_b[], int tamano) {
    for (int i = 0; i < tamano; i++) {
        int temp = bloque_a[i];
        bloque_a[i] = bloque_b[i];
        bloque_b[i] = temp;
    }
}

// Función: mem_invertir_bloque
// Invierte el orden de los elementos en un bloque de memoria simulado.
void mem_invertir_bloque(int bloque[], int tamano) {
    int inicio = 0;
    int fin = tamano - 1;
    while (inicio < fin) {
        int temp = bloque[inicio];
        bloque[inicio] = bloque[fin];
        bloque[fin] = temp;
        inicio++;
        fin--;
    }
}

// Función: mem_buscar_byte
// Busca un valor específico en un bloque de memoria simulado.
int mem_buscar_byte(int bloque[], int tamano, int valor) {
    for (int i = 0; i < tamano; i++) {
        if (bloque[i] == valor) {
            return i;
        }
    }
    return -1;
}

// Función: util_generar_secuencia
// Llena un arreglo con una secuencia consecutiva de números.
void util_generar_secuencia(int arr[], int tamano, int valor_inicial) {
    for (int i = 0; i < tamano; i++) {
        arr[i] = valor_inicial + i;
    }
}

// Función: util_sumar_condicional
// Suma dos números solo si una condición booleana es verdadera.
int util_sumar_condicional(int a, int b, int condicion) {
    if (condicion != 0) {
        return a + b;
    }
    return 0;
}

