
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
*/

#include <iostream>
#include <unordered_set>

using namespace std;

int main()
{
    // Acelera la lectura y escritura de datos.
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    // Este conjunto almacenará los números que ya aparecieron.
    unordered_set<int> vistos;

    // Reservamos memoria porque puede haber hasta n números distintos.
    vistos.reserve(n);

    for (int i = 0; i < n; i++)
    {
        int numero;
        cin >> numero;

        // count(numero) devuelve 1 si el número ya está guardado.
        if (vistos.count(numero))
        {
            cout << numero << '\n';
            return 0;
        }

        // Como todavía no había aparecido, lo guardamos.
        vistos.insert(numero);
    }

    // Si terminamos el recorrido, ningún número se repitió.
    cout << "NO\n";

    return 0;
}