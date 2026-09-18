/*
============================================================
D. PISO Y TECHO
============================================================

ENUNCIADO:

Se proporcionan n números enteros distintos.

Los números deben insertarse, uno por uno y en el orden
recibido, en un Árbol Binario de Búsqueda (ABB).

Después de construir el árbol, se deben responder q
consultas.

Cada consulta contiene un valor x, que puede existir o no
dentro del árbol.

Para cada consulta se debe encontrar:

1. PISO DE x:

   El mayor valor del árbol que sea menor o igual que x.

   Es decir:

       piso <= x

   Si no existe, se imprime NONE.

2. TECHO DE x:

   El menor valor del árbol que sea mayor o igual que x.

   Es decir:

       techo >= x

   Si no existe, se imprime NONE.

------------------------------------------------------------
PROPIEDAD DEL ABB:
------------------------------------------------------------

Para cada nodo se cumple:

    valores menores -> subárbol izquierdo
    valores mayores -> subárbol derecho

Es decir:

    izquierdo < raíz < derecho

------------------------------------------------------------
ENTRADA:
------------------------------------------------------------

La primera línea contiene un entero n.

La segunda línea contiene n enteros distintos, en el orden
en que deben insertarse en el ABB.

La tercera línea contiene un entero q.

La cuarta línea contiene q valores que deben consultarse.

Los valores consultados no necesariamente existen dentro
del árbol.

------------------------------------------------------------
SALIDA:
------------------------------------------------------------

Por cada consulta imprime dos valores:

    piso techo

Si no existe el piso o el techo, imprime NONE en su lugar.

------------------------------------------------------------
EJEMPLO DE ENTRADA:
------------------------------------------------------------

9
50 30 70 20 40 60 80 10 90
5
45 30 5 95 10

------------------------------------------------------------
ÁRBOL GENERADO:
------------------------------------------------------------

                    50
                  /    \
                30      70
               /  \    /  \
             20   40  60   80
            /                 \
          10                   90

------------------------------------------------------------
EJEMPLO DE SALIDA:
------------------------------------------------------------

40 50
30 30
NONE 10
90 NONE
10 10

------------------------------------------------------------
EXPLICACION:
------------------------------------------------------------

Consulta x = 45:

    El mayor valor menor o igual que 45 es 40.
    El menor valor mayor o igual que 45 es 50.

    Piso = 40
    Techo = 50

Consulta x = 30:

    El valor 30 existe en el árbol.

    Piso = 30
    Techo = 30

Consulta x = 5:

    No existe ningún valor menor o igual que 5.
    El menor valor mayor o igual que 5 es 10.

    Piso = NONE
    Techo = 10

Consulta x = 95:

    El mayor valor menor o igual que 95 es 90.
    No existe ningún valor mayor o igual que 95.

    Piso = 90
    Techo = NONE

------------------------------------------------------------
IDEA PARA ENCONTRAR EL PISO Y EL TECHO:
------------------------------------------------------------

Comenzamos en la raíz.

CASO 1:

    x == clave del nodo

Entonces:

    piso = x
    techo = x

Podemos terminar la búsqueda.

CASO 2:

    x < clave del nodo

El nodo actual puede ser el techo.

Guardamos su valor como candidato a techo y avanzamos
hacia el hijo izquierdo para intentar encontrar un valor
más pequeño que todavía sea mayor o igual que x.

CASO 3:

    x > clave del nodo

El nodo actual puede ser el piso.

Guardamos su valor como candidato a piso y avanzamos
hacia el hijo derecho para intentar encontrar un valor
más grande que todavía sea menor o igual que x.

------------------------------------------------------------
COMPLEJIDAD:
------------------------------------------------------------

Si el árbol está aproximadamente balanceado:

    Insertar: O(log n)
    Consulta: O(log n)

En el peor caso, si el árbol forma una cadena:

    Insertar: O(n)
    Consulta: O(n)

Memoria para almacenar el árbol:

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

        Nodo(int valor)
        {
            clave = valor;
            izquierdo = nullptr;
            derecho = nullptr;
        }
    };

    Nodo* raiz;

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
    ABB()
    {
        raiz = nullptr;
    }

    ~ABB()
    {
        liberar(raiz);
    }

    /*
    Inserta una clave utilizando el procedimiento estándar
    de inserción en un ABB.
    */
    void insertar(int clave)
    {
        Nodo* nuevo = new Nodo(clave);

        // Si el árbol está vacío, el nuevo nodo será la raíz.
        if (raiz == nullptr)
        {
            raiz = nuevo;
            return;
        }

        Nodo* actual = raiz;

        while (true)
        {
            if (clave < actual->clave)
            {
                if (actual->izquierdo == nullptr)
                {
                    actual->izquierdo = nuevo;
                    return;
                }

                actual = actual->izquierdo;
            }
            else
            {
                /*
                Las claves son distintas, por lo tanto,
                en este caso clave > actual->clave.
                */

                if (actual->derecho == nullptr)
                {
                    actual->derecho = nuevo;
                    return;
                }

                actual = actual->derecho;
            }
        }
    }

    /*
    Busca simultáneamente el piso y el techo de x.

    tienePiso será true si se encontró un piso.
    tieneTecho será true si se encontró un techo.

    piso y techo guardarán los valores encontrados.
    */
    void buscarPisoTecho(
        int x,
        bool& tienePiso,
        int& piso,
        bool& tieneTecho,
        int& techo
    ) const
    {
        tienePiso = false;
        tieneTecho = false;

        Nodo* actual = raiz;

        while (actual != nullptr)
        {
            /*
            Si encontramos exactamente x, entonces x es
            simultáneamente su piso y su techo.
            */
            if (x == actual->clave)
            {
                piso = actual->clave;
                techo = actual->clave;

                tienePiso = true;
                tieneTecho = true;

                return;
            }

            /*
            Si x es menor que el nodo actual, el nodo puede
            ser un candidato a techo.

            Después avanzamos a la izquierda para intentar
            encontrar un techo más pequeño.
            */
            if (x < actual->clave)
            {
                techo = actual->clave;
                tieneTecho = true;

                actual = actual->izquierdo;
            }

            /*
            Si x es mayor que el nodo actual, el nodo puede
            ser un candidato a piso.

            Después avanzamos a la derecha para intentar
            encontrar un piso más grande.
            */
            else
            {
                piso = actual->clave;
                tienePiso = true;

                actual = actual->derecho;
            }
        }
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    ABB arbol;

    // Insertamos las n claves.
    for (int i = 0; i < n; i++)
    {
        int clave;
        cin >> clave;

        arbol.insertar(clave);
    }

    int q;
    cin >> q;

    // Procesamos las q consultas.
    for (int i = 0; i < q; i++)
    {
        int x;
        cin >> x;

        bool tienePiso;
        bool tieneTecho;

        int piso = 0;
        int techo = 0;

        arbol.buscarPisoTecho(
            x,
            tienePiso,
            piso,
            tieneTecho,
            techo
        );

        // Imprimir el piso.
        if (tienePiso)
        {
            cout << piso;
        }
        else
        {
            cout << "NONE";
        }

        cout << ' ';

        // Imprimir el techo.
        if (tieneTecho)
        {
            cout << techo;
        }
        else
        {
            cout << "NONE";
        }

        cout << '\n';
    }

    return 0;
}