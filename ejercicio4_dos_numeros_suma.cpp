/*
============================================================
4. DOS NUMEROS CON SUMA OBJETIVO
============================================================

ENUNCIADO:

Dado un arreglo de n números enteros y un valor objetivo x,
determina si existen dos elementos ubicados en posiciones
diferentes cuya suma sea exactamente igual a x.

Si existen, imprime SI.

Si no existen, imprime NO.

------------------------------------------------------------
ENTRADA:
------------------------------------------------------------

La primera línea contiene dos números enteros:

    n x

Donde:

    n = cantidad de elementos del arreglo.
    x = suma objetivo.

La segunda línea contiene n números enteros.

------------------------------------------------------------
SALIDA:
------------------------------------------------------------

Imprime:

    SI

si existen dos elementos de posiciones diferentes cuya
suma sea igual al objetivo.

En caso contrario, imprime:

    NO

------------------------------------------------------------
EJEMPLO DE ENTRADA:
------------------------------------------------------------

5 9
2 7 11 4 3

------------------------------------------------------------
EJEMPLO DE SALIDA:
------------------------------------------------------------

SI

------------------------------------------------------------
EXPLICACION:
------------------------------------------------------------

El arreglo es:

    [2, 7, 11, 4, 3]

El objetivo es:

    9

Los números 2 y 7 cumplen:

    2 + 7 = 9

Por lo tanto, la respuesta es SI.

------------------------------------------------------------
IDEA DE LA SOLUCION:
------------------------------------------------------------

Para cada número calculamos su complemento:

    complemento = objetivo - numero

Por ejemplo, si el objetivo es 9 y el número actual es 7:

    complemento = 9 - 7
    complemento = 2

Luego comprobamos si el número 2 ya apareció anteriormente.

Si ya apareció, significa que encontramos dos números cuya
suma es igual al objetivo.

------------------------------------------------------------
ESTRUCTURA UTILIZADA:
------------------------------------------------------------

Se utiliza:

    unordered_set<long long>

El conjunto guarda los números que ya fueron leídos.

Antes de insertar el número actual, buscamos si su
complemento ya se encuentra en el conjunto.

------------------------------------------------------------
COMPLEJIDAD:
------------------------------------------------------------

Tiempo esperado: O(n)
Memoria: O(n)

============================================================
SOLUCION EN C++
============================================================
*/

#include <iostream>
#include <unordered_set>

using namespace std;

int main()
{
    // Acelera la lectura y escritura.
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long objetivo;

    cin >> n >> objetivo;

    // Guardará los números que ya aparecieron.
    unordered_set<long long> vistos;
    vistos.reserve(n);

    for (int i = 0; i < n; i++)
    {
        long long numero;
        cin >> numero;

        // Calculamos qué número necesitamos para completar la suma.
        long long complemento = objetivo - numero;

        // Comprobamos si el complemento ya apareció.
        if (vistos.count(complemento))
        {
            cout << "SI\n";
            return 0;
        }

        // Guardamos el número actual.
        vistos.insert(numero);
    }

    cout << "NO\n";

    return 0;
}