#include "Inventario.h"

Inventario::Inventario() : productos() {}

Inventario::Inventario(const Inventario &inv) : productos(inv.productos) {}

Inventario::Inventario(Inventario &&inv) : productos(inv.productos) {}

Inventario::~Inventario() {}

int Inventario::buscarCodigo(string codigo) {
    size_t s = productos.size();
    for (int i = 0; i < s; i++) {
        if (productos.get(i).first == codigo) return i;
    }
    return -1;
}

void Inventario::insertarProducto(string codigo, int cantidad) {
    productos.push_front(pair<string, int>(codigo, cantidad));
}

void Inventario::eliminarProducto(string codigo) {
    int index = buscarCodigo(codigo);
    if (index == -1) return;
    productos.eliminar(index);
}

void Inventario::actualizarProducto(string codigo, int cantidad) {
    int index = buscarCodigo(codigo);
    if (index == -1) return;
    productos.modificar(index, pair<string, int>(codigo, cantidad));
}

string Inventario::to_string() {
    stringstream ss;
    if (productos.size() == 0) {
        ss << "El inventario esta vacio" << endl;
    } else {
        for (int i = 0; i < productos.size(); i++) {
            ss << productos.get(i).first << ": " << productos.get(i).second
               << endl;
        }
    }
    return ss.str();
}