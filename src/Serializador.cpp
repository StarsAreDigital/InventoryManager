#include "Serializador.h"

Serializador::Serializador(InventoryManager* manager, std::string filename)
    : manager(manager), filename(filename) {}
Serializador::~Serializador() {}

bool Serializador::Guardar() {
    std::ofstream outFile(this->filename);
    if (!outFile.is_open()) return false;

    List<Categoria *> categorias = manager->productos.inOrderCategoryList();
    outFile << "cat " << categorias.size() << endl;
    for (auto it = categorias.begin(); it != categorias.end(); it = it->next) {
        outFile << it->val->categoria << endl << it->val->productos.size() << endl;
        for (auto prod = it->val->productos.begin(); prod != it->val->productos.end(); prod = prod->next) {
            outFile << prod->val->codigo << endl;
            outFile << prod->val->nombre << endl;
            outFile << prod->val->precio << endl;
        }
    }

    List<Inventario*> inventarios = manager->getInventarios();
    outFile << "inv " << inventarios.size() << endl;

    for (auto it = inventarios.begin(); it != inventarios.end();
         it = it->next) {
        outFile << "prod " << it->val->productos.size() << endl;
        for (auto prod = it->val->productos.begin(); prod != nullptr;
             prod = prod->next) {
            outFile << prod->val.first << " " << prod->val.second << endl;
        }
    }
    return true;
}

bool Serializador::Cargar() {
    std::ifstream inFile(this->filename);
    if (!inFile.is_open()) return false;

    std::string command;
    size_t count;
    List<Inventario*> inventarios = manager->getInventarios();
    while (!inventarios.empty()) {
        inventarios.pop_final();
    }

    while (!inFile.eof()) {
        inFile >> command;
        inFile.ignore();
        if (command == "inv") {
            inFile >> count;
            inFile.ignore();
            for (size_t i = 0; i < count; i++) {
                Inventario* inv = new Inventario();
                inventarios.push_back(inv);
                int n;
                inFile >> n;
                for (size_t j = 0; j < n; j++) {
                    string codigo;
                    int cantidad;
                    inFile >> codigo >> cantidad;
                    inFile.ignore();
                    getline(inFile, codigo);
                    if (manager->productos.buscar(codigo)) inFile >> cantidad;
                    inv->productos.push_back(std::pair(codigo, cantidad));
                }
            }
        }
    }
    return true;
}