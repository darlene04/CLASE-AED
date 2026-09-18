/*
============================================================
F. SUCESOR Y PREDECESOR
============================================================

ENUNCIADO:

Se construye un Árbol Binario de Búsqueda (ABB) insertando
n números enteros distintos en el orden recibido.

Después se deben responder q consultas.

Cada consulta contiene una clave x que está garantizada
dentro del árbol.

Para cada consulta se debe imprimir:

    predecesor sucesor

------------------------------------------------------------
PREDECESOR:
------------------------------------------------------------

El predecesor de x es el mayor valor del árbol que es
estrictamente menor que x.

Es decir:

    predecesor < x

Si x es el menor valor del árbol, no tiene predecesor y
se debe imprimir:

    NONE

------------------------------------------------------------
SUCESOR:
------------------------------------------------------------

El sucesor de x es el menor valor del árbol que es
estrictamente mayor que x.

Es decir:

    sucesor > x

Si x es el mayor valor del árbol, no tiene sucesor y
se debe imprimir:

    NONE

------------------------------------------------------------
COMO ENCONTRAR EL SUCESOR:
------------------------------------------------------------

CASO 1:

Si el nodo tiene un hijo derecho, su sucesor es el mínimo
de su subárbol derecho.

Para encontrar ese mínimo:

    1. Avanzamos al hijo derecho.
    2. Bajamos todo lo posible hacia la izquierda.

CASO 2:

Si el nodo no tiene hijo derecho, subimos utilizando los
punteros de padre.

Seguimos subiendo mientras el nodo sea hijo derecho.

El primer ancestro del cual venimos desde su hijo izquierdo
es el sucesor.

Si llegamos por encima de la raíz, no existe sucesor.

------------------------------------------------------------
COMO ENCONTRAR EL PREDECESOR:
------------------------------------------------------------

CASO 1:

Si el nodo tiene un hijo izquierdo, su predecesor es el
máximo de su subárbol izquierdo.

Para encontrar ese máximo:

    1. Avanzamos al hijo izquierdo.
    2. Bajamos todo lo posible hacia la derecha.

CASO 2:

Si el nodo no tiene hijo izquierdo, subimos utilizando los
punteros de padre.

Seguimos subiendo mientras el nodo sea hijo izquierdo.

El primer ancestro del cual venimos desde su hijo derecho
es el predecesor.

Si llegamos por encima de la raíz, no existe predecesor.

------------------------------------------------------------
ENTRADA:
------------------------------------------------------------

La primera línea contiene un entero n.

La segunda línea contiene n números enteros distintos,
en el orden en que deben insertarse en el ABB.

La tercera línea contiene un entero q.

Cada una de las siguientes q líneas contiene una clave x.

Se garantiza que todas las claves consultadas existen en
el árbol.

------------------------------------------------------------
SALIDA:
------------------------------------------------------------

Para cada consulta imprime:

    predecesor sucesor

Si no existe alguno de ellos, imprime NONE en su lugar.

------------------------------------------------------------
EJEMPLO DE ENTRADA:
------------------------------------------------------------

7
50 30 70 20 40 60 80
4
50
20
80
40

------------------------------------------------------------
ÁRBOL GENERADO:
------------------------------------------------------------

                    50
                  /    \
                30      70
               /  \    /  \
             20   40  60   80

------------------------------------------------------------
EJEMPLO DE SALIDA:
------------------------------------------------------------

40 60
NONE 30
70 NONE
30 50

------------------------------------------------------------
EXPLICACION:
------------------------------------------------------------

Consulta x = 50:

    El predecesor es el máximo del subárbol izquierdo:

        40

    El sucesor es el mínimo del subárbol derecho:

        60

    Respuesta: 40 60

Consulta x = 20:

    Es el menor valor del árbol, por lo tanto no tiene
    predecesor.

    Su sucesor es 30.

    Respuesta: NONE 30

Consulta x = 80:

    Su predecesor es 70.

    Es el mayor valor del árbol, por lo tanto no tiene
    sucesor.

    Respuesta: 70 NONE

Consulta x = 40:

    Su predecesor es 30.
    Su sucesor es 50.

    Respuesta: 30 50

------------------------------------------------------------
COMPLEJIDAD:
------------------------------------------------------------

Sea h la altura del árbol.

    Insertar: O(h)
    Buscar: O(h)
    Predecesor: O(h)
    Sucesor: O(h)

En un árbol aproximadamente balanceado:

    h = O(log n)

En el peor caso:

    h = O(n)

Memoria:

    O(n)

============================================================
SOLUCION EN C++
============================================================
*/

#include <iostream>

using namespace std;

class ABB
{
private:
    struct Nodo
    {
        int clave;

        Nodo* izquierdo;
        Nodo* derecho;
        Nodo* padre;

        Nodo(int valor)
        {
            clave = valor;

            izquierdo = nullptr;
            derecho = nullptr;
            padre = nullptr;
        }
    };

    Nodo* raiz;

    /*
    Busca un nodo utilizando la propiedad del ABB.
    */
    Nodo* buscarNodo(int clave) const
    {
        Nodo* actual = raiz;

        while (actual != nullptr)
        {
            if (clave == actual->clave)
            {
                return actual;
            }

            if (clave < actual->clave)
            {
                actual = actual->izquierdo;
            }
            else
            {
                actual = actual->derecho;
            }
        }

        return nullptr;
    }

    /*
    Devuelve el nodo mínimo de un subárbol.

    Para encontrarlo, avanzamos todo lo posible
    hacia la izquierda.
    */
    Nodo* minimo(Nodo* nodo) const
    {
        if (nodo == nullptr)
        {
            return nullptr;
        }

        while (nodo->izquierdo != nullptr)
        {
            nodo = nodo->izquierdo;
        }

        return nodo;
    }

    /*
    Devuelve el nodo máximo de un subárbol.

    Para encontrarlo, avanzamos todo lo posible
    hacia la derecha.
    */
    Nodo* maximo(Nodo* nodo) const
    {
        if (nodo == nullptr)
        {
            return nullptr;
        }

        while (nodo->derecho != nullptr)
        {
            nodo = nodo->derecho;
        }

        return nodo;
    }

    /*
    Libera todos los nodos utilizando postorder.
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
    ABB()
    {
        raiz = nullptr;
    }

    ~ABB()
    {
        liberar(raiz);
    }

    /*
    Inserta una clave y guarda correctamente el
    puntero hacia su padre.
    */
    void insertar(int clave)
    {
        Nodo* nuevo = new Nodo(clave);

        Nodo* padre = nullptr;
        Nodo* actual = raiz;

        /*
        Buscamos la posición donde se insertará
        el nuevo nodo.
        */
        while (actual != nullptr)
        {
            padre = actual;

            if (clave < actual->clave)
            {
                actual = actual->izquierdo;
            }
            else
            {
                actual = actual->derecho;
            }
        }

        nuevo->padre = padre;

        // El árbol estaba vacío.
        if (padre == nullptr)
        {
            raiz = nuevo;
        }

        // Insertar como hijo izquierdo.
        else if (clave < padre->clave)
        {
            padre->izquierdo = nuevo;
        }

        // Insertar como hijo derecho.
        else
        {
            padre->derecho = nuevo;
        }
    }

    /*
    Encuentra el sucesor de una clave.

    Devuelve true si existe.
    Devuelve false si la clave es el máximo del árbol.
    */
    bool sucesor(int clave, int& resultado) const
    {
        Nodo* nodo = buscarNodo(clave);

        /*
        CASO 1:

        Si tiene subárbol derecho, el sucesor es
        el mínimo de ese subárbol.
        */
        if (nodo->derecho != nullptr)
        {
            Nodo* siguiente = minimo(nodo->derecho);

            resultado = siguiente->clave;
            return true;
        }

        /*
        CASO 2:

        No tiene subárbol derecho.

        Subimos mientras el nodo actual sea hijo
        derecho de su padre.
        */
        Nodo* padre = nodo->padre;

        while (padre != nullptr &&
               nodo == padre->derecho)
        {
            nodo = padre;
            padre = padre->padre;
        }

        /*
        Si padre es nullptr, significa que la clave
        es el máximo del árbol.
        */
        if (padre == nullptr)
        {
            return false;
        }

        resultado = padre->clave;
        return true;
    }

    /*
    Encuentra el predecesor de una clave.

    Devuelve true si existe.
    Devuelve false si la clave es el mínimo del árbol.
    */
    bool predecesor(int clave, int& resultado) const
    {
        Nodo* nodo = buscarNodo(clave);

        /*
        CASO 1:

        Si tiene subárbol izquierdo, el predecesor
        es el máximo de ese subárbol.
        */
        if (nodo->izquierdo != nullptr)
        {
            Nodo* anterior = maximo(nodo->izquierdo);

            resultado = anterior->clave;
            return true;
        }

        /*
        CASO 2:

        No tiene subárbol izquierdo.

        Subimos mientras el nodo actual sea hijo
        izquierdo de su padre.
        */
        Nodo* padre = nodo->padre;

        while (padre != nullptr &&
               nodo == padre->izquierdo)
        {
            nodo = padre;
            padre = padre->padre;
        }

        /*
        Si padre es nullptr, significa que la clave
        es el mínimo del árbol.
        */
        if (padre == nullptr)
        {
            return false;
        }

        resultado = padre->clave;
        return true;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    ABB arbol;

    // Construimos el ABB.
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
        int x;
        cin >> x;

        int valorPredecesor = 0;
        int valorSucesor = 0;

        bool tienePredecesor =
            arbol.predecesor(x, valorPredecesor);

        bool tieneSucesor =
            arbol.sucesor(x, valorSucesor);

        // El enunciado pide primero el predecesor.
        if (tienePredecesor)
        {
            cout << valorPredecesor;
        }
        else
        {
            cout << "NONE";
        }

        cout << ' ';

        // Después se imprime el sucesor.
        if (tieneSucesor)
        {
            cout << valorSucesor;
        }
        else
        {
            cout << "NONE";
        }

        cout << '\n';
    }

    return 0;
}