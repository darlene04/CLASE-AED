/*
============================================================
3. INTERSECCION DE DOS ARREGLOS
============================================================

ENUNCIADO:

Se proporcionan dos arreglos de números enteros A y B.

Determina cuántos valores distintos aparecen en ambos
arreglos.

Si un número aparece varias veces, solamente debe contarse
una vez.

------------------------------------------------------------
ENTRADA:
------------------------------------------------------------

La primera línea contiene un número entero n, que representa
la cantidad de elementos del arreglo A.

La segunda línea contiene n números enteros correspondientes
al arreglo A.

La tercera línea contiene un número entero m, que representa
la cantidad de elementos del arreglo B.

La cuarta línea contiene m números enteros correspondientes
al arreglo B.

------------------------------------------------------------
SALIDA:
------------------------------------------------------------

Imprime un único número entero: la cantidad de valores
distintos que aparecen tanto en A como en B.

------------------------------------------------------------
EJEMPLO DE ENTRADA:
------------------------------------------------------------

5
1 2 2 3 5
4
2 2 3 8

------------------------------------------------------------
EJEMPLO DE SALIDA:
------------------------------------------------------------

2

------------------------------------------------------------
EXPLICACION:
------------------------------------------------------------

Los valores distintos del arreglo A son:

    {1, 2, 3, 5}

Los valores distintos del arreglo B son:

    {2, 3, 8}

Los valores que aparecen en ambos arreglos son:

    {2, 3}

Por lo tanto, existen 2 valores distintos en común.

Aunque el número 2 aparece repetido, solamente se cuenta
una vez.

------------------------------------------------------------
ESTRUCTURA UTILIZADA:
------------------------------------------------------------

Se utiliza:

    unordered_set<int>

Primero se guardan en un conjunto los valores distintos
del arreglo A.

Luego se recorren los valores del arreglo B.

Si un número de B existe en el conjunto A, se aumenta el
contador y se elimina ese número del conjunto.

La eliminación evita contar nuevamente un valor repetido.

------------------------------------------------------------
COMPLEJIDAD:
------------------------------------------------------------

Tiempo esperado: O(n + m)
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
    cin >> n;

    // Guardará los valores distintos del arreglo A.
    unordered_set<int> conjuntoA;
    conjuntoA.reserve(n);

    // Leemos el primer arreglo.
    for (int i = 0; i < n; i++)
    {
        int numero;
        cin >> numero;

        conjuntoA.insert(numero);
    }

    int m;
    cin >> m;

    int cantidadComunes = 0;

    // Leemos el segundo arreglo.
    for (int i = 0; i < m; i++)
    {
        int numero;
        cin >> numero;

        // Buscamos el número dentro del conjunto A.
        auto resultado = conjuntoA.find(numero);

        if (resultado != conjuntoA.end())
        {
            // El número aparece en ambos arreglos.
            cantidadComunes++;

            // Lo eliminamos para no contarlo nuevamente.
            conjuntoA.erase(resultado);
        }
    }

    cout << cantidadComunes << '\n';

    return 0;
}