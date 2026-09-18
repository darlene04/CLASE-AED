
/*
============================================================
C. ALTURA Y NIVEL
============================================================

ENUNCIADO:

Se proporcionan n números enteros distintos.

Los números deben insertarse, uno por uno y en el orden
recibido, dentro de un Árbol Binario de Búsqueda (ABB)
inicialmente vacío.

Después de construir el árbol se debe imprimir:

1. La altura del árbol.
2. El nivel o profundidad de cada clave consultada.

------------------------------------------------------------
PROPIEDAD DEL ABB:
------------------------------------------------------------

Para cada nodo:

    claves menores -> subárbol izquierdo
    claves mayores -> subárbol derecho

Es decir:

    izquierdo < raíz < derecho

ABB significa Árbol Binario de Búsqueda.

En inglés se llama BST:

    Binary Search Tree

Por lo tanto:

    ABB = BST

------------------------------------------------------------
ALTURA:
------------------------------------------------------------

La altura es la cantidad de aristas del camino más largo
desde la raíz hasta una hoja.

Por convención:

    Árbol con un solo nodo -> altura 0
    Árbol vacío -> altura -1

------------------------------------------------------------
NIVEL O PROFUNDIDAD:
------------------------------------------------------------

El nivel de un nodo es la cantidad de aristas que existen
desde la raíz hasta ese nodo.

Por convención:

    Raíz -> nivel 0
    Hijos de la raíz -> nivel 1
    Nietos de la raíz -> nivel 2

------------------------------------------------------------
ENTRADA:
------------------------------------------------------------

La primera línea contiene un entero n.

La segunda línea contiene n enteros distintos, en el orden
en que deben insertarse en el ABB.

La tercera línea contiene un entero q.

La cuarta línea contiene q claves que deben consultarse.

Se garantiza que todas las claves consultadas existen.

------------------------------------------------------------
SALIDA:
------------------------------------------------------------

En la primera línea, imprime la altura del árbol.

Después imprime q líneas. Cada línea debe contener el nivel
de la clave correspondiente.

------------------------------------------------------------
EJEMPLO DE ENTRADA:
------------------------------------------------------------

9
5 3 8 1 4 7 9 2 6
4
5 8 2 6



------------------------------------------------------------
EJEMPLO DE SALIDA:
------------------------------------------------------------

3
0
1
3
3

------------------------------------------------------------
EXPLICACION:
------------------------------------------------------------

La altura es 3 porque el camino más largo tiene 3 aristas.

Por ejemplo:

    5 -> 3 -> 1 -> 2

Las consultas son:

    5 -> nivel 0, porque es la raíz.
    8 -> nivel 1.
    2 -> nivel 3.
    6 -> nivel 3.

------------------------------------------------------------
COMPLEJIDAD:
------------------------------------------------------------

Si el árbol está aproximadamente balanceado:

    Insertar: O(log n)
    Buscar nivel: O(log n)

En el peor caso, si el árbol forma una cadena:

    Insertar: O(n)
    Buscar nivel: O(n)

La memoria utilizada por los nodos es:

    O(n)

============================================================
SOLUCION EN C++
============================================================
*/

#include <iostream>
#include <algorithm>

using namespace std;

class ABB
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
    int alturaArbol;

    /*
    Libera todos los nodos del árbol.
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
    /*
    El árbol comienza vacío.

    La altura de un árbol vacío es -1.
    */
    ABB()
    {
        raiz = nullptr;
        alturaArbol = -1;
    }

    ~ABB()
    {
        liberar(raiz);
    }

    /*
    Inserta una clave y calcula el nivel donde fue insertada.
    */
    void insertar(int clave)
    {
        // Si el árbol está vacío, la clave será la raíz.
        if (raiz == nullptr)
        {
            raiz = new Nodo(clave);
            alturaArbol = 0;
            return;
        }

        Nodo* actual = raiz;
        int nivelActual = 0;

        while (true)
        {
            if (clave < actual->clave)
            {
                // Si existe hijo izquierdo, continuamos bajando.
                if (actual->izquierdo != nullptr)
                {
                    actual = actual->izquierdo;
                    nivelActual++;
                }
                else
                {
                    // Encontramos el lugar donde insertar.
                    actual->izquierdo = new Nodo(clave);
                    nivelActual++;

                    alturaArbol = max(alturaArbol, nivelActual);
                    return;
                }
            }
            else
            {
                // Las claves son distintas, así que clave > actual->clave.

                if (actual->derecho != nullptr)
                {
                    actual = actual->derecho;
                    nivelActual++;
                }
                else
                {
                    // Encontramos el lugar donde insertar.
                    actual->derecho = new Nodo(clave);
                    nivelActual++;

                    alturaArbol = max(alturaArbol, nivelActual);
                    return;
                }
            }
        }
    }

    /*
    Devuelve la altura del árbol completo.
    */
    int altura() const
    {
        return alturaArbol;
    }

    /*
    Busca una clave y devuelve su nivel.

    La raíz está en el nivel 0.
    */
    int nivel(int clave) const
    {
        Nodo* actual = raiz;
        int nivelActual = 0;

        while (actual != nullptr)
        {
            if (clave == actual->clave)
            {
                return nivelActual;
            }

            if (clave < actual->clave)
            {
                actual = actual->izquierdo;
            }
            else
            {
                actual = actual->derecho;
            }

            nivelActual++;
        }

        /*
        El enunciado garantiza que la clave existe,
        por lo que normalmente nunca se retorna -1.
        */
        return -1;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    ABB arbol;

    // Insertamos las n claves en el orden recibido.
    for (int i = 0; i < n; i++)
    {
        int clave;
        cin >> clave;

        arbol.insertar(clave);
    }

    // Primero imprimimos la altura.
    cout << arbol.altura() << '\n';

    int q;
    cin >> q;

    // Después respondemos las q consultas.
    for (int i = 0; i < q; i++)
    {
        int clave;
        cin >> clave;

        cout << arbol.nivel(clave) << '\n';
    }

    return 0;
}