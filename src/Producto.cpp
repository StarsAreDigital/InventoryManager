#include "Producto.h"

Producto::Producto() {}
Producto::Producto(std::string codigo, std::string nombre, float precio,
                   std::string categoria)
    : codigo(codigo), nombre(nombre), precio(precio), categoria(categoria) {}

std::string Producto::to_string() {
    std::stringstream ss;
    ss << "{ " << codigo << ", " << nombre << ", $" << precio << ", "
       << categoria << " }";
    return ss.str();
}

bool operator==(const Producto &lhs, const Producto &rhs) {
    return lhs.codigo == rhs.codigo;
}