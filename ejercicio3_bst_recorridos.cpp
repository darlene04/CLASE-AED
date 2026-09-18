/*
============================================================
3. BST: RECORRIDOS INORDER, PREORDER Y POSTORDER
============================================================

ENUNCIADO:

Se proporcionan n números enteros que deben insertarse en un
Árbol Binario de Búsqueda (BST).

Después de construir el árbol, imprime sus elementos usando
los siguientes recorridos:

    1. Inorder.
    2. Preorder.
    3. Postorder.

Cada recorrido debe imprimirse en una línea diferente.

------------------------------------------------------------
PROPIEDAD DEL BST:
------------------------------------------------------------

Para cada nodo se cumple:

    claves menores -> subárbol izquierdo
    claves mayores -> subárbol derecho

Es decir:

    izquierdo < raíz < derecho

------------------------------------------------------------
RECORRIDOS:
------------------------------------------------------------

INORDER:

    Izquierda - Raíz - Derecha

En un BST, produce las claves ordenadas de menor a mayor.

PREORDER:

    Raíz - Izquierda - Derecha

Visita primero la raíz. Es útil para copiar o guardar la
estructura de un árbol.

POSTORDER:

    Izquierda - Derecha - Raíz

Visita la raíz al final. Es útil para eliminar todos los
nodos de un árbol.

------------------------------------------------------------
ENTRADA:
------------------------------------------------------------

La primera línea contiene un número entero n, que representa
la cantidad de claves.

La segunda línea contiene n números enteros que deben
insertarse en el BST.

------------------------------------------------------------
SALIDA:
------------------------------------------------------------

Imprime tres líneas:

    Inorder: recorrido inorder
    Preorder: recorrido preorder
    Postorder: recorrido postorder

------------------------------------------------------------
EJEMPLO DE ENTRADA:
------------------------------------------------------------

7
40 20 60 10 30 50 70

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

Inorder: 10 20 30 40 50 60 70
Preorder: 40 20 10 30 60 50 70
Postorder: 10 30 20 50 70 60 40

------------------------------------------------------------
EXPLICACION:
------------------------------------------------------------

INORDER:

    Izquierda - Raíz - Derecha

Primero recorremos el subárbol izquierdo de 40:

    10 20 30

Después visitamos la raíz:

    40

Finalmente recorremos el subárbol derecho:

    50 60 70

Resultado:

    10 20 30 40 50 60 70

------------------------------------------------------------

PREORDER:

    Raíz - Izquierda - Derecha

Primero visitamos la raíz:

    40

Después recorremos el subárbol izquierdo:

    20 10 30

Finalmente recorremos el subárbol derecho:

    60 50 70

Resultado:

    40 20 10 30 60 50 70

------------------------------------------------------------

POSTORDER:

    Izquierda - Derecha - Raíz

Primero recorremos el subárbol izquierdo:

    10 30 20

Después recorremos el subárbol derecho:

    50 70 60

Finalmente visitamos la raíz:

    40

Resultado:

    10 30 20 50 70 60 40

------------------------------------------------------------
COMPLEJIDAD:
------------------------------------------------------------

Cada recorrido visita todos los nodos una sola vez:

    Tiempo: O(n)

La memoria auxiliar depende de la altura h del árbol:

    Memoria: O(h)

Si está balanceado:

    h = O(log n)

En el peor caso:

    h = O(n)

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
    Inserta una clave en el BST.
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

        return nodo;
    }

    /*
    INORDER:

        Izquierda - Raíz - Derecha
    */
    void inorder(Nodo* nodo) const
    {
        if (nodo == nullptr)
        {
            return;
        }

        inorder(nodo->izquierdo);

        cout << nodo->clave << ' ';

        inorder(nodo->derecho);
    }

    /*
    PREORDER:

        Raíz - Izquierda - Derecha
    */
    void preorder(Nodo* nodo) const
    {
        if (nodo == nullptr)
        {
            return;
        }

        cout << nodo->clave << ' ';

        preorder(nodo->izquierdo);

        preorder(nodo->derecho);
    }

    /*
    POSTORDER:

        Izquierda - Derecha - Raíz
    */
    void postorder(Nodo* nodo) const
    {
        if (nodo == nullptr)
        {
            return;
        }

        postorder(nodo->izquierdo);

        postorder(nodo->derecho);

        cout << nodo->clave << ' ';
    }

    /*
    Libera la memoria de todos los nodos.
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

    void imprimirInorder() const
    {
        cout << "Inorder: ";
        inorder(raiz);
        cout << '\n';
    }

    void imprimirPreorder() const
    {
        cout << "Preorder: ";
        preorder(raiz);
        cout << '\n';
    }

    void imprimirPostorder() const
    {
        cout << "Postorder: ";
        postorder(raiz);
        cout << '\n';
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

    // Imprimimos los tres recorridos.
    arbol.imprimirInorder();
    arbol.imprimirPreorder();
    arbol.imprimirPostorder();

    return 0;
}