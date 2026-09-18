
/*
============================================================
1. PRIMER ELEMENTO REPETIDO
============================================================

ENUNCIADO:

Dado un arreglo de n números enteros, imprime el primer número
que aparezca por segunda vez mientras recorres el arreglo de
izquierda a derecha.

Si ningún número se repite, imprime NO.

------------------------------------------------------------
ENTRADA:
------------------------------------------------------------

La primera línea contiene un número entero n, que representa
la cantidad de elementos del arreglo.

La segunda línea contiene n números enteros.

------------------------------------------------------------
SALIDA:
------------------------------------------------------------

Imprime el primer número que aparezca por segunda vez.

Si ningún número se repite, imprime NO.

------------------------------------------------------------
EJEMPLO DE ENTRADA:
------------------------------------------------------------

7
4 2 8 3 2 9 4

------------------------------------------------------------
EJEMPLO DE SALIDA:
------------------------------------------------------------

2

------------------------------------------------------------
EXPLICACION:
------------------------------------------------------------

Recorremos el arreglo de izquierda a derecha:

- El número 4 aparece por primera vez.
- El número 2 aparece por primera vez.
- El número 8 aparece por primera vez.
- El número 3 aparece por primera vez.
- El número 2 aparece nuevamente.

Por lo tanto, el primer número que aparece por segunda vez
es el número 2.

------------------------------------------------------------
ESTRUCTURA UTILIZADA:
------------------------------------------------------------

Se utiliza unordered_set<int>.

Un unordered_set guarda elementos sin repetir y permite
comprobar rápidamente si un número ya fue insertado.

------------------------------------------------------------
COMPLEJIDAD:
------------------------------------------------------------

Tiempo esperado: O(n)
Memoria: O(n)

============================================================
SOLUCION EN C++
============================================================
/*
============================================================
2. NUMERO MAS FRECUENTE
============================================================

ENUNCIADO:

Dado un arreglo de n números enteros, encuentra el número
que aparece la mayor cantidad de veces y muestra también
su frecuencia.

Si dos o más números tienen la misma frecuencia máxima,
se debe imprimir el número menor.

------------------------------------------------------------
ENTRADA:
------------------------------------------------------------

La primera línea contiene un número entero n, que representa
la cantidad de elementos del arreglo.

La segunda línea contiene n números enteros.

------------------------------------------------------------
SALIDA:
------------------------------------------------------------

Imprime dos números separados por un espacio:

    numero frecuencia

El primer número es el elemento más frecuente.
El segundo número es la cantidad de veces que aparece.

Si varios números tienen la misma frecuencia máxima,
se imprime el menor de ellos.

------------------------------------------------------------
EJEMPLO DE ENTRADA:
------------------------------------------------------------

8
4 2 4 3 2 4 3 3

------------------------------------------------------------
EJEMPLO DE SALIDA:
------------------------------------------------------------

3 3

------------------------------------------------------------
EXPLICACION:
------------------------------------------------------------

En el arreglo:

    [4, 2, 4, 3, 2, 4, 3, 3]

las frecuencias son:

    4 aparece 3 veces.
    2 aparece 2 veces.
    3 aparece 3 veces.

Los números 3 y 4 tienen la frecuencia máxima de 3.

Como existe un empate, debemos escoger el número menor.

Entre 3 y 4, el menor es 3.

Por lo tanto, la respuesta es:

    3 3

------------------------------------------------------------
ESTRUCTURA UTILIZADA:
------------------------------------------------------------

Se utiliza:

    unordered_map<int, int>

La clave representa el número del arreglo y el valor
representa su frecuencia:

    numero -> cantidad de apariciones

Por ejemplo:

    frecuencia[4] = 3
    frecuencia[2] = 2
    frecuencia[3] = 3

------------------------------------------------------------
COMPLEJIDAD:
------------------------------------------------------------

Tiempo esperado: O(n)
Memoria: O(k)

Donde k es la cantidad de números distintos.

============================================================
SOLUCION EN C++
============================================================
*/

#include <iostream>
#include <unordered_map>
#include <limits>

using namespace std;

int main()
{
    // Acelera la lectura y escritura.
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    // La clave es el número y el valor es su frecuencia.
    unordered_map<int, int> frecuencia;

    // Reservamos espacio para reducir redimensionamientos.
    frecuencia.reserve(n);

    // Contamos cuántas veces aparece cada número.
    for (int i = 0; i < n; i++)
    {
        int numero;
        cin >> numero;

        frecuencia[numero]++;
    }

    int mejorNumero = numeric_limits<int>::max();
    int mayorFrecuencia = 0;

    // Recorremos la tabla hash.
    for (const auto& elemento : frecuencia)
    {
        int numero = elemento.first;
        int cantidad = elemento.second;

        // Primer caso:
        // Encontramos una frecuencia mayor.
        if (cantidad > mayorFrecuencia)
        {
            mayorFrecuencia = cantidad;
            mejorNumero = numero;
        }

        // Segundo caso:
        // Hay empate de frecuencias y el número actual es menor.
        else if (cantidad == mayorFrecuencia &&
                 numero < mejorNumero)
        {
            mejorNumero = numero;
        }
    }

    cout << mejorNumero << ' '
         << mayorFrecuencia << '\n';

    return 0;
}