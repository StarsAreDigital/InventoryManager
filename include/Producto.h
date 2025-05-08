#ifndef PRODUCTO_H
#define PRODUCTO_H

#include <sstream>
#include <string>

class Producto {
   public:
    std::string codigo;
    std::string nombre;
    float precio;
    std::string categoria;

    Producto();
    Producto(std::string codigo, std::string nombre, float precio,
             std::string categoria);

    std::string to_string();
};

bool operator==(const Producto &lhs, const Producto &rhs);

#endif  // PRODUCTO_H