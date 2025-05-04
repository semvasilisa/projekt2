#include <iostream>
#include <chrono>
#include <fstream>
#include <sstream>
#include "PriorityQueue.h"

using namespace std;
using namespace chrono;

const int NUM_QUEUES = 10;
const int MAX_SIZE = 100000;
int values[MAX_SIZE];
int priorities[MAX_SIZE];

//metoda dla odczytu danych z plików
void load_data_from_files(int n) {
    //tworzymy tablei dynamicznie 
    int* values = new int[n];
    int* priorities = new int[n];

    //ścieżki do plików z priorytetami i wartościami 
    string values_filename = "D:\\SD\\priorityQueue\\values_" + to_string(n) + ".txt";
    string priorities_filename = "D:\\SD\\priorityQueue\\priorities_" + to_string(n) + ".txt";

    ifstream valFile(values_filename);
    ifstream prioFile(priorities_filename);

    if (!valFile.is_open() || !prioFile.is_open()) {
        cerr << "Error opening files for size " << n << endl;
        delete[] values;   
        delete[] priorities;
        return;
    }

    //odczytujemy wartości i priorytety z pliku
    for (int i = 0; i < n; i++) {
        valFile >> values[i];
        prioFile >> priorities[i];
    }

    valFile.close();
    prioFile.close();
}

template <typename T>
PriorityQueue<T>** create_filled_queues(int n) {
    PriorityQueue<T>** queues = new PriorityQueue<T>*[NUM_QUEUES];
    for (int i = 0; i < NUM_QUEUES; i++) {
        queues[i] = new PriorityQueue<T>();
        for (int j = 0; j < n; j++) {
            queues[i]->insert(values[j], priorities[j]);
        }
    }
    return queues;
}

template <typename T>
void destroy_queues(PriorityQueue<T>** queues) {
    for (int i = 0; i < NUM_QUEUES; i++) {
        delete queues[i];
    }
    delete[] queues;
}

template <typename T>
double test_insert(int n) {
    auto start = high_resolution_clock::now();
    PriorityQueue<T>** queues = create_filled_queues<T>(n);
    auto end = high_resolution_clock::now();
    destroy_queues<T>(queues);
    return duration<double, milli>(end - start).count() / NUM_QUEUES;
}

template <typename T>
double test_extract_max(int n) {
    PriorityQueue<T>** queues = create_filled_queues<T>(n);
    auto start = high_resolution_clock::now();
    for (int i = 0; i < NUM_QUEUES; i++) {
        for (int j = 0; j < n; j++) {
            queues[i]->extractMax();
        }
    }
    auto end = high_resolution_clock::now();
    destroy_queues<T>(queues);
    return duration<double, milli>(end - start).count() / NUM_QUEUES;
}

template <typename T>
double test_peek(int n) {
    PriorityQueue<T>** queues = create_filled_queues<T>(n);
    auto start = high_resolution_clock::now();
    for (int i = 0; i < NUM_QUEUES; i++) {
        queues[i]->peek();
    }
    auto end = high_resolution_clock::now();
    destroy_queues<T>(queues);
    return duration<double, nano>(end - start).count() / NUM_QUEUES;
}

template <typename T>
double test_modify_key(int n) {
    PriorityQueue<T>** queues = create_filled_queues<T>(n);
    int limit = (n < 1000) ? n : 1000;
    auto start = high_resolution_clock::now();
    for (int i = 0; i < NUM_QUEUES; i++) {
        for (int j = 0; j < limit; j++) {
            queues[i]->modifyKey(values[j], priorities[j] + 1);
        }
    }
    auto end = high_resolution_clock::now();
    destroy_queues<T>(queues);
    return duration<double, nano>(end - start).count() / (NUM_QUEUES * limit);
}

template <typename T>
double test_get_size(int n) {
    PriorityQueue<T>** queues = create_filled_queues<T>(n);
    auto start = high_resolution_clock::now();
    for (int i = 0; i < NUM_QUEUES; i++) {
        queues[i]->getSize();
    }
    auto end = high_resolution_clock::now();
    destroy_queues<T>(queues);
    return duration<double, nano>(end - start).count() / NUM_QUEUES;
}

int main() {
    int sizes[] = { 5000, 8000, 10000, 16000, 20000, 40000, 60000, 100000 };

    for (int i = 0; i < 8; i++) {
        int n = sizes[i];
        cout << "Queue size: " << n << endl;

        // Load data from files instead of generating new data
        load_data_from_files(n);

        cout << "Insert time: " << test_insert<int>(n) << " ms" << endl;
        cout << "Extract max time: " << test_extract_max<int>(n) << " ms" << endl;
        cout << "Peek time: " << test_peek<int>(n) << " ns" << endl;
        cout << "Modify key time: " << test_modify_key<int>(n) << " ns" << endl;
        cout << "Get size time: " << test_get_size<int>(n) << " ns" << endl;
        cout << "-----------------------------" << endl;
    }

    return 0;
}
