/*
PROBLEMA C: MULTISETS IGUALES

Se proporcionan dos arreglos de números enteros:

    A = (a1, a2, ..., an)
    B = (b1, b2, ..., bm)

Se debe determinar si ambos arreglos contienen exactamente
los mismos valores y con las mismas cantidades.

El orden de los elementos no importa.

ENTRADA:

La primera línea contiene un entero n:

    1 <= n <= 10^6

La segunda línea contiene n enteros correspondientes al arreglo A.

La tercera línea contiene un entero m:

    1 <= m <= 10^6

La cuarta línea contiene m enteros correspondientes al arreglo B.

Cada elemento cumple:

    1 <= ai, bi <= 10^9

SALIDA:

Imprimir:

    SI

si ambos arreglos tienen los mismos valores con las mismas
frecuencias.

En caso contrario, imprimir:

    NO

EJEMPLO DE ENTRADA:

5
3 1 2 3 5
5
1 3 3 2 5

EJEMPLO DE SALIDA:

SI
*/

#include <iostream>
#include <unordered_map>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    unordered_map<int, int> frecuencia;
    frecuencia.reserve(n);

    // Leemos el arreglo A y contamos sus frecuencias.
    for (int i = 0; i < n; i++)
    {
        int numero;
        cin >> numero;

        frecuencia[numero]++;
    }

    int m;
    cin >> m;

    // Para ser iguales, deben tener la misma cantidad de elementos.
    bool iguales = (n == m);

    // Leemos el arreglo B.
    for (int i = 0; i < m; i++)
    {
        int numero;
        cin >> numero;

        auto resultado = frecuencia.find(numero);

        // El número no existe en A.
        if (resultado == frecuencia.end())
        {
            iguales = false;
        }
        else
        {
            // Quitamos una aparición.
            resultado->second--;

            // Si su frecuencia llegó a cero, lo eliminamos del hash.
            if (resultado->second == 0)
            {
                frecuencia.erase(resultado);
            }
        }
    }

    // Si quedaron elementos, las frecuencias no eran iguales.
    if (!frecuencia.empty())
    {
        iguales = false;
    }

    if (iguales)
    {
        cout << "SI\n";
    }
    else
    {
        cout << "NO\n";
    }

    return 0;
}