#ifndef QUEUE_H
#define QUEUE_H

#include <stdexcept>
#include <sstream>
#include <iostream>

using namespace std;

template <typename T>
class Queue {
    private:
    struct Node
    {
        T data;
        Node *siguiente;
        Node(const T &valor) : data(valor), siguiente(nullptr) {}
    };

    Node *front;
    Node *back;
    int size;

public:
    Queue() : front(nullptr), back(nullptr), size(0) {}

    ~Queue()
    {
        while (!empty())
        {
            dequeue();
        }
    }

    void encolar(const T &val)
    {
        Node *n = new (nothrow) Node(val);
        if (!n)
        {
            throw runtime_error("Error: No hay memoria disponible");
        }

        if (empty())
        {
            front = n;
        }
        else
        {
            back->siguiente = n;
        }
        back = n;
        size++;
    }

    void dequeue()
    {
        if (empty())
        {
            throw runtime_error("Error: Cola vacía");
        }

        Node *temp = front;
        front = front->siguiente;
        delete temp;
        size--;

        if (empty())
        {
            back = nullptr;
        }
    }

    T &top() const
    {
        if (empty())
        {
            throw runtime_error("Error: Cola vacía");
        }
        return front->data;
    }

    bool empty() const { return front == nullptr; }
    int getsize() const { return size; }

    string to_string() const
    {
        if (empty())
        {
            return "COLA VACÍA\n";
        }

        stringstream ss;
        Node *actual = front;
        ss << "=== CONTENIDO DE LA COLA ===\n";
        while (actual)
        {
            ss << "-> " << actual->data.getId() << " (Total: $"
                 << actual->data.getTotal() << ")\n";
            actual = actual->siguiente;
        }
        ss << "TOTAL PEDIDOS: " << size << "\n\n";
        return ss.str();
    }
};

#endif // QUEUE_H