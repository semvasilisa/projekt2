#ifndef PRIORITYQUEUE1_HPP
#define PRIORITYQUEUE1_HPP

#include <iostream>

struct Node {
    int value;//liczba
    int priority;//liczba wskazająca priorytet
    Node* next;//wskaznik na następny element

    Node(int v, int p) {
        value = v;
        priority = p;
        next = nullptr;
    }
};

class PriorityQueue {
    Node* head;

public:
    PriorityQueue(); // konstruktro
    ~PriorityQueue(); //destruktor

    void insert(int value, int priority);  //dodanie elementu value o priorytecie priorytet
    Node* extract_max(); //usunięcie i zwrócenie elementu o największym priorytecie
    int find_max(); //zwrócenie (podejrzenie) elementu o największym priorytecie
    void modify_key(int value, int new_priority); //zmiana priorytetu elementu e na p
    int return_size(); //zwrócenie rozmiaru
};

#endif