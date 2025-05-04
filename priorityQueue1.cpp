#include "priorityQueue.h"

// Konstruktor
template<typename T>
PriorityQueue<T>::PriorityQueue() {
    head = nullptr;
}

// Destruktor
template<typename T>
PriorityQueue<T>::~PriorityQueue() {
    Node<T>* current = head;
    while (current != nullptr) {
        Node<T>* temp = current;
        current = current->next;
        delete temp;
    }
}

// Dodanie elementu z określonym priorytetem
template<typename T>
void PriorityQueue<T>::insert(T value, int priority) {
    Node<T>* newNode = new Node<T>{ value, priority };

    if (head == nullptr) {
        head = newNode; //jeśli lista pusta -> nowy element będzie mieć największy priorytet
        return;
    }

    //jeśli priorytet mniej niż u head to nowy element będzie głową
    if (newNode->priority < head->priority) {
        newNode->next = head;
        head = newNode;
        return;
    }

    Node<T>* current = head;

    while (current->next != nullptr && current->next->priority <= newNode->priority) {
        current = current->next;
    }

    newNode->next = current->next;
    current->next = newNode;
}

// Usunięcie i zwrócenie elementu o największym priorytecie
template<typename T>
Node<T>* PriorityQueue<T>::extract_max() {
    if (head == nullptr) return nullptr;

    Node<T>* current = head;
    head = head->next;
    current->next = nullptr;
    return current;
}

// Podejrzenie wartości elementu o największym priorytecie
template<typename T>
T PriorityQueue<T>::find_max() {
    if (head == nullptr) {
        throw std::runtime_error("Kolejka jest pusta!");
    }
    return head->value;
}

// Zmiana priorytetu elementu z daną wartością
template<typename T>
void PriorityQueue<T>::modify_key(T value, int new_priority) {
    if (head == nullptr) return;

    Node<T>* current = head;
    Node<T>* previous = nullptr;

    while (current != nullptr && current->value != value) {
        previous = current;
        current = current->next;
    }

    if (current == nullptr) return;

    T val = current->value;

    if (previous == nullptr) head = head->next;
    else previous->next = current->next;

    delete current;
    insert(val, new_priority);
}

// Zwrócenie rozmiaru kolejki
template<typename T>
int PriorityQueue<T>::return_size() {
    int size = 0;
    Node<T>* current = head;
    while (current != nullptr) {
        size++;
        current = current->next;
    }
    return size;
}
