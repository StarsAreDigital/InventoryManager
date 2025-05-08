#ifndef SERIALIZADOR_H
#define SERIALIZADOR_H

#include <fstream>

#include "Inventario.h"
#include "InventoryManager.h"
#include "Pedido.h"
#include "Producto.h"

class Serializador {
   private:
    std::string filename;
    InventoryManager* manager;

   public:
    Serializador(InventoryManager* manager, std::string filename);
    ~Serializador();

    bool Guardar();
    bool Cargar();
};

#endif