#include <functional>
#include <iostream>
#include <list>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

// ================================================================
// PARTE 1: TABLA HASH CON ENCADENAMIENTO (CHAINING)
// Guarda pares clave -> valor. Sirve con int, string y otros tipos
// que tengan std::hash.
// ================================================================
template <typename Clave, typename Valor>
class TablaHashEncadenamiento {
private:
    using Par = pair<Clave, Valor>;

    vector<list<Par>> tabla;
    size_t cantidad = 0;
    double factorMaximo = 0.75;

    size_t indice(const Clave& clave) const {
        return hash<Clave>{}(clave) % tabla.size();
    }

    void rehash(size_t nuevaCapacidad) {
        vector<list<Par>> tablaAnterior = move(tabla);
        tabla.clear();
        tabla.resize(nuevaCapacidad);
        cantidad = 0;

        for (const auto& bucket : tablaAnterior) {
            for (const auto& [clave, valor] : bucket) {
                insertar(clave, valor);
            }
        }
    }

public:
    explicit TablaHashEncadenamiento(size_t capacidadInicial = 7)
        : tabla(capacidadInicial == 0 ? 7 : capacidadInicial) {}

    // Inserta una clave nueva. Si ya existe, actualiza su valor.
    void insertar(const Clave& clave, const Valor& valor) {
        size_t posicion = indice(clave);

        for (auto& [claveActual, valorActual] : tabla[posicion]) {
            if (claveActual == clave) {
                valorActual = valor;
                return;
            }
        }

        tabla[posicion].push_back({clave, valor});
        ++cantidad;

        if (factorCarga() > factorMaximo) {
            rehash(tabla.size() * 2 + 1);
        }
    }

    // Devuelve true y copia el valor en "resultado" si encuentra la clave.
    bool buscar(const Clave& clave, Valor& resultado) const {
        size_t posicion = indice(clave);

        for (const auto& [claveActual, valorActual] : tabla[posicion]) {
            if (claveActual == clave) {
                resultado = valorActual;
                return true;
            }
        }
        return false;
    }

    bool contiene(const Clave& clave) const {
        size_t posicion = indice(clave);

        for (const auto& [claveActual, valorActual] : tabla[posicion]) {
            (void)valorActual;
            if (claveActual == clave) return true;
        }
        return false;
    }

    bool eliminar(const Clave& clave) {
        size_t posicion = indice(clave);

        for (auto it = tabla[posicion].begin();
             it != tabla[posicion].end(); ++it) {
            if (it->first == clave) {
                tabla[posicion].erase(it);
                --cantidad;
                return true;
            }
        }
        return false;
    }

    size_t tamanio() const { return cantidad; }
    bool vacia() const { return cantidad == 0; }
    double factorCarga() const {
        return static_cast<double>(cantidad) / tabla.size();
    }

    void limpiar() {
        for (auto& bucket : tabla) bucket.clear();
        cantidad = 0;
    }

    void imprimir() const {
        for (size_t i = 0; i < tabla.size(); ++i) {
            cout << i << ": ";
            for (const auto& [clave, valor] : tabla[i]) {
                cout << "(" << clave << ", " << valor << ") -> ";
            }
            cout << "NULL\n";
        }
    }
};

// ================================================================
// PARTE 2: DIRECCIONAMIENTO ABIERTO CON LINEAR PROBING
// Esta version didactica usa claves y valores enteros.
// ================================================================
class TablaHashLinearProbing {
private:
    enum class Estado { VACIO, OCUPADO, ELIMINADO };

    struct Casilla {
        int clave = 0;
        int valor = 0;
        Estado estado = Estado::VACIO;
    };

    vector<Casilla> tabla;
    size_t cantidad = 0;
    double factorMaximo = 0.70;

    size_t indice(int clave) const {
        // Funciona incluso si la clave es negativa.
        long long m = static_cast<long long>(tabla.size());
        return static_cast<size_t>(((clave % m) + m) % m);
    }

    void rehash(size_t nuevaCapacidad) {
        vector<Casilla> anterior = move(tabla);
        tabla.clear();
        tabla.resize(nuevaCapacidad);
        cantidad = 0;

        for (const Casilla& casilla : anterior) {
            if (casilla.estado == Estado::OCUPADO) {
                insertar(casilla.clave, casilla.valor);
            }
        }
    }

public:
    explicit TablaHashLinearProbing(size_t capacidadInicial = 7)
        : tabla(capacidadInicial == 0 ? 7 : capacidadInicial) {}

    // Inserta o actualiza. Si hay colision, prueba la siguiente posicion.
    void insertar(int clave, int valor) {
        if ((static_cast<double>(cantidad + 1) / tabla.size()) > factorMaximo) {
            rehash(tabla.size() * 2 + 1);
        }

        size_t inicio = indice(clave);
        size_t primerEliminado = tabla.size();

        for (size_t intento = 0; intento < tabla.size(); ++intento) {
            size_t posicion = (inicio + intento) % tabla.size();
            Casilla& casilla = tabla[posicion];

            if (casilla.estado == Estado::OCUPADO && casilla.clave == clave) {
                casilla.valor = valor;
                return;
            }

            if (casilla.estado == Estado::ELIMINADO &&
                primerEliminado == tabla.size()) {
                primerEliminado = posicion;
            }

            if (casilla.estado == Estado::VACIO) {
                size_t destino = primerEliminado == tabla.size()
                                     ? posicion
                                     : primerEliminado;
                tabla[destino] = {clave, valor, Estado::OCUPADO};
                ++cantidad;
                return;
            }
        }

        // Puede suceder si solo quedan casillas marcadas ELIMINADO.
        if (primerEliminado != tabla.size()) {
            tabla[primerEliminado] = {clave, valor, Estado::OCUPADO};
            ++cantidad;
            return;
        }

        rehash(tabla.size() * 2 + 1);
        insertar(clave, valor);
    }

    bool buscar(int clave, int& resultado) const {
        size_t inicio = indice(clave);

        for (size_t intento = 0; intento < tabla.size(); ++intento) {
            size_t posicion = (inicio + intento) % tabla.size();
            const Casilla& casilla = tabla[posicion];

            // VACIO significa que la cadena de probing termino.
            if (casilla.estado == Estado::VACIO) return false;

            if (casilla.estado == Estado::OCUPADO && casilla.clave == clave) {
                resultado = casilla.valor;
                return true;
            }
            // Si esta ELIMINADO, continuamos buscando.
        }
        return false;
    }

    bool contiene(int clave) const {
        int valorIgnorado;
        return buscar(clave, valorIgnorado);
    }

    bool eliminar(int clave) {
        size_t inicio = indice(clave);

        for (size_t intento = 0; intento < tabla.size(); ++intento) {
            size_t posicion = (inicio + intento) % tabla.size();
            Casilla& casilla = tabla[posicion];

            if (casilla.estado == Estado::VACIO) return false;

            if (casilla.estado == Estado::OCUPADO && casilla.clave == clave) {
                // No usamos VACIO porque cortaria futuras busquedas.
                casilla.estado = Estado::ELIMINADO;
                --cantidad;
                return true;
            }
        }
        return false;
    }

    size_t tamanio() const { return cantidad; }
    double factorCarga() const {
        return static_cast<double>(cantidad) / tabla.size();
    }

    void imprimir() const {
        for (size_t i = 0; i < tabla.size(); ++i) {
            cout << i << ": ";
            if (tabla[i].estado == Estado::VACIO) {
                cout << "VACIO";
            } else if (tabla[i].estado == Estado::ELIMINADO) {
                cout << "ELIMINADO";
            } else {
                cout << "(" << tabla[i].clave << ", " << tabla[i].valor << ")";
            }
            cout << '\n';
        }
    }
};

// ================================================================
// PARTE 3: POLYNOMIAL ROLLING HASH PARA STRINGS
// ================================================================
long long hashString(const string& texto) {
    const long long p = 31;
    const long long modulo = 1'000'000'009;
    long long resultado = 0;
    long long potencia = 1;

    for (char caracter : texto) {
        long long valor = caracter - 'a' + 1; // Para letras de 'a' a 'z'.
        resultado = (resultado + valor * potencia) % modulo;
        potencia = (potencia * p) % modulo;
    }
    return resultado;
}

// ================================================================
// PARTE 4: EJEMPLO DE USO
// ================================================================
int main() {
    cout << "=== ENCADENAMIENTO ===\n";
    TablaHashEncadenamiento<int, string> alumnos(7);
    alumnos.insertar(23, "Darlene");
    alumnos.insertar(37, "Ana");       // Colision si usamos k % 7.
    alumnos.insertar(45, "Carlos");
    alumnos.insertar(23, "Darlene P."); // Actualiza la clave 23.

    string nombre;
    if (alumnos.buscar(23, nombre)) {
        cout << "Clave 23 encontrada: " << nombre << "\n";
    }
    alumnos.eliminar(37);
    alumnos.imprimir();

    cout << "\n=== LINEAR PROBING ===\n";
    TablaHashLinearProbing numeros(5);
    numeros.insertar(12, 120);
    numeros.insertar(18, 180);
    numeros.insertar(13, 130);
    numeros.imprimir();

    int valor;
    if (numeros.buscar(13, valor)) {
        cout << "Valor asociado a 13: " << valor << "\n";
    }
    numeros.eliminar(18);

    cout << "\nDespues de eliminar 18:\n";
    numeros.imprimir();

    cout << "\n=== STL PARA CODEFORCES ===\n";
    unordered_map<int, int> frecuencia;
    vector<int> arreglo = {1, 2, 1, 3, 2, 1};
    for (int x : arreglo) ++frecuencia[x];
    cout << "Frecuencia de 1: " << frecuencia[1] << "\n";

    unordered_set<int> vistos;
    bool hayDuplicado = false;
    for (int x : arreglo) {
        if (vistos.count(x)) {
            hayDuplicado = true;
            break;
        }
        vistos.insert(x);
    }
    cout << "Hay duplicados: " << boolalpha << hayDuplicado << "\n";

    cout << "Hash de 'darlene': " << hashString("darlene") << "\n";
    return 0;
}
