#include "Pedido.h"

void Pedido::validarDatos() const {
    if (idPedido.empty() || cliente.empty()) {
        throw invalid_argument("ID y cliente son obligatorios");
    }
    if (productos.empty()) {
        throw logic_error("El pedido no tiene productos");
    }
}

Pedido::Pedido() {}
Pedido::Pedido(string id, string nombreCliente)
    : idPedido(id), cliente(nombreCliente), total(0.0f) {
    if (id.empty() || nombreCliente.empty()) {
        throw invalid_argument("Datos incompletos para el pedido");
    }
}

void Pedido::agregarProducto(const Producto &prod, int cantidad) {
    if (cantidad <= 0) {
        throw invalid_argument("Cantidad solicitada debe ser > 0");
    }
    productos.push_back(std::pair(prod, cantidad));
    total += prod.precio * cantidad;
}

string Pedido::mostrarPedido() const {
    stringstream ss;
    validarDatos();
    ss << "=== Pedido #" << idPedido << " ===" << endl;
    ss << "Cliente: " << cliente << "\nProductos:\n";
    for (int i = 0; i < productos.size(); i++) {
        Producto prod = productos.get(i).first;
        ss << prod.codigo << "\t" << prod.nombre << "\t$" << prod.precio
           << "\tx" << productos.get(i).second << endl;
    }
    ss << "TOTAL: $" << total << "\n\n";
    return ss.str();
}

string Pedido::getId() const { return idPedido; }
float Pedido::getTotal() const { return total; }