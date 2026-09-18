/*
============================================================
1. BST: INSERCION Y RECORRIDO INORDER
============================================================

ENUNCIADO:

Se proporcionan n números enteros distintos.

Inserta todos los números, en el orden recibido, dentro de
un Árbol Binario de Búsqueda (BST).

Después de construir el árbol, imprime sus elementos
utilizando el recorrido inorder.

------------------------------------------------------------
PROPIEDAD DEL BST:
------------------------------------------------------------

En cada nodo se cumple:

    claves menores  -> subárbol izquierdo
    claves mayores  -> subárbol derecho

Es decir:

    izquierdo < raíz < derecho

------------------------------------------------------------
RECORRIDO INORDER:
------------------------------------------------------------

El recorrido inorder visita los nodos en este orden:

    1. Subárbol izquierdo.
    2. Nodo actual o raíz.
    3. Subárbol derecho.

Se puede recordar como:

    Izquierda - Raíz - Derecha

En un BST, el recorrido inorder imprime las claves de
menor a mayor.

------------------------------------------------------------
ENTRADA:
------------------------------------------------------------

La primera línea contiene un número entero n, que representa
la cantidad de claves.

La segunda línea contiene n números enteros distintos,
que serán insertados en el BST.

------------------------------------------------------------
SALIDA:
------------------------------------------------------------

Imprime las claves del BST ordenadas de menor a mayor,
separadas por espacios.

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

10 20 30 40 50 60 70

------------------------------------------------------------
EXPLICACION:
------------------------------------------------------------

Insertamos los números en el orden recibido.

Insertar 40:

    Como el árbol está vacío, 40 se convierte en la raíz.

Insertar 20:

    20 < 40

    Por lo tanto, se coloca a la izquierda de 40.

Insertar 60:

    60 > 40

    Por lo tanto, se coloca a la derecha de 40.

Insertar 10:

    10 < 40
    10 < 20

    Se coloca a la izquierda de 20.

Insertar 30:

    30 < 40
    30 > 20

    Se coloca a la derecha de 20.

Insertar 50:

    50 > 40
    50 < 60

    Se coloca a la izquierda de 60.

Insertar 70:

    70 > 40
    70 > 60

    Se coloca a la derecha de 60.

Finalmente, realizamos el recorrido inorder:

    Izquierda - Raíz - Derecha

Resultado:

    10 20 30 40 50 60 70

------------------------------------------------------------
COMPLEJIDAD:
------------------------------------------------------------

Si el árbol está aproximadamente balanceado:

    Inserción: O(log n)
    Construcción completa: O(n log n)
    Recorrido inorder: O(n)

En el peor caso, si las claves se insertan ordenadas:

    Inserción: O(n)
    Construcción completa: O(n²)

La memoria utilizada es:

    O(n)

============================================================
SOLUCION EN C++
============================================================
*/

#include <iostream>

using namespace std;

class BST
{
private:
    /*
    Cada nodo guarda:

    - Una clave.
    - Un puntero al hijo izquierdo.
    - Un puntero al hijo derecho.
    */
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

    // Puntero a la raíz del árbol.
    Nodo* raiz;

    /*
    Función recursiva que inserta una clave.

    Devuelve la raíz actualizada del subárbol.
    */
    Nodo* insertar(Nodo* nodo, int clave)
    {
        // Si encontramos un espacio vacío, creamos el nodo.
        if (nodo == nullptr)
        {
            return new Nodo(clave);
        }

        // Si la clave es menor, avanzamos a la izquierda.
        if (clave < nodo->clave)
        {
            nodo->izquierdo =
                insertar(nodo->izquierdo, clave);
        }

        // Si la clave es mayor, avanzamos a la derecha.
        else if (clave > nodo->clave)
        {
            nodo->derecho =
                insertar(nodo->derecho, clave);
        }

        /*
        Si la clave es igual, no hacemos nada.

        En este BST no se almacenan claves duplicadas.
        */

        return nodo;
    }

    /*
    Recorrido inorder:

        Izquierda - Raíz - Derecha
    */
    void inorder(Nodo* nodo) const
    {
        // Caso base: no hay ningún nodo.
        if (nodo == nullptr)
        {
            return;
        }

        // 1. Recorrer el subárbol izquierdo.
        inorder(nodo->izquierdo);

        // 2. Procesar la raíz.
        cout << nodo->clave << ' ';

        // 3. Recorrer el subárbol derecho.
        inorder(nodo->derecho);
    }

    /*
    Libera todos los nodos del árbol.

    Se utiliza postorder:

        Izquierda - Derecha - Raíz
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
    Constructor:

    El árbol comienza vacío.
    */
    BST()
    {
        raiz = nullptr;
    }

    /*
    Destructor:

    Libera la memoria de todos los nodos.
    */
    ~BST()
    {
        liberar(raiz);
    }

    /*
    Método público para insertar una clave.
    */
    void insertar(int clave)
    {
        raiz = insertar(raiz, clave);
    }

    /*
    Método público para imprimir el recorrido inorder.
    */
    void inorder() const
    {
        inorder(raiz);
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

    // Leemos e insertamos las n claves.
    for (int i = 0; i < n; i++)
    {
        int clave;
        cin >> clave;

        arbol.insertar(clave);
    }

    // Imprimimos las claves de menor a mayor.
    arbol.inorder();

    return 0;
}