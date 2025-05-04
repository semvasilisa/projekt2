#include "priorityQueue1.h"

// Konstruktor
PriorityQueue::PriorityQueue() {
    head = nullptr;
}

// Destruktor
PriorityQueue::~PriorityQueue() {
    Node* current = head;
    while (current != nullptr) {
        Node* temp = current;
        current = current->next;
        delete temp;
    }
}

// Dodanie elementu z określonym priorytetem
void PriorityQueue::insert(int value, int priority) {
    Node* newNode = new Node{ value,priority };

    if (head == nullptr) {
        head = newNode;//jeśli lista pusta -> nowy element będzie mieć największy priorytet
        return;
    }

    //jeśli priorytet mniej niż u head to nowy element będzie głową
    if (newNode->priority < head->priority) {
        newNode->next = head;
        head = newNode;
        return;
    }

    Node* current = head;

    while (current->next != nullptr && current->next->priority <= newNode->priority) {
        current = current->next;
    }

    newNode->next = current->next;
    current->next = newNode;
}

// Usunięcie i zwrócenie elementu o największym priorytecie
Node* PriorityQueue::extract_max() {
    if (head == nullptr) return nullptr;

    Node* current = head;
    head = head->next;
    current->next = nullptr;
    return current;
}

// Podejrzenie wartości elementu o największym priorytecie
int PriorityQueue::find_max() {
    if (head == nullptr) {
        throw std::runtime_error("Kolejka jest pusta!");
    }
    return head->value;
}

// Zmiana priorytetu elementu z daną wartością
void PriorityQueue::modify_key(int value, int new_priority) {
    if (head == nullptr) return;

    Node* current = head;
    Node* previous = nullptr;

    while (current != nullptr && current->value != value) {
        previous = current;
        current = current->next;
    }

    if (current == nullptr) return;

    int val = current->value;


    if (previous == nullptr)  head = head->next;
    else previous->next = current->next;

    delete current;
    insert(val, new_priority);
}

// Zwrócenie rozmiaru kolejki
int PriorityQueue::return_size() {
    int size = 0;
    Node* current = head;
    while (current != nullptr) {
        size++;
        current = current->next;
    }
    return size;
}