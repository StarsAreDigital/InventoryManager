#include <iostream>
using namespace std;

#include "AVL.h"
#include "InventoryManager.h"
#include "Serializador.h"

// int main()
// {
//     bool salir = false;
//     int option, index;
//     InventoryManager manager;
//     do
//     {
//         cout << "=== Gestor de inventarios ===" << endl;
//         cout << "1. Nuevo inventario" << endl;
//         cout << "2. Agregar producto" << endl;
//         cout << "3. Eliminar producto" << endl;
//         cout << "4. Modificar producto" << endl;
//         cout << "5. Agregar pedido" << endl;
//         cout << "6. Surtir pedido" << endl;
//         cout << "7. Listar pedidos" << endl;
//         cout << "8. Deshacer ultima accion" << endl;
//         cout << "9. Rehacer ultima accion" << endl;
//         cout << "10. Imprimir inventario" << endl;
//         cout << "0. Salir" << endl;
//         cout << "> ";
//         cin >> option;

//         switch (option)
//         {
//         case 1:
//             manager.agregarInventario(new Inventario());
//             break;
//         case 2:
//             if (manager.size() == 0)
//             {
//                 cout << "No hay ningun inventario" << endl;
//             }
//             else
//             {
//                 cout << "Seleccionar inventario (1 - " << manager.size() <<
//                 ")" << endl; cin >> index; index--; if (index < 0 || index >=
//                 manager.size())
//                 {
//                     cout << "Indice fuera de rango" << endl;
//                 }
//                 else
//                 {
//                     Producto *p = new Producto();
//                     cout << "Codigo: ";
//                     cin >> p->codigo;
//                     cin.ignore();
//                     cout << "Nombre: ";
//                     getline(cin, p->nombre);
//                     cout << "Precio: ";
//                     cin >> p->precio;
//                     cout << "Categoria: ";
//                     cin >> p->categoria;
//                     cout << "Existencias: ";
//                     cin >> p->existencias;
//                     cin.ignore();
//                     manager.agregarProducto(index, p);
//                 }
//             }
//             break;
//         case 3:
//             if (manager.size() == 0)
//             {
//                 cout << "No hay ningun inventario" << endl;
//             }
//             else
//             {
//                 cout << "Seleccionar inventario (1 - " << manager.size() <<
//                 ")" << endl; cin >> index; index--; if (index < 0 || index >=
//                 manager.size())
//                 {
//                     cout << "Indice fuera de rango" << endl;
//                 }
//                 else
//                 {
//                     string codigo;
//                     cout << "Codigo a eliminar: ";
//                     cin >> codigo;
//                     bool res = manager.eliminarProducto(index, codigo);
//                     if (res)
//                     {
//                         cout << "Producto eliminado con exito" << endl;
//                     }
//                     else
//                     {
//                         cout << "No se encontro el codigo" << endl;
//                     }
//                 }
//             }
//             break;
//         case 4:
//             if (manager.size() == 0)
//             {
//                 cout << "No hay ningun inventario" << endl;
//             }
//             else
//             {
//                 cout << "Seleccionar inventario (1 - " << manager.size() <<
//                 ")" << endl; cin >> index; index--; if (index < 0 || index >=
//                 manager.size())
//                 {
//                     cout << "Indice fuera de rango" << endl;
//                 }
//                 else
//                 {
//                     string codigo;
//                     cout << "Codigo a modificar: ";
//                     cin >> codigo;
//                     cin.ignore();

//                     Producto *p = manager.buscarProducto(index, codigo);
//                     if (p == nullptr)
//                     {
//                         cout << "No se encontro el producto" << endl;
//                     }
//                     else
//                     {
//                         Producto *n = new Producto(*p);
//                         cout << "Producto a modificar: " << n->to_string() <<
//                         endl; cout << "Nombre: "; getline(cin, n->nombre);
//                         cout << "Precio: ";
//                         cin >> n->precio;
//                         cout << "Categoria: ";
//                         cin >> n->categoria;
//                         cout << "Existencias: ";
//                         cin >> n->existencias;
//                         cin.ignore();
//                         manager.actualizarProducto(index, codigo, n);
//                     }
//                 }
//             }
//             break;
//         case 5:
//             break;
//         case 6:
//             break;
//         case 7:
//             break;
//         case 8:
//             cout << manager.deshacer() << endl;
//             break;
//         case 9:
//             cout << manager.rehacer() << endl;
//             break;
//         case 10:
//             if (manager.size() == 0)
//             {
//                 cout << "No hay ningun inventario" << endl;
//             }
//             else
//             {
//                 cout << "Seleccionar inventario (1 - " << manager.size() <<
//                 ")" << endl; cin >> index; index--; if (index < 0 || index >=
//                 manager.size())
//                 {
//                     cout << "Indice fuera de rango" << endl;
//                 }
//                 else
//                 {
//                     cout << manager.obtener(index)->to_string() << endl;
//                 }
//             }
//             break;
//         case 0:
//             salir = true;
//             break;

//         default:
//             break;
//         }
//         cout << endl
//              << endl;
//     } while (!salir);
// }

int main() {
    InventoryManager* manager = new InventoryManager();

    manager->productos.insertar("A aaa");
    manager->productos.insertar("V vvv");
    manager->productos.insertar("L lll");

    manager->productos.agregarproducto(
        new Producto("A1", "Producto de prueba A1", 20, "A aaa"));
    manager->productos.agregarproducto(
        new Producto("A2", "Producto de prueba A2", 25, "A aaa"));
    manager->productos.agregarproducto(
        new Producto("A3", "Producto de prueba A3", 30, "A aaa"));

    manager->productos.agregarproducto(
        new Producto("V1", "Producto de prueba V", 35, "V vvv"));
    manager->productos.agregarproducto(
        new Producto("V2", "Producto de prueba V", 40, "V vvv"));

    manager->productos.agregarproducto(
        new Producto("L1", "Producto de prueba L", 45, "L lll"));

    manager->agregarInventario(new Inventario());
    manager->agregarInventario(new Inventario());

    manager->getInventarios().get(0)->insertarProducto("A1", 5);
    manager->getInventarios().get(0)->insertarProducto("A2", 1);
    manager->getInventarios().get(0)->insertarProducto("L1", 2);

    manager->getInventarios().get(1)->insertarProducto("A1", 4);
    manager->getInventarios().get(1)->insertarProducto("A3", 3);
    manager->getInventarios().get(1)->insertarProducto("V1", 7);
    manager->getInventarios().get(1)->insertarProducto("V2", 6);

    Serializador s(manager, "db.txt");
    s.Guardar();
}