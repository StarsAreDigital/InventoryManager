#ifndef INVENTORY_MANAGER_H
#define INVENTORY_MANAGER_H

#include "Action.h"
#include "Inventario.h"
#include "Pedido.h"
#include "structs/Queue.h"
#include "structs/Stack.h"

class InventoryManager {
   private:
    Stack<Action *> undoStack, redoStack;
    void registrarAccion(Action *a) {
        undoStack.push(a);
        redoStack.clear();
    }
    List<Inventario *> inventarios;
    Queue<Pedido> pedidos;

   public:
    ArbolAVL productos;
    string deshacer() {
        if (undoStack.size() == 0) return "No hay acciones para deshacer";
        Action *t = undoStack.top();
        t->undo();
        redoStack.push(t);
        undoStack.pop();
        return t->to_string();
    }
    string rehacer() {
        if (redoStack.size() == 0) return "No hay acciones para rehacer";
        Action *t = redoStack.top();
        t->redo();
        undoStack.push(t);
        redoStack.pop();
        return t->to_string();
    }

    void agregarInventario(Inventario *inv) { inventarios.push_back(inv); }

    List<Inventario *> getInventarios() { return this->inventarios; }

    void agregarProducto(int inv, string codigo, int cantidad) {
        Inventario *inventario = inventarios.get(inv);
        inventario->insertarProducto(codigo, cantidad);

        AddProductAction *a =
            new AddProductAction(inventario, codigo, cantidad);
        registrarAccion(a);
    }

    bool eliminarProducto(int inv, string codigo) {
        Inventario *inventario = inventarios.get(inv);
        int index = inventario->buscarCodigo(codigo);
        if (index == -1) return false;
        int cantidad = inventario->productos.get(index).second;

        inventario->eliminarProducto(codigo);

        DeleteProductAction *a =
            new DeleteProductAction(inventario, codigo, cantidad);
        registrarAccion(a);
        return true;
    }

    bool actualizarProducto(int inv, string codigo, int cantidadDespues) {
        Inventario *inventario = inventarios.get(inv);
        int index = inventario->buscarCodigo(codigo);
        if (index == -1) return false;
        int cantidadAntes = inventario->productos.get(index).second;

        inventario->actualizarProducto(codigo, cantidadDespues);

        UpdateProductAction *a = new UpdateProductAction(
            inventario, codigo, cantidadAntes, cantidadDespues);
        registrarAccion(a);
        return true;
    }

    size_t size() { return inventarios.size(); }
};

#endif  // INVENTORY_MANAGER_H