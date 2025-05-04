#ifndef PRIORITYQUEUE1_HPP
#define PRIORITYQUEUE1_HPP

#include <iostream>

template<typename T>
struct Node {
    T value; //liczba
    int priority; //liczba wskazująca priorytet
    Node* next; //wskaznik na następny element

    Node(T v, int p) {
        value = v;
        priority = p;
        next = nullptr;
    }
};

template<typename T>
class PriorityQueue {
    Node<T>* head;

public:
    PriorityQueue(); // konstruktor
    ~PriorityQueue(); //destruktor

    void insert(T value, int priority);  //dodanie elementu value o priorytecie priorytet
    Node<T>* extract_max(); //usunięcie i zwrócenie elementu o największym priorytecie
    T find_max(); //zwrócenie (podejrzenie) elementu o największym priorytecie
    void modify_key(T value, int new_priority); //zmiana priorytetu elementu e na p
    int return_size(); //zwrócenie rozmiaru
};

#endif