#ifndef STACK_H
#define STACK_H

#define MAX_TRACKED_ACTIONS 5

#include <iostream>
#include <sstream>

using namespace std;

template <typename T>
class Stack {
    private:
    struct Node
    {
        T data;
        Node *next;
        Node() : next(nullptr) {}
        Node(T data) : data(data), next(nullptr) {}
    };
    Node *head; // Push y pop
    Node *tail; // Eliminar si _size excede MAX_TRACKED_ACTIONS
    size_t _size;

public:
    Stack() : _size(0), head(nullptr), tail(nullptr) {} // Default constructor
    Stack(const Stack &other)
    { // Copy constructor (inserts all values)
        Node *t = other.head;
        while (t != nullptr)
        {
            push(t->data);
            t = t->next;
        }
    }
    Stack(Stack &&other) : _size(other._size), head(other.head), tail(other.tail) {}

    void push(T val)
    {
        Node *n = new Node(val);
        n->next = head;
        if (head == nullptr)
            tail = n;
        head = n;

        if (_size == MAX_TRACKED_ACTIONS)
        {
            Node *t = head;
            while (t->next != tail)
                t = t->next;
            t->next = nullptr;
            delete tail;
            tail = t;
            _size--;
        }
        _size++;
    }

    void pop()
    {
        if (head == nullptr)
            return;
        Node *d = head;
        head = d->next;
        delete d;
        if (head == nullptr)
            tail = nullptr;
        _size--;
    }

    void clear()
    {
        if (head == nullptr)
            return;
        while (head != nullptr)
        {
            pop();
        }
    }

    T top()
    {
        if (head == nullptr)
            throw out_of_range("Stack is empty");
        return head->data;
    }
    size_t size()
    {
        return _size;
    }
};

#endif // STACK_H