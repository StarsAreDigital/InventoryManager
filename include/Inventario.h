#ifndef INVENTARIO_H
#define INVENTARIO_H

#include "AVL.h"
#include "Producto.h"
#include "structs/List.h"

class Inventario {
   public:
    List<std::pair<string, int>> productos;
    Inventario();
    Inventario(const Inventario &inv);
    Inventario(Inventario &&inv);
    ~Inventario();

    int buscarCodigo(std::string id);
    void insertarProducto(std::string codigo, int cantidad);
    void eliminarProducto(std::string idProducto);
    void actualizarProducto(std::string codigo, int cantidad);

    std::string to_string();
};

#endif  // INVENTARIO_H