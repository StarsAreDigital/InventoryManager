#ifndef PEDIDO_H
#define PEDIDO_H

#include "Producto.h"
#include "structs/List.h"

class Pedido {
   private:
    std::string idPedido;
    std::string cliente;
    List<std::pair<Producto, int>> productos;
    float total;

    void validarDatos() const;

   public:
    Pedido();
    Pedido(std::string id, std::string nombreCliente);

    void agregarProducto(const Producto &prod, int cantidad);
    std::string mostrarPedido() const;

    std::string getId() const;
    float getTotal() const;
};

#endif  // PEDIDO_H