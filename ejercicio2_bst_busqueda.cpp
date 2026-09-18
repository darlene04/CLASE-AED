/*
============================================================
2. BST: BUSQUEDA DE CLAVES
============================================================

ENUNCIADO:

Se proporcionan n números enteros que deben insertarse en un
Árbol Binario de Búsqueda (BST).

Después se proporcionan q consultas. Cada consulta contiene
una clave x.

Para cada consulta, determina si la clave x se encuentra
dentro del BST.

Imprime SI si la clave existe y NO si no existe.

------------------------------------------------------------
PROPIEDAD DEL BST:
------------------------------------------------------------

Para cada nodo se cumple:

    claves menores -> subárbol izquierdo
    claves mayores -> subárbol derecho

Es decir:

    izquierdo < raíz < derecho

Esta propiedad permite decidir en qué dirección buscar sin
recorrer necesariamente todos los nodos.

------------------------------------------------------------
ENTRADA:
------------------------------------------------------------

La primera línea contiene un entero n, que representa la
cantidad de claves que se insertarán en el BST.

La segunda línea contiene n números enteros.

La tercera línea contiene un entero q, que representa la
cantidad de consultas.

La cuarta línea contiene q números enteros, correspondientes
a las claves que se desean buscar.

------------------------------------------------------------
SALIDA:
------------------------------------------------------------

Por cada consulta, imprime una línea:

    SI

si la clave existe en el BST.

En caso contrario, imprime:

    NO

------------------------------------------------------------
EJEMPLO DE ENTRADA:
------------------------------------------------------------

7
40 20 60 10 30 50 70
4
30 80 10 55

------------------------------------------------------------
ÁRBOL GENERADO:
------------------------------------------------------------

              40
            /    \
          20      60
         /  \    /  \
       10   30  50   70

------------------------------------------------------------
EJEMPLO DE SALIDA:
------------------------------------------------------------

SI
NO
SI
NO

------------------------------------------------------------
EXPLICACION:
------------------------------------------------------------

Consulta 30:

    30 < 40 -> avanzamos hacia la izquierda.
    30 > 20 -> avanzamos hacia la derecha.
    Encontramos 30.

    Respuesta: SI.

Consulta 80:

    80 > 40 -> derecha.
    80 > 60 -> derecha.
    80 > 70 -> derecha.
    Encontramos nullptr.

    Respuesta: NO.

Consulta 10:

    10 < 40 -> izquierda.
    10 < 20 -> izquierda.
    Encontramos 10.

    Respuesta: SI.

Consulta 55:

    55 > 40 -> derecha.
    55 < 60 -> izquierda.
    55 > 50 -> derecha.
    Encontramos nullptr.

    Respuesta: NO.

------------------------------------------------------------
COMPLEJIDAD:
------------------------------------------------------------

Si el BST está aproximadamente balanceado:

    Búsqueda: O(log n)

En el peor caso, si el árbol está degenerado:

    Búsqueda: O(n)

La búsqueda iterativa utiliza:

    Memoria auxiliar: O(1)

============================================================
SOLUCION EN C++
============================================================
*/

#include <iostream>

using namespace std;

class BST
{
private:
    struct Nodo
    {
        int clave;
        Nodo* izquierdo;
        Nodo* derecho;

        Nodo(int valor)
        {
            clave = valor;
            izquierdo = nullptr;
            derecho = nullptr;
        }
    };

    Nodo* raiz;

    /*
    Inserta una clave dentro del BST.
    */
    Nodo* insertar(Nodo* nodo, int clave)
    {
        if (nodo == nullptr)
        {
            return new Nodo(clave);
        }

        if (clave < nodo->clave)
        {
            nodo->izquierdo =
                insertar(nodo->izquierdo, clave);
        }
        else if (clave > nodo->clave)
        {
            nodo->derecho =
                insertar(nodo->derecho, clave);
        }

        // Las claves repetidas no se insertan.
        return nodo;
    }

    /*
    Libera la memoria utilizando postorder.
    */
    void liberar(Nodo* nodo)
    {
        if (nodo == nullptr)
        {
            return;
        }

        liberar(nodo->izquierdo);
        liberar(nodo->derecho);

        delete nodo;
    }

public:
    BST()
    {
        raiz = nullptr;
    }

    ~BST()
    {
        liberar(raiz);
    }

    void insertar(int clave)
    {
        raiz = insertar(raiz, clave);
    }

    /*
    Busca una clave de manera iterativa.

    Devuelve true si la encuentra.
    Devuelve false si no existe.
    */
    bool buscar(int clave) const
    {
        Nodo* actual = raiz;

        while (actual != nullptr)
        {
            // Encontramos la clave.
            if (clave == actual->clave)
            {
                return true;
            }

            // La clave es menor: avanzamos a la izquierda.
            if (clave < actual->clave)
            {
                actual = actual->izquierdo;
            }

            // La clave es mayor: avanzamos a la derecha.
            else
            {
                actual = actual->derecho;
            }
        }

        // Llegamos a nullptr, por lo tanto no existe.
        return false;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    BST arbol;

    // Construimos el BST.
    for (int i = 0; i < n; i++)
    {
        int clave;
        cin >> clave;

        arbol.insertar(clave);
    }

    int q;
    cin >> q;

    // Procesamos las consultas.
    for (int i = 0; i < q; i++)
    {
        int claveBuscada;
        cin >> claveBuscada;

        if (arbol.buscar(claveBuscada))
        {
            cout << "SI\n";
        }
        else
        {
            cout << "NO\n";
        }
    }

    return 0;
}