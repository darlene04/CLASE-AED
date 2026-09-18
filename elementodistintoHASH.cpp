/*
PROBLEMA B: ELEMENTOS DISTINTOS

Se proporciona un arreglo de n números enteros.
Se debe determinar cuántos valores diferentes aparecen en el arreglo.

ENTRADA:

La primera línea contiene un número entero n:

    1 <= n <= 10^6

La segunda línea contiene n números enteros:

    a1, a2, ..., an
    1 <= ai <= 10^9

SALIDA:

Imprimir un único número entero: la cantidad de valores
distintos que aparecen en el arreglo.

EJEMPLO DE ENTRADA:

7
5 3 5 8 3 9 8

EJEMPLO DE SALIDA:

4

EXPLICACION:

Los valores distintos son:

    {5, 3, 8, 9}

Por lo tanto, existen 4 elementos diferentes.
*/

#include <iostream>
#include <unordered_set>

using namespace std;

int main()
{
    // Hace que la lectura y escritura sean más rápidas.
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    // El unordered_set guarda únicamente elementos distintos.
    unordered_set<int> elementos;

    // Reservamos espacio porque n puede llegar hasta 1 000 000.
    elementos.reserve(n);

    // Leemos los n números.
    for (int i = 0; i < n; i++)
    {
        int numero;
        cin >> numero;

        // Si el número ya existe, no se vuelve a guardar.
        elementos.insert(numero);
    }

    // size() devuelve la cantidad de números distintos.
    cout << elementos.size() << '\n';

    return 0;
}