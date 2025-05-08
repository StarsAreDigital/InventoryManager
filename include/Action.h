#ifndef ACTION_H
#define ACTION_H

#include <iostream>
#include <sstream>

#include "Inventario.h"

class Action {
   protected:
    Inventario *inv;

   public:
    Action(Inventario *inv) : inv(inv) {}
    virtual void undo() = 0;
    virtual void redo() = 0;
    virtual string to_string() = 0;
    virtual ~Action() {}
};

class AddProductAction : public Action {
   private:
    string codigo;
    int cantidad;

   public:
    AddProductAction(Inventario *inv, string codigo, int cantidad)
        : Action(inv), codigo(codigo), cantidad(cantidad) {}
    void undo() override { inv->eliminarProducto(codigo); }
    void redo() override { inv->insertarProducto(codigo, cantidad); }
    string to_string() override {
        stringstream ss;
        ss << "Accion Agregar Producto " << codigo << ": " << cantidad;
        return ss.str();
    }
};

class DeleteProductAction : public Action {
   private:
    string codigo;
    int cantidad;

   public:
    DeleteProductAction(Inventario *inv, string codigo, int cantidad)
        : Action(inv), codigo(codigo), cantidad(cantidad) {}
    void undo() override { inv->insertarProducto(codigo, cantidad); }
    void redo() override { inv->eliminarProducto(codigo); }
    string to_string() override {
        stringstream ss;
        ss << "Accion Eliminar Producto " << codigo << ": " << cantidad;
        return ss.str();
    }
};

class UpdateProductAction : public Action {
   private:
    string codigo;
    int cantidadAntes;
    int cantidadDespues;

   public:
    UpdateProductAction(Inventario *inv, string codigo, int cantidadAntes,
                        int cantidadDespues)
        : Action(inv),
          codigo(codigo),
          cantidadAntes(cantidadAntes),
          cantidadDespues(cantidadDespues) {}
    void undo() override { inv->actualizarProducto(codigo, cantidadAntes); }
    void redo() override { inv->actualizarProducto(codigo, cantidadDespues); }
    string to_string() override {
        stringstream ss;
        ss << "Accion Modificar Producto " << codigo << ": " << cantidadAntes
           << " -> " << cantidadDespues;
        return ss.str();
    }
};
#endif  // ACTION_H