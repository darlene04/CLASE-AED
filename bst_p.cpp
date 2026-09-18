#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>
#include <stdexcept>
#include <utility>
#include <vector>

using namespace std;

// ============================================================================
// BINARY SEARCH TREE (BST) COMPLETO
// Regla: claves menores a la izquierda y mayores a la derecha.
// Esta implementacion NO guarda claves duplicadas: si una clave ya existe,
// insertar() devuelve false. Usa operator[] si deseas insertar o actualizar.
// ============================================================================
template <typename Clave, typename Valor>
class BST {
private:
    struct Nodo {
        Clave clave;
        Valor valor;
        Nodo* izquierdo = nullptr;
        Nodo* derecho = nullptr;

        Nodo(const Clave& c, const Valor& v) : clave(c), valor(v) {}
    };

    Nodo* raiz = nullptr;
    size_t cantidad = 0;

    // Devuelve la direccion del puntero que apunta al nodo buscado.
    // Si no existe, devuelve la direccion del nullptr donde se insertaria.
    Nodo** buscarEnlace(const Clave& clave) {
        Nodo** actual = &raiz;

        while (*actual != nullptr && (*actual)->clave != clave) {
            if (clave < (*actual)->clave) {
                actual = &((*actual)->izquierdo);
            } else {
                actual = &((*actual)->derecho);
            }
        }
        return actual;
    }

    const Nodo* buscarNodo(const Clave& clave) const {
        const Nodo* actual = raiz;
        while (actual != nullptr && actual->clave != clave) {
            actual = clave < actual->clave
                         ? actual->izquierdo
                         : actual->derecho;
        }
        return actual;
    }

    static Nodo* minimoNodo(Nodo* nodo) {
        if (nodo == nullptr) return nullptr;
        while (nodo->izquierdo != nullptr) nodo = nodo->izquierdo;
        return nodo;
    }

    static const Nodo* minimoNodo(const Nodo* nodo) {
        if (nodo == nullptr) return nullptr;
        while (nodo->izquierdo != nullptr) nodo = nodo->izquierdo;
        return nodo;
    }

    static const Nodo* maximoNodo(const Nodo* nodo) {
        if (nodo == nullptr) return nullptr;
        while (nodo->derecho != nullptr) nodo = nodo->derecho;
        return nodo;
    }

    static void liberar(Nodo* nodo) {
        if (nodo == nullptr) return;
        liberar(nodo->izquierdo);
        liberar(nodo->derecho);
        delete nodo;
    }

    static Nodo* clonar(const Nodo* nodo) {
        if (nodo == nullptr) return nullptr;
        Nodo* copia = new Nodo(nodo->clave, nodo->valor);
        copia->izquierdo = clonar(nodo->izquierdo);
        copia->derecho = clonar(nodo->derecho);
        return copia;
    }

    static int altura(const Nodo* nodo) {
        // Altura medida en aristas: arbol vacio = -1, hoja = 0.
        if (nodo == nullptr) return -1;
        return 1 + max(altura(nodo->izquierdo), altura(nodo->derecho));
    }

    static size_t contarHojas(const Nodo* nodo) {
        if (nodo == nullptr) return 0;
        if (nodo->izquierdo == nullptr && nodo->derecho == nullptr) return 1;
        return contarHojas(nodo->izquierdo) + contarHojas(nodo->derecho);
    }

    static void inorder(const Nodo* nodo, vector<Clave>& resultado) {
        if (nodo == nullptr) return;
        inorder(nodo->izquierdo, resultado);
        resultado.push_back(nodo->clave);
        inorder(nodo->derecho, resultado);
    }

    static void preorder(const Nodo* nodo, vector<Clave>& resultado) {
        if (nodo == nullptr) return;
        resultado.push_back(nodo->clave);
        preorder(nodo->izquierdo, resultado);
        preorder(nodo->derecho, resultado);
    }

    static void postorder(const Nodo* nodo, vector<Clave>& resultado) {
        if (nodo == nullptr) return;
        postorder(nodo->izquierdo, resultado);
        postorder(nodo->derecho, resultado);
        resultado.push_back(nodo->clave);
    }

    static bool esBST(const Nodo* nodo, const Clave* minimo,
                      const Clave* maximo) {
        if (nodo == nullptr) return true;
        if (minimo != nullptr && !(nodo->clave > *minimo)) return false;
        if (maximo != nullptr && !(nodo->clave < *maximo)) return false;

        return esBST(nodo->izquierdo, minimo, &nodo->clave) &&
               esBST(nodo->derecho, &nodo->clave, maximo);
    }

    static void clavesEnRango(const Nodo* nodo, const Clave& desde,
                              const Clave& hasta, vector<Clave>& resultado) {
        if (nodo == nullptr) return;

        if (desde < nodo->clave) {
            clavesEnRango(nodo->izquierdo, desde, hasta, resultado);
        }
        if (!(nodo->clave < desde) && !(hasta < nodo->clave)) {
            resultado.push_back(nodo->clave);
        }
        if (nodo->clave < hasta) {
            clavesEnRango(nodo->derecho, desde, hasta, resultado);
        }
    }

public:
    BST() = default;

    ~BST() { liberar(raiz); }

    // Permite copiar un BST sin compartir punteros.
    BST(const BST& otro) : raiz(clonar(otro.raiz)), cantidad(otro.cantidad) {}

    BST& operator=(const BST& otro) {
        if (this == &otro) return *this;
        Nodo* nuevaRaiz = clonar(otro.raiz);
        liberar(raiz);
        raiz = nuevaRaiz;
        cantidad = otro.cantidad;
        return *this;
    }

    // Permite mover el BST eficientemente.
    BST(BST&& otro) noexcept : raiz(otro.raiz), cantidad(otro.cantidad) {
        otro.raiz = nullptr;
        otro.cantidad = 0;
    }

    BST& operator=(BST&& otro) noexcept {
        if (this == &otro) return *this;
        liberar(raiz);
        raiz = otro.raiz;
        cantidad = otro.cantidad;
        otro.raiz = nullptr;
        otro.cantidad = 0;
        return *this;
    }

    // INSERTAR: devuelve false si la clave ya existe.
    bool insertar(const Clave& clave, const Valor& valor) {
        Nodo** lugar = buscarEnlace(clave);
        if (*lugar != nullptr) return false;

        *lugar = new Nodo(clave, valor);
        ++cantidad;
        return true;
    }

    // BUSCAR: copia el valor encontrado en "resultado".
    bool buscar(const Clave& clave, Valor& resultado) const {
        const Nodo* nodo = buscarNodo(clave);
        if (nodo == nullptr) return false;
        resultado = nodo->valor;
        return true;
    }

    bool contiene(const Clave& clave) const {
        return buscarNodo(clave) != nullptr;
    }

    // Acceso tipo map: arbol[clave]. Si no existe, la crea con Valor{}.
    Valor& operator[](const Clave& clave) {
        Nodo** lugar = buscarEnlace(clave);
        if (*lugar == nullptr) {
            *lugar = new Nodo(clave, Valor{});
            ++cantidad;
        }
        return (*lugar)->valor;
    }

    // ELIMINAR: maneja los tres casos (0, 1 o 2 hijos).
    bool eliminar(const Clave& clave) {
        Nodo** enlace = buscarEnlace(clave);
        if (*enlace == nullptr) return false;

        Nodo* objetivo = *enlace;

        // Caso 1: no tiene hijo izquierdo (incluye hoja y solo hijo derecho).
        if (objetivo->izquierdo == nullptr) {
            *enlace = objetivo->derecho;
            delete objetivo;
        }
        // Caso 2: solo tiene hijo izquierdo.
        else if (objetivo->derecho == nullptr) {
            *enlace = objetivo->izquierdo;
            delete objetivo;
        }
        // Caso 3: tiene dos hijos.
        else {
            // Buscamos el sucesor: minimo del subarbol derecho.
            Nodo** enlaceSucesor = &(objetivo->derecho);
            while ((*enlaceSucesor)->izquierdo != nullptr) {
                enlaceSucesor = &((*enlaceSucesor)->izquierdo);
            }

            Nodo* sucesor = *enlaceSucesor;
            objetivo->clave = sucesor->clave;
            objetivo->valor = sucesor->valor;

            // El sucesor nunca tiene hijo izquierdo.
            *enlaceSucesor = sucesor->derecho;
            delete sucesor;
        }

        --cantidad;
        return true;
    }

    bool minimo(Clave& resultado) const {
        const Nodo* nodo = minimoNodo(raiz);
        if (nodo == nullptr) return false;
        resultado = nodo->clave;
        return true;
    }

    bool maximo(Clave& resultado) const {
        const Nodo* nodo = maximoNodo(raiz);
        if (nodo == nullptr) return false;
        resultado = nodo->clave;
        return true;
    }

    // Menor clave estrictamente mayor que "clave".
    bool sucesor(const Clave& clave, Clave& resultado) const {
        const Nodo* actual = raiz;
        const Nodo* candidato = nullptr;

        while (actual != nullptr) {
            if (clave < actual->clave) {
                candidato = actual;
                actual = actual->izquierdo;
            } else {
                actual = actual->derecho;
            }
        }

        if (candidato == nullptr) return false;
        resultado = candidato->clave;
        return true;
    }

    // Mayor clave estrictamente menor que "clave".
    bool predecesor(const Clave& clave, Clave& resultado) const {
        const Nodo* actual = raiz;
        const Nodo* candidato = nullptr;

        while (actual != nullptr) {
            if (actual->clave < clave) {
                candidato = actual;
                actual = actual->derecho;
            } else {
                actual = actual->izquierdo;
            }
        }

        if (candidato == nullptr) return false;
        resultado = candidato->clave;
        return true;
    }

    // Profundidad de una clave: raiz = 0. Devuelve -1 si no existe.
    int profundidad(const Clave& clave) const {
        const Nodo* actual = raiz;
        int nivel = 0;

        while (actual != nullptr) {
            if (actual->clave == clave) return nivel;
            actual = clave < actual->clave
                         ? actual->izquierdo
                         : actual->derecho;
            ++nivel;
        }
        return -1;
    }

    // Altura en aristas: vacio = -1, una sola raiz = 0.
    int altura() const { return altura(raiz); }
    size_t tamanio() const { return cantidad; }
    size_t numeroHojas() const { return contarHojas(raiz); }
    bool vacio() const { return raiz == nullptr; }
    bool esBSTValido() const { return esBST(raiz, nullptr, nullptr); }

    vector<Clave> inorder() const {
        vector<Clave> resultado;
        resultado.reserve(cantidad);
        inorder(raiz, resultado);
        return resultado;
    }

    vector<Clave> preorder() const {
        vector<Clave> resultado;
        resultado.reserve(cantidad);
        preorder(raiz, resultado);
        return resultado;
    }

    vector<Clave> postorder() const {
        vector<Clave> resultado;
        resultado.reserve(cantidad);
        postorder(raiz, resultado);
        return resultado;
    }

    vector<Clave> levelOrder() const {
        vector<Clave> resultado;
        if (raiz == nullptr) return resultado;

        queue<const Nodo*> pendientes;
        pendientes.push(raiz);

        while (!pendientes.empty()) {
            const Nodo* actual = pendientes.front();
            pendientes.pop();
            resultado.push_back(actual->clave);

            if (actual->izquierdo != nullptr) pendientes.push(actual->izquierdo);
            if (actual->derecho != nullptr) pendientes.push(actual->derecho);
        }
        return resultado;
    }

    // Devuelve las claves desde "desde" hasta "hasta", inclusive y ordenadas.
    vector<Clave> rango(const Clave& desde, const Clave& hasta) const {
        vector<Clave> resultado;
        if (hasta < desde) return resultado;
        clavesEnRango(raiz, desde, hasta, resultado);
        return resultado;
    }

    // k empieza en 1: k=1 devuelve la menor clave. Complejidad O(n).
    bool kesimoMenor(size_t k, Clave& resultado) const {
        if (k == 0 || k > cantidad) return false;
        vector<Clave> ordenadas = inorder();
        resultado = ordenadas[k - 1];
        return true;
    }

    void limpiar() {
        liberar(raiz);
        raiz = nullptr;
        cantidad = 0;
    }
};

template <typename T>
void imprimirVector(const vector<T>& elementos, const string& nombre) {
    cout << nombre << ": ";
    for (const T& elemento : elementos) cout << elemento << ' ';
    cout << '\n';
}

// ============================================================================
// EJEMPLO DE USO: puedes reemplazar este main por el de cada ejercicio.
// ============================================================================
int main() {
    BST<int, string> arbol;

    arbol.insertar(40, "raiz");
    arbol.insertar(20, "veinte");
    arbol.insertar(60, "sesenta");
    arbol.insertar(10, "diez");
    arbol.insertar(30, "treinta");
    arbol.insertar(50, "cincuenta");
    arbol.insertar(70, "setenta");

    imprimirVector(arbol.inorder(), "Inorder");
    imprimirVector(arbol.preorder(), "Preorder");
    imprimirVector(arbol.postorder(), "Postorder");
    imprimirVector(arbol.levelOrder(), "Level-order");

    string valor;
    if (arbol.buscar(30, valor)) cout << "Valor de 30: " << valor << '\n';

    int clave;
    if (arbol.minimo(clave)) cout << "Minimo: " << clave << '\n';
    if (arbol.maximo(clave)) cout << "Maximo: " << clave << '\n';
    if (arbol.sucesor(30, clave)) cout << "Sucesor de 30: " << clave << '\n';
    if (arbol.predecesor(30, clave)) cout << "Predecesor de 30: " << clave << '\n';

    cout << "Altura: " << arbol.altura() << '\n';
    cout << "Profundidad de 50: " << arbol.profundidad(50) << '\n';
    cout << "Cantidad de nodos: " << arbol.tamanio() << '\n';
    cout << "Cantidad de hojas: " << arbol.numeroHojas() << '\n';
    cout << "BST valido: " << boolalpha << arbol.esBSTValido() << '\n';

    imprimirVector(arbol.rango(20, 60), "Claves entre 20 y 60");
    if (arbol.kesimoMenor(3, clave)) cout << "Tercer menor: " << clave << '\n';

    // Prueba de los tres casos de eliminacion.
    arbol.eliminar(10); // Caso 1: hoja.
    arbol.eliminar(20); // Caso 2: un hijo (despues de eliminar 10).
    arbol.eliminar(40); // Caso 3: dos hijos.
    imprimirVector(arbol.inorder(), "Despues de eliminar");

    // Inserta o actualiza como std::map.
    arbol[80] = "ochenta";
    arbol[80] = "OCHENTA actualizado";

    return 0;
}
