#include "AVL.h"

#include <sstream>

#include "List.h"
#include "Producto.h"

int ArbolAVL::altura(Categoria* nodo) {
    if (nodo == nullptr) return 0;
    return nodo->altura;
}

int ArbolAVL::balanceFactor(Categoria* nodo) {
    return nodo ? altura(nodo->izquierda) - altura(nodo->derecha) : 0;
}

void ArbolAVL::actualizarAltura(Categoria* nodo) {
    nodo->altura = 1 + max(altura(nodo->izquierda), altura(nodo->derecha));
}

Categoria* ArbolAVL::rotacionDerecha(Categoria* y) {
    Categoria* x = y->izquierda;
    Categoria* T2 = x->derecha;

    x->derecha = y;
    y->izquierda = T2;

    actualizarAltura(y);
    actualizarAltura(x);

    return x;
}

Categoria* ArbolAVL::rotacionIzquierda(Categoria* x) {
    Categoria* y = x->derecha;
    Categoria* T2 = y->izquierda;

    y->izquierda = x;
    x->derecha = T2;

    actualizarAltura(x);
    actualizarAltura(y);

    return y;
}

Categoria* ArbolAVL::nodoMinimo(Categoria* nodo) {
    Categoria* t = nodo;
    while (t->izquierda) t = t->izquierda;
    return t;
}

Categoria* ArbolAVL::insertar(Categoria* nodo, string nombre) {
    if (!nodo) return new Categoria(nombre);

    if (nombre < nodo->categoria)
        nodo->izquierda = insertar(nodo->izquierda, nombre);
    else if (nombre > nodo->categoria)
        nodo->derecha = insertar(nodo->derecha, nombre);
    else
        return nodo;

    actualizarAltura(nodo);

    int balance = balanceFactor(nodo);

    if (balance > 1 && nombre < nodo->izquierda->categoria)
        return rotacionDerecha(nodo);

    if (balance < -1 && nombre > nodo->derecha->categoria)
        return rotacionIzquierda(nodo);

    if (balance > 1 && nombre > nodo->izquierda->categoria) {
        nodo->izquierda = rotacionIzquierda(nodo->izquierda);
        return rotacionDerecha(nodo);
    }

    if (balance < -1 && nombre < nodo->derecha->categoria) {
        nodo->derecha = rotacionDerecha(nodo->derecha);
        return rotacionIzquierda(nodo);
    }

    return nodo;
}

Categoria* ArbolAVL::eliminar(Categoria* nodo, string nombre) {
    if (!nodo) return nullptr;

    if (nombre < nodo->categoria)
        nodo->izquierda = eliminar(nodo->izquierda, nombre);
    else if (nombre > nodo->categoria)
        nodo->derecha = eliminar(nodo->derecha, nombre);
    else {
        if (!nodo->productos.empty()) {
            cout << "No se puede eliminar la categoría '" << nombre
                 << "' porque contiene productos." << endl;
            return nodo;
        }

        if (!nodo->izquierda || !nodo->derecha) {
            Categoria* temp = nodo->izquierda ? nodo->izquierda : nodo->derecha;
            delete nodo;
            return temp;
        } else {
            Categoria* sucesor = nodoMinimo(nodo->derecha);

            if (!sucesor->productos.empty()) {
                cout << "No se puede eliminar la categoría '" << nombre
                     << "' porque contiene productos." << endl;
                return nodo;
            }

            nodo->categoria = sucesor->categoria;

            nodo->derecha = eliminar(nodo->derecha, sucesor->categoria);
        }
    }

    nodo->altura = 1 + max(altura(nodo->izquierda), altura(nodo->derecha));

    int balance = balanceFactor(nodo);

    if (balance > 1 && balanceFactor(nodo->izquierda) >= 0)
        return rotacionDerecha(nodo);
    if (balance > 1 && balanceFactor(nodo->izquierda) < 0) {
        nodo->izquierda = rotacionIzquierda(nodo->izquierda);
        return rotacionDerecha(nodo);
    }
    if (balance < -1 && balanceFactor(nodo->derecha) <= 0)
        return rotacionIzquierda(nodo);
    if (balance < -1 && balanceFactor(nodo->derecha) > 0) {
        nodo->derecha = rotacionDerecha(nodo->derecha);
        return rotacionIzquierda(nodo);
    }

    return nodo;
}

string ArbolAVL::imprimirOrden(Categoria* nodo) {
    if (!nodo) {
        return "";
    }
    stringstream ss;
    ss << imprimirOrden(nodo->izquierda);
    ss << nodo->categoria << endl;
    ss << imprimirOrden(nodo->derecha);
    return ss.str();
}

Categoria* ArbolAVL::buscarNodo(Categoria* nodo, string nombre) {
    if (!nodo) return nullptr;

    if (nombre == nodo->categoria)
        return nodo;
    else if (nombre < nodo->categoria)
        return buscarNodo(nodo->izquierda, nombre);
    else
        return buscarNodo(nodo->derecha, nombre);
}

void ArbolAVL::agregarProducto(Producto* producto) {
    Categoria* cat = buscarNodo(raiz, producto->categoria);
    if (cat) {
        cat->productos.push_back(producto);
    } else {
        throw out_of_range("Categoria no encontrada");
    }
}

bool ArbolAVL::vacio() { return raiz == nullptr; }

ArbolAVL::ArbolAVL() : raiz(nullptr) {}

void ArbolAVL::insertar(string nombre) { raiz = insertar(raiz, nombre); }

string ArbolAVL::imprimircategorias() { return imprimirOrden(raiz); }

List<Categoria*> ArbolAVL::inOrderCategoryList() { 
    List<Categoria*> categorias;
    inOrderCategoryList(raiz, categorias);
    return categorias;
}
void ArbolAVL::inOrderCategoryList(Categoria* nodo, List<Categoria*>& categorias) {
    if (nodo == nullptr) return;
    inOrderCategoryList(nodo->izquierda, categorias);
    categorias.push_back(nodo);
    inOrderCategoryList(nodo->derecha, categorias);
}

void ArbolAVL::eliminar(string nombre) { raiz = eliminar(raiz, nombre); }

Categoria* ArbolAVL::buscar(string nombre) { return buscarNodo(raiz, nombre); }

void ArbolAVL::agregarproducto(Producto* p) { agregarProducto(p); }

bool ArbolAVL::Vacio() { return vacio(); }

size_t ArbolAVL::contarCategorias(Categoria* nodo) {
    if (!nodo) return 0;
    return 1 + contarCategorias(nodo->izquierda) +
           contarCategorias(nodo->derecha);
}

size_t ArbolAVL::contarCategorias() { return contarCategorias(raiz); }

Producto* ArbolAVL::buscarProductoRec(Categoria* nodo, const string& codigo) {
    if (!nodo) return nullptr;

    for (int i = 0; i < nodo->productos.size(); ++i) {
        Producto* p = nodo->productos.get(i);
        if (p->codigo == codigo) {
            return p;
        }
    }

    Producto* encontrado = buscarProductoRec(nodo->izquierda, codigo);
    if (encontrado) return encontrado;

    return buscarProductoRec(nodo->derecha, codigo);
}

bool ArbolAVL::eliminarProducto(Categoria* nodo, const string& codigo) {
    if (!nodo) return false;

    if (eliminarProducto(nodo->izquierda, codigo)) return true;

    for (int i = 0; i < nodo->productos.size(); ++i) {
        Producto* p = nodo->productos.get(i);
        if (p->codigo == codigo) {
            nodo->productos.eliminar(
                i);    // Suponiendo que tienes remove(int index)
            delete p;  // Liberar memoria si fue creado con new

            return true;
        }
    }

    return eliminarProducto(nodo->derecha, codigo);
}

void ArbolAVL::imprimirProductos(Categoria* nodo) {
    if (nodo) {
        imprimirProductos(nodo->izquierda);

        cout << "Categoria: " << nodo->categoria << endl;
        for (size_t i = 0; i < nodo->productos.size(); ++i) {
            Producto* p = nodo->productos.get(i);
            cout << "  - " << p->to_string() << endl;
        }

        imprimirProductos(nodo->derecha);
    }
}