/*
============================================================
5. FRECUENCIAS DINAMICAS
============================================================

ENUNCIADO:

Se deben procesar q operaciones sobre un conjunto de números.

Existen tres tipos de operaciones:

    1 x

Insertar una aparición del número x.

    2 x

Eliminar una aparición del número x, solamente si existe.

    3 x

Consultar e imprimir cuántas veces aparece actualmente
el número x.

Inicialmente no hay ningún número almacenado.

------------------------------------------------------------
ENTRADA:
------------------------------------------------------------

La primera línea contiene un número entero q, que representa
la cantidad de operaciones.

Las siguientes q líneas contienen dos números enteros:

    operacion x

Donde operacion puede ser:

    1 = insertar una aparición de x.
    2 = eliminar una aparición de x.
    3 = consultar la frecuencia de x.

------------------------------------------------------------
SALIDA:
------------------------------------------------------------

Por cada operación de tipo 3, imprime una línea con la
cantidad de veces que aparece el número consultado.

Si el número no existe, imprime 0.

------------------------------------------------------------
EJEMPLO DE ENTRADA:
------------------------------------------------------------

7
1 5
1 5
1 8
3 5
2 5
3 5
3 8

------------------------------------------------------------
EJEMPLO DE SALIDA:
------------------------------------------------------------

2
1
1

------------------------------------------------------------
EXPLICACION:
------------------------------------------------------------

Inicialmente no hay ningún número:

    {}

Operación 1 5:

    Insertamos el número 5.
    Frecuencias: 5 -> 1

Operación 1 5:

    Insertamos otra aparición de 5.
    Frecuencias: 5 -> 2

Operación 1 8:

    Insertamos el número 8.
    Frecuencias: 5 -> 2, 8 -> 1

Operación 3 5:

    Consultamos la frecuencia de 5.
    El número 5 aparece 2 veces.
    Se imprime 2.

Operación 2 5:

    Eliminamos una aparición de 5.
    Frecuencias: 5 -> 1, 8 -> 1

Operación 3 5:

    El número 5 aparece 1 vez.
    Se imprime 1.

Operación 3 8:

    El número 8 aparece 1 vez.
    Se imprime 1.

------------------------------------------------------------
ESTRUCTURA UTILIZADA:
------------------------------------------------------------

Se utiliza:

    unordered_map<int, int>

La clave representa el número y el valor representa su
frecuencia actual:

    numero -> cantidad de apariciones

Por ejemplo:

    frecuencia[5] = 2
    frecuencia[8] = 1

------------------------------------------------------------
COMPLEJIDAD:
------------------------------------------------------------

Cada operación tiene una complejidad esperada de O(1).

Para las q operaciones:

    Tiempo esperado: O(q)
    Memoria: O(k)

Donde k es la cantidad de números distintos almacenados.

============================================================
SOLUCION EN C++
============================================================
*/

#include <iostream>
#include <unordered_map>

using namespace std;

int main()
{
    // Acelera la lectura y escritura.
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q;
    cin >> q;

    // La clave es el número y el valor es su frecuencia.
    unordered_map<int, int> frecuencia;
    frecuencia.reserve(q);

    for (int i = 0; i < q; i++)
    {
        int operacion;
        int numero;

        cin >> operacion >> numero;

        if (operacion == 1)
        {
            // OPERACION 1:
            // Insertar una aparición del número.
            frecuencia[numero]++;
        }
        else if (operacion == 2)
        {
            // OPERACION 2:
            // Eliminar una aparición si el número existe.

            auto resultado = frecuencia.find(numero);

            if (resultado != frecuencia.end())
            {
                resultado->second--;

                // Si la frecuencia llegó a cero,
                // eliminamos completamente la clave.
                if (resultado->second == 0)
                {
                    frecuencia.erase(resultado);
                }
            }
        }
        else if (operacion == 3)
        {
            // OPERACION 3:
            // Consultar la frecuencia del número.

            auto resultado = frecuencia.find(numero);

            if (resultado != frecuencia.end())
            {
                cout << resultado->second << '\n';
            }
            else
            {
                cout << 0 << '\n';
            }
        }
    }

    return 0;
}