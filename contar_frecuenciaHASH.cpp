/*
PROBLEMA A: CONTAR FRECUENCIAS

Se proporciona un arreglo de n números enteros a1, a2, ..., an,
seguido de q consultas.

Cada consulta contiene un número entero x. Para cada consulta,
se debe determinar cuántas veces aparece el valor x dentro del arreglo.

ENTRADA:

La primera línea contiene dos números enteros n y q:

    1 <= n, q <= 10^6

La segunda línea contiene n números enteros que representan
los elementos del arreglo:

    a1, a2, ..., an
    1 <= ai <= 10^9

La tercera línea contiene q números enteros que representan
las consultas:

    x1, x2, ..., xq
    1 <= xj <= 10^9

SALIDA:

Se deben imprimir q líneas.

En la j-esima línea se debe imprimir la cantidad de veces
que el valor xj aparece dentro del arreglo.

EJEMPLO DE ENTRADA:

5 3
4 2 4 7 4
4 2 9

EJEMPLO DE SALIDA:

3
1
0

EXPLICACION:

El arreglo es:

    [4, 2, 4, 7, 4]

- El número 4 aparece 3 veces.
- El número 2 aparece 1 vez.
- El número 9 aparece 0 veces.

Por eso, las respuestas son 3, 1 y 0.
*/
#include <iostream>
using namespace std;
//merge sort --(modificar la lista)

//temrino de el polinomio
struct termino
{
    long long exponente;
    long long coeficiente;

    termino() = default;

    termino(long long e, long long c)
    {
        exponente = e;
        coeficiente = c;
    }
};


// ==========================================
// LISTA ENLAZADA SIMPLE
// ==========================================
template <class T>
class linked_list
{
    struct node
    {
        T dato;
        node* next = nullptr;

        node(const T& d, node* n = nullptr)
        {
            dato = d;
            next = n;
        }
    };


    node* head = nullptr;
    node* tail = nullptr;


public:

    linked_list() = default;


    // ======================================
    // PUSH BACK
    // ======================================
    void push_back(const T& d)
    {
        node* nuevo = new node(d);


        if (head == nullptr)
        {
            head = nuevo;
            tail = nuevo;
        }
        else
        {
            tail->next = nuevo;
            tail = nuevo;
        }
    }


    // ======================================
    // RETORNAR HEAD
    // ======================================
    node* get_head() const
    {
        return head;
    }


    // ======================================
    // IMPRIMIR POLINOMIO
    // ======================================
    friend ostream& operator<<(ostream& os,
                               const linked_list<T>& ll)
    {
        for (node* n = ll.head;
             n != nullptr;
             n = n->next)
        {
            os << n->dato.exponente
               << " "
               << n->dato.coeficiente
               << endl;
        }

        return os;
    }


    // ======================================
    // DESTRUCTOR
    // ======================================
    ~linked_list()
    {
        node* actual = head;

        while (actual != nullptr)
        {
            node* siguiente = actual->next;

            delete actual;

            actual = siguiente;
        }
    }


    // ======================================
    // FUNCION PARA SUMAR DOS LISTAS
    // ======================================
    static linked_list<T>* sumar(
            const linked_list<T>& P,
            const linked_list<T>& Q)
    {
        linked_list<T>* resultado =
                new linked_list<T>();


        node* p = P.head;
        node* q = Q.head;


        while (p != nullptr &&
               q != nullptr)
        {
            // Exponente de P menor
            if (p->dato.exponente <
                q->dato.exponente)
            {
                resultado->push_back(p->dato);

                p = p->next;
            }

                // Exponente de Q menor
            else if (q->dato.exponente <
                     p->dato.exponente)
            {
                resultado->push_back(q->dato);

                q = q->next;
            }

                // Mismo exponente
            else
            {
                long long suma =
                        p->dato.coeficiente +
                        q->dato.coeficiente;


                if (suma != 0)
                {
                    termino nuevoTermino(
                            p->dato.exponente,
                            suma
                    );

                    resultado->push_back(
                            nuevoTermino
                    );
                }


                p = p->next;
                q = q->next;
            }
        }


        // Si quedan términos en P
        while (p != nullptr)
        {
            resultado->push_back(p->dato);

            p = p->next;
        }


        // Si quedan términos en Q
        while (q != nullptr)
        {
            resultado->push_back(q->dato);

            q = q->next;
        }


        return resultado;
    }


    // ======================================
    // CONTAR ELEMENTOS
    // ======================================
    int size() const
    {
        int cantidad = 0;

        node* actual = head;

        while (actual != nullptr)
        {
            cantidad++;

            actual = actual->next;
        }

        return cantidad;
    }
};


// ==========================================
// MAIN
// ==========================================
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    linked_list<termino> P;
    linked_list<termino> Q;


    // ======================================
    // LEER P
    // ======================================
    int n1;

    cin >> n1;


    for (int i = 0; i < n1; i++)
    {
        long long exponente;
        long long coeficiente;

        cin >> exponente >> coeficiente;


        termino nuevo(
                exponente,
                coeficiente
        );


        P.push_back(nuevo);
    }


    // ======================================
    // LEER Q
    // ======================================
    int n2;

    cin >> n2;


    for (int i = 0; i < n2; i++)
    {
        long long exponente;
        long long coeficiente;

        cin >> exponente >> coeficiente;


        termino nuevo(
                exponente,
                coeficiente
        );


        Q.push_back(nuevo);
    }


    // ======================================
    // SUMAR
    // ======================================
    linked_list<termino>* R =
            linked_list<termino>::sumar(P, Q);


    // ======================================
    // IMPRIMIR
    // ======================================
    cout << R->size() << endl;

    cout << *R;


    delete R;


    return 0;
}