/*
============================================================
E. ELIMINAR NODOS
============================================================

ENUNCIADO:

Se debe simular un Árbol Binario de Búsqueda (ABB) de
números enteros, inicialmente vacío.

Se deben procesar m operaciones en el orden recibido.

Existen tres tipos de operaciones:

1. INSERTAR x

   Inserta el valor x dentro del ABB.

   Se garantiza que x no se encuentra actualmente
   dentro del árbol.

2. ELIMINAR x

   Elimina el valor x del ABB utilizando el algoritmo
   estándar de eliminación.

   Se garantiza que x existe actualmente en el árbol.

3. EXISTE x

   Determina si el valor x está actualmente en el árbol.

   Imprime SI si existe y NO si no existe.

Después de procesar todas las operaciones, se debe imprimir
el recorrido inorder del árbol resultante.

Si el árbol queda vacío, se debe imprimir VACIO.

------------------------------------------------------------
PROPIEDAD DEL ABB:
------------------------------------------------------------

Para cada nodo se cumple:

    valores menores -> subárbol izquierdo
    valores mayores -> subárbol derecho

Es decir:

    izquierdo < raíz < derecho

------------------------------------------------------------
CASOS DE ELIMINACION:
------------------------------------------------------------

CASO 1: NODO SIN HIJO IZQUIERDO

El nodo puede ser:

    - Una hoja.
    - Un nodo que solamente tiene hijo derecho.

Se reemplaza el nodo por su hijo derecho.

Si es una hoja, su hijo derecho es nullptr.

------------------------------------------------------------

CASO 2: NODO SIN HIJO DERECHO

El nodo solamente tiene hijo izquierdo.

Se reemplaza el nodo por su hijo izquierdo.

------------------------------------------------------------

CASO 3: NODO CON DOS HIJOS

Se busca el sucesor inorder:

    El menor nodo del subárbol derecho.

Después se coloca el sucesor en la posición del nodo
que queremos eliminar.

------------------------------------------------------------
OPERACION TRANSPLANTAR:
------------------------------------------------------------

Transplantar(u, v) reemplaza el subárbol cuya raíz es u
por el subárbol cuya raíz es v.

También actualiza:

    - El enlace del padre de u.
    - La raíz, si u era la raíz.
    - El padre de v, si v no es nullptr.

------------------------------------------------------------
ENTRADA:
------------------------------------------------------------

La primera línea contiene un número entero m, que representa
la cantidad de operaciones.

Cada una de las siguientes m líneas contiene una operación:

    INSERTAR x
    ELIMINAR x
    EXISTE x

------------------------------------------------------------
SALIDA:
------------------------------------------------------------

Por cada operación EXISTE, imprime:

    SI

si el valor está presente, o:

    NO

si el valor no está presente.

Después de todas las operaciones, imprime el recorrido
inorder del árbol.

Si el árbol está vacío, imprime:

    VACIO

------------------------------------------------------------
EJEMPLO DE ENTRADA:
------------------------------------------------------------

24
INSERTAR 50
INSERTAR 30
INSERTAR 70
INSERTAR 20
INSERTAR 40
INSERTAR 60
INSERTAR 80
INSERTAR 35
INSERTAR 45
INSERTAR 65
EXISTE 45
EXISTE 100
ELIMINAR 20
EXISTE 20
ELIMINAR 60
EXISTE 60
EXISTE 65
ELIMINAR 50
EXISTE 50
EXISTE 65
ELIMINAR 40
EXISTE 40
EXISTE 45
EXISTE 35

------------------------------------------------------------
EJEMPLO DE SALIDA:
------------------------------------------------------------

SI
NO
NO
NO
SI
NO
SI
NO
SI
SI
30 35 45 65 70 80

------------------------------------------------------------
COMPLEJIDAD:
------------------------------------------------------------

Sea h la altura del árbol.

    INSERTAR: O(h)
    ELIMINAR: O(h)
    EXISTE: O(h)
    INORDER: O(n)

Si el árbol está aproximadamente balanceado:

    h = O(log n)

En el peor caso, el árbol puede formar una cadena:

    h = O(n)

Memoria utilizada:

    O(n)

============================================================
SOLUCION EN C++
============================================================
*/

#include <iostream>
#include <string>

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
    Busca una clave dentro del árbol.

    Devuelve un puntero al nodo si lo encuentra.

    Devuelve nullptr si no existe.
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
    Encuentra el nodo con la clave mínima de un subárbol.

    Para encontrar el mínimo, avanzamos todo lo posible
    hacia la izquierda.
    */
    Nodo* minimo(Nodo* nodo) const
    {
        while (nodo->izquierdo != nullptr)
        {
            nodo = nodo->izquierdo;
        }

        return nodo;
    }

    /*
    Reemplaza el subárbol con raíz u por el subárbol
    con raíz v.

    Esta operación NO conecta los hijos de u con v.
    Esas conexiones se realizan en eliminar().
    */
    void transplantar(Nodo* u, Nodo* v)
    {
        /*
        Si u no tiene padre, significa que u es la raíz.

        Por lo tanto, v se convierte en la nueva raíz.
        */
        if (u->padre == nullptr)
        {
            raiz = v;
        }

        /*
        Si u es el hijo izquierdo de su padre,
        reemplazamos el enlace izquierdo.
        */
        else if (u == u->padre->izquierdo)
        {
            u->padre->izquierdo = v;
        }

        /*
        Si no es hijo izquierdo, entonces es hijo derecho.
        */
        else
        {
            u->padre->derecho = v;
        }

        /*
        Si v existe, actualizamos su padre.
        */
        if (v != nullptr)
        {
            v->padre = u->padre;
        }
    }

    /*
    Recorrido inorder:

        Izquierda - Raíz - Derecha

    La variable primero sirve para imprimir los espacios
    correctamente.
    */
    void inorder(Nodo* nodo, bool& primero) const
    {
        if (nodo == nullptr)
        {
            return;
        }

        inorder(nodo->izquierdo, primero);

        if (!primero)
        {
            cout << ' ';
        }

        cout << nodo->clave;
        primero = false;

        inorder(nodo->derecho, primero);
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
    Inserción estándar en un ABB.
    */
    void insertar(int clave)
    {
        Nodo* nuevo = new Nodo(clave);

        Nodo* padre = nullptr;
        Nodo* actual = raiz;

        /*
        Buscamos el lugar donde debe insertarse
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

        // Guardamos el padre del nuevo nodo.
        nuevo->padre = padre;

        /*
        Si no existe un padre, el árbol estaba vacío.

        El nuevo nodo se convierte en la raíz.
        */
        if (padre == nullptr)
        {
            raiz = nuevo;
        }

        /*
        Conectamos el nuevo nodo como hijo izquierdo
        o derecho.
        */
        else if (clave < padre->clave)
        {
            padre->izquierdo = nuevo;
        }
        else
        {
            padre->derecho = nuevo;
        }
    }

    /*
    Comprueba si una clave existe dentro del ABB.
    */
    bool existe(int clave) const
    {
        return buscarNodo(clave) != nullptr;
    }

    /*
    Elimina una clave del ABB.

    El enunciado garantiza que la clave existe.
    */
    void eliminar(int clave)
    {
        Nodo* objetivo = buscarNodo(clave);

        /*
        CASO 1:

        El nodo no tiene hijo izquierdo.

        Esto incluye:

            - Nodo hoja.
            - Nodo con solamente hijo derecho.
        */
        if (objetivo->izquierdo == nullptr)
        {
            transplantar(
                objetivo,
                objetivo->derecho
            );
        }

        /*
        CASO 2:

        El nodo tiene hijo izquierdo, pero no tiene
        hijo derecho.
        */
        else if (objetivo->derecho == nullptr)
        {
            transplantar(
                objetivo,
                objetivo->izquierdo
            );
        }

        /*
        CASO 3:

        El nodo tiene dos hijos.
        */
        else
        {
            /*
            El sucesor es el mínimo del subárbol derecho.
            */
            Nodo* sucesor = minimo(objetivo->derecho);

            /*
            Si el sucesor no es hijo directo del objetivo,
            primero debemos reemplazar el sucesor por su
            posible hijo derecho.
            */
            if (sucesor->padre != objetivo)
            {
                transplantar(
                    sucesor,
                    sucesor->derecho
                );

                /*
                Conectamos el subárbol derecho del objetivo
                como hijo derecho del sucesor.
                */
                sucesor->derecho = objetivo->derecho;
                sucesor->derecho->padre = sucesor;
            }

            /*
            Reemplazamos el objetivo por el sucesor.

            Esta operación también actualiza la raíz
            cuando el objetivo era la raíz.
            */
            transplantar(
                objetivo,
                sucesor
            );

            /*
            Conectamos el subárbol izquierdo del objetivo
            como hijo izquierdo del sucesor.
            */
            sucesor->izquierdo = objetivo->izquierdo;
            sucesor->izquierdo->padre = sucesor;
        }

        // Liberamos la memoria del nodo eliminado.
        delete objetivo;
    }

    /*
    Imprime el recorrido inorder.

    Si el árbol está vacío, imprime VACIO.
    */
    void imprimirInorder() const
    {
        if (raiz == nullptr)
        {
            cout << "VACIO\n";
            return;
        }

        bool primero = true;

        inorder(raiz, primero);

        cout << '\n';
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m;
    cin >> m;

    ABB arbol;

    for (int i = 0; i < m; i++)
    {
        string operacion;
        int valor;

        cin >> operacion >> valor;

        if (operacion == "INSERTAR")
        {
            arbol.insertar(valor);
        }
        else if (operacion == "ELIMINAR")
        {
            arbol.eliminar(valor);
        }
        else if (operacion == "EXISTE")
        {
            if (arbol.existe(valor))
            {
                cout << "SI\n";
            }
            else
            {
                cout << "NO\n";
            }
        }
    }

    // Después de todas las operaciones, imprimimos el árbol.
    arbol.imprimirInorder();

    return 0;
}