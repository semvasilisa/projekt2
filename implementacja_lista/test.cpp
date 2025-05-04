#include <iostream>
#include <chrono>
#include <cstdlib>
#include <fstream>
#include <string>
#include "priorityQueue1.h"

using namespace std;
using namespace chrono;

const int NUM_QUEUES = 10; //ile kopii kolejek będzie stworzono 
const int MAX_SIZE = 100000; //rozmiar największej kolejki
int values[MAX_SIZE]; //tablica liczb które będą dodane do kolejki
int priorities[MAX_SIZE]; //tablica priorytetów odpowiadających wartościam w tablice values

//generujemy tablicy odpowiedniego rozmiaru, zapisujemy do pliku
void generate_and_save_data_files() {
    int sizes[] = { 5000, 8000, 10000, 16000, 20000, 40000, 60000, 100000 };
    for (int s = 0; s < 8; s++) {
        int n = sizes[s];
        //tworzymy dwa pliki: dla wartości i priorytetów
        ofstream valFile("values_" + to_string(n) + ".txt");
        ofstream prioFile("priorities_" + to_string(n) + ".txt");

        //w pętli generujemy wartości i odpowiadające im priorytety 
        for (int i = 0; i < n; i++) {
            int value = rand() % 100000 + 1;
            int priority = rand() % 100 + 1;
            valFile << value << "\n";
            prioFile << priority << "\n";
        }
        //zamykamy pliki do zapisu
        valFile.close();
        prioFile.close();
    }
}

// metoda do generowania losowych wartości i priorytetów
void generate_data(int n) {
    //tworzymy tabeli do dynamicznego przechowywania danych
    int* values = new int[n];
    int* priorities = new int[n];

    //otwórzamy plik zawierający wygenerowane wartości dla podanego rozmiaru 'n'
    ifstream valFile("values_" + to_string(n) + ".txt");
    //otwórzamy plik zawierający odpowiadające priorytety
    ifstream prioFile("priorities_" + to_string(n) + ".txt");

    //sprawdzamy czy udało się odtworzyć plik
    if (!valFile || !prioFile) {
        cerr << "Error opening file!" << endl;
        delete[] values;    // Clean up previously allocated memory
        delete[] priorities;
        return;
    }

    //przechodzimy wszystkie wartości i priorytety „n” i załadujemy je do tablic „values” i „priorities”
    for (int i = 0; i < n; i++) {
        valFile >> values[i];
        prioFile >> priorities[i];
    }

    //zamykamy plik do odczytu
    valFile.close();
    prioFile.close();

}

//metoda dla dynamicznego wepełnienia NUM_QUEUES tablic losowymi liczbami z tablicy values o priorytecie priorities
PriorityQueue** create_filled_queues(int n) {
    //tworzymy tablicę wskażników na kolejki
    PriorityQueue** queues = new PriorityQueue * [NUM_QUEUES];
    for (int i = 0; i < NUM_QUEUES; i++) {
        queues[i] = new PriorityQueue();
        for (int j = 0; j < n; j++) {
        //zwracamy się do metod za pomocą -> bo każdy element queues[i] jest wskażnikiem
            queues[i]->insert(values[j], priorities[j]);
        }
    }
    return queues;
}

//metoda dla zwalnienia pamięci po testach 
void destroy_queues(PriorityQueue** queues) {
    for (int i = 0; i < NUM_QUEUES; i++) {
        delete queues[i];//usuwamy kolejki
    }
    delete[] queues;//usuwamy tablicę kolejek 
}

//testowanie metody insert - dodanie elementów do kolejki
double test_insert(int n) {
    //włączenie timera
    auto start = high_resolution_clock::now();

    PriorityQueue** queues = create_filled_queues(n);

    //wyłączenie timera
    auto end = high_resolution_clock::now();

    //zwalniamy pamięć
    destroy_queues(queues);

    //zwracamy średni czas działania metody
    return duration<double, milli>(end - start).count() / NUM_QUEUES;
}

//testowanie metody extract_max - metoda do usuwania elementu o największym priorytecie
double test_extract_max(int n) {
    //tworzymy puste kolejki o rozmiarze NUM_QUEUES
    PriorityQueue** queues = create_filled_queues(n);

    //włączenie timera
    auto start = high_resolution_clock::now();

    //usuwamy element o największym priorytecie w NUM_QUEUES tablicach
    for (int i = 0; i < NUM_QUEUES; i++) {
        for (int j = 0; j < n; j++) {
            Node* node = queues[i]->extract_max();
            delete node;
        }
    }

    //wyłączenie timera
    auto end = high_resolution_clock::now();

    //zwalniamy pamięć
    destroy_queues(queues);

    //zwracamy średni czas działania metody
    return duration<double, milli>(end - start).count() / NUM_QUEUES;
}

//testowanie metody find_max - szukania elementu o największym priorytecie 
double test_find_max(int n) {
    PriorityQueue** queues = create_filled_queues(n);

    // włączenie timera
    auto start = high_resolution_clock::now();

    // szukamy element o największym priorytecie w NUM_QUEUES kolejkach
    for (int i = 0; i < NUM_QUEUES; i++) {
        queues[i]->find_max();
    }

    // wyłączenie timera
    auto end = high_resolution_clock::now();

    destroy_queues(queues); // zwalniamy pamięć 

    // zwracamy średni czas działania metody
    return duration<double, nano>(end - start).count() / NUM_QUEUES;
}

//testowanie metody modify_key - zmiany priorytetu losowo wybranego elementu 
double test_modify_key(int n) {
    PriorityQueue** queues = create_filled_queues(n);

    //włączamy timer
    auto start = high_resolution_clock::now();

    //zmienna w której ustawiamy na ilu elementach chcemy zmienić priorytet
    int limit = (n < 1000) ? n : 1000;
    //zewnętszna pętla iteruję po każdej kolejce 
    for (int i = 0; i < NUM_QUEUES; i++) {
        //wewnętrzna pętla zmienia priorytet dla 1000 elementów w każdej kolejce
        for (int j = 0; j < limit; j++) {
            //priorytet każdego elementu zmienia się na +1
            queues[i]->modify_key(values[j], priorities[j] + 1);
        }
    }

    //wyłączenie timera
    auto end = high_resolution_clock::now();

    destroy_queues(queues);//zwalniamy pamięć

    //zwracamy średni czas działania metody
    return duration<double, nano>(end - start).count() / (NUM_QUEUES * limit);
}

//testowanie metody return_size - zwraca rozmiar kolejki
double test_return_size(int n) {
    PriorityQueue** queues = create_filled_queues(n);

    // włączenie timera
    auto start = high_resolution_clock::now();

    // wywołujemy metodę return_size() na NUM_QUEUES kolejkach 
    for (int i = 0; i < NUM_QUEUES; i++) {
        queues[i]->return_size();
    }

    // wyłączenie timera
    auto end = high_resolution_clock::now();

    destroy_queues(queues); // zwalniamy pamięć

    // zwracamy średni czas działania metody
    return duration<double, nano>(end - start).count() / NUM_QUEUES;
}

int main() {
    generate_and_save_data_files();
    //na jakiego rozmiaru kolejjkach powinnyśmy przeprowadzać badania
    int sizes[] = { 5000, 8000, 10000, 16000, 20000, 40000, 60000, 100000 };

    //przeprowadzamy badanie na kolejkach o rozmiarach podanych w tablice sizes
    for (int i = 0; i < 8; i++) {
        //w zmienną n podajemy rozmiar kolejki 
        int n = sizes[i];
        cout << "Queue size: " << n << endl;
        //wypełniamy kolejkę n elementami 
        generate_data(n);

        //obliczenie średniego czasu dla każdej metody 
        cout << "Insert time: " << test_insert(n) << " ms" << endl;
        cout << "Extract max time: " << test_extract_max(n) << " ms" << endl;
        cout << "Find max time: " << test_find_max(n) << " ns" << endl;
        cout << "Modify key time: " << test_modify_key(n) << " ns" << endl;
        cout << "Return size time: " << test_return_size(n) << " ns" << endl;
        cout << "-----------------------------" << endl;
    }

    return 0;
}
