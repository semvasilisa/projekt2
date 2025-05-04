
#ifndef PRIORITY_QUEUE2_HPP
#define PRIORITY_QUEUE2_HPP// PriorityQueue.hpp
#include <iostream>

template <typename T>
class PriorityQueue  // Priority queue using max-heap
{
private:
    struct Node
    {
        T element;
        int priority;
    };

    Node* heap;
    int size;
    int capacity;

    void resize();
    void siftUp(int index);
    void siftDown(int index);

public:
    PriorityQueue(int initialCapacity = 16);
    ~PriorityQueue();

    int getSize() const { return size; };
    int getCapacity() const { return capacity; };
    bool isEmpty() const { return size == 0; };

    void insert(const T& element, int priority);
    T extractMax();
    T peek() const;
    void modifyKey(const T& element, int newPriority);
};

template <typename T>
PriorityQueue<T>::PriorityQueue(int initialCapacity) : size(0), capacity(initialCapacity)
{
    heap = new Node[capacity];
}

template <typename T>
PriorityQueue<T>::~PriorityQueue()
{
    delete[] heap;
}

template <typename T>
void PriorityQueue<T>::resize()
{
    capacity *= 2;
    Node* newHeap = new Node[capacity];
    for (int i = 0; i < size; ++i)
    {
        newHeap[i] = heap[i];
    }
    delete[] heap;  // Free the old heap memory
    heap = newHeap;
}

template <typename T>
void PriorityQueue<T>::siftUp(int index)
{
    while (index > 0)
    {
        int parentIndex = (index - 1) / 2;
        if (heap[index].priority <= heap[parentIndex].priority)
            break;

        std::swap(heap[index], heap[parentIndex]);
        index = parentIndex;
    }
}

template <typename T>
void PriorityQueue<T>::siftDown(int index)
{
    while (index < size)
    {
        int leftChildIndex = 2 * index + 1;
        int rightChildIndex = 2 * index + 2;
        int largestIndex = index;

        if (leftChildIndex < size && heap[leftChildIndex].priority > heap[largestIndex].priority)
            largestIndex = leftChildIndex;

        if (rightChildIndex < size && heap[rightChildIndex].priority > heap[largestIndex].priority)
            largestIndex = rightChildIndex;

        if (largestIndex == index)
            break;

        std::swap(heap[index], heap[largestIndex]);
        index = largestIndex;
    }
}

template <typename T>
void PriorityQueue<T>::insert(const T& element, int priority)
{
    if (size == capacity)
        resize();

    heap[size] = Node{ element, priority };
    siftUp(size);
    size++;
}

template <typename T>
T PriorityQueue<T>::extractMax()
{
    if (isEmpty())
        throw std::runtime_error("Priority queue is empty.");

    T maxElement = heap[0].element;
    heap[0] = heap[size - 1];  // Move the last element to the root
    size--;
    siftDown(0);
    return maxElement;
}

template <typename T>
T PriorityQueue<T>::peek() const
{
    if (isEmpty())
        throw std::runtime_error("Priority queue is empty.");

    return heap[0].element;
}

template <typename T>
void PriorityQueue<T>::modifyKey(const T& element, int newPriority)
{
    for (int i = 0; i < size; ++i)
    {
        if (heap[i].element == element)
        {
            int oldPriority = heap[i].priority;
            heap[i].priority = newPriority;

            if (newPriority > oldPriority)
                siftUp(i);
            else
                siftDown(i);

            return;
        }
    }

    throw std::runtime_error("Element not found in the priority queue.");
}
#endif