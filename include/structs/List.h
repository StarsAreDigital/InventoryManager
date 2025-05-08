#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <sstream>
#include <stdexcept>

using namespace std;

template <typename T>
class List {
   private:
    struct Node {
        T val;
        Node *next;
        Node *prev;

        Node() {
            this->next = nullptr;
            this->prev = nullptr;
        }
        Node(T val) {
            this->val = val;
            this->next = nullptr;
            this->prev = nullptr;
        }
        ~Node() {
            this->next = nullptr;
            this->prev = nullptr;
        }
    };

    Node *head;
    Node *tail;
    int longitud;

   public:
    List() {
        this->head = nullptr;
        this->tail = nullptr;
        this->longitud = 0;
    }
    List(const List<T> &rhs) {
        this->head = rhs.head;
        this->tail = rhs.tail;
        this->longitud = rhs.longitud;
    }
    List(List<T> &&rhs) {
        this->head = move(rhs.head);
        this->tail = move(rhs.tail);
        this->longitud = move(rhs.longitud);
    }
    ~List() {}

    Node *begin() { return this->head; }
    Node *end() {
        if (this->tail == nullptr) return nullptr;
        return this->tail->next;
    }

    bool empty() const { return longitud == 0; }

    void insertar(T val, int i) {
        if (i < 0 || i > this->longitud)
            throw out_of_range("Posicion de insertar invalida");

        Node *n = new Node(val);
        if (this->empty()) {
            this->head = this->tail = n;
        } else if (i == 0) {
            n->next = this->head;
            this->head->prev = n;
            this->head = n;
        } else if (i == this->longitud) {
            n->prev = this->tail;
            this->tail->next = n;
            this->tail = n;
        } else {
            Node *cursor = this->head;
            for (int k = 0; k < i - 1; k++) {
                cursor = cursor->next;
            }
            n->next = cursor->next;
            n->prev = cursor;
            n->next->prev = n;
            n->prev->next = n;
        }
        this->longitud++;
    }
    void push_front(T val) { this->insertar(val, 0); }
    void push_back(T val) { this->insertar(val, this->longitud); }
    void push_posicion(T val, int pos) { this->insertar(val, pos); }

    void eliminar(int i) {
        if (i < 0 || i >= this->longitud) {
            throw out_of_range("Posicion de eliminar invalida");
        }

        if (i == 0) {
            Node *del = this->head;
            this->head = this->head->next;
            if (this->head == nullptr) {
                this->tail = nullptr;
            } else {
                this->head->prev = nullptr;
            }
            delete del;
        } else if (i == longitud - 1) {
            Node *del = this->tail;
            this->tail = this->tail->prev;
            if (this->tail == nullptr) {
                this->head = nullptr;
            } else {
                this->tail->next = nullptr;
            }
            delete del;
        } else {
            Node *cursor = this->head;
            for (int k = 0; k < i - 1; k++) {
                cursor = cursor->next;
            }
            cursor->next = cursor->next->next;
            delete cursor->next->prev;
            cursor->next->prev = cursor;
        }
        longitud--;
    }
    void pop_inicio() { this->eliminar(0); }
    void pop_final() { this->eliminar(this->longitud - 1); }
    void pop_posicion(int pos) { this->eliminar(pos); }

    void modificar(int i, T val) {
        if (i < 0 || i >= this->longitud) {
            throw out_of_range("Posicion de get invalida");
        }
        if (i == 0) this->head->val = val;
        if (i == this->longitud - 1) this->tail->val = val;
        Node *cursor = this->head;
        for (int k = 0; k < i; k++) {
            cursor = cursor->next;
        }
        cursor->val = val;
    }

    T get(int i) const {
        if (i < 0 || i >= this->longitud) {
            throw out_of_range("Posicion de get invalida");
        }
        if (i == 0) return this->head->val;
        if (i == this->longitud - 1) return this->tail->val;
        Node *cursor = this->head;
        for (int k = 0; k < i; k++) {
            cursor = cursor->next;
        }
        return cursor->val;
    }
    void get_inicio() { this->get(0); }
    void get_final() { this->get(this->longitud - 1); }
    void get_posicion(int pos) { this->get(pos); }

    string toString() {
        stringstream ss;
        ss << "{ ";
        Node *cursor = this->head;
        while (cursor != nullptr) {
            ss << cursor->val << " ";
            cursor = cursor->next;
        }
        ss << "}";
        return ss.str();
    }
    size_t size() const { return this->longitud; }
};

#endif  // LIST_H