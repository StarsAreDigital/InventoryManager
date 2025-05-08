#ifndef AVL_H
#define AVL_H

#include "List.h"
#include "Producto.h"

class Categoria {
   public:
    string categoria;
    List<Producto*> productos;
    int altura;
    Categoria* izquierda;
    Categoria* derecha;

    Categoria() {}
    Categoria(string nombre)
        : categoria(nombre), altura(1), izquierda(nullptr), derecha(nullptr) {}
};

class ArbolAVL {
   private:
    Categoria* raiz;

    int altura(Categoria* nodo);
    int balanceFactor(Categoria* nodo);
    void actualizarAltura(Categoria* nodo);

    Categoria* rotacionDerecha(Categoria* y);
    Categoria* rotacionIzquierda(Categoria* x);
    Categoria* nodoMinimo(Categoria* nodo);
    Categoria* insertar(Categoria* nodo, std::string nombre);
    Categoria* eliminar(Categoria* nodo, std::string nombre);
    std::string imprimirOrden(Categoria* nodo);
    Categoria* buscarNodo(Categoria* nodo, std::string nombre);
    void agregarProducto(Producto* producto);
    void imprimirProductos(Categoria* nodo);
    void inOrderCategoryList(Categoria* nodo, List<Categoria*>& categorias);

    bool eliminarProducto(Categoria* nodo, const string& codigo);
    Producto* buscarProductoRec(Categoria* nodo, const string& codigo);

    size_t contarCategorias(Categoria* nodo);
    bool vacio();

   public:
    ArbolAVL();
    void insertar(std::string nombre);
    void eliminar(std::string nombre);
    Categoria* buscar(std::string nombre);
    std::string imprimircategorias();
    size_t contarCategorias();
    void agregarproducto(Producto* p);
    bool Vacio();
    Producto* buscarProductoPorCodigo(const string& codigo) {
        return buscarProductoRec(raiz, codigo);
    }
    List<Categoria*> inOrderCategoryList();
};

#endif