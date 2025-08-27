#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include <stdexcept>
#include <iostream>

using namespace std;

template <class T>
class DynamicArray {
private:
    T* data;
    size_t size;
    size_t capacity;
public:
    DynamicArray(): size(0), capacity(10) {
        data = new T[capacity];
    }

    DynamicArray(T* items, size_t size): size(size), capacity(size) {
        data = new T[capacity];
        for (size_t i = 0; i < size; i++) {
            data[i] = items[i];
        }
    }

    DynamicArray(size_t size): size(0), capacity(size) {
        data = new T[capacity];
    }

    DynamicArray(const DynamicArray<T>& other) {
        size = other.size;
        capacity = other.capacity;
        data = new T[capacity];
        for (size_t i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }

    ~DynamicArray() {
        delete[] data;
    }

    void Append(const T& item) {
        if (size == capacity) {
            Resize(capacity * 2);
        }
        data[size] = item;
        size++;
    }

    T Get(const size_t index) const {
        if (index >= size) {
            throw out_of_range("Invalid index!");
        }
        return data[index];
    }

    size_t GetLength() const {
        return size;
    }

    void Set(const size_t index, const T & value) {
        if (index >= size) {
            throw out_of_range("Invalid index!");
        }
        data[index] = value;
    }

    void Resize(size_t newSize) {
        if (newSize < size) {
            throw logic_error("New size is less than old size!");
        }
        T* newData = new T[newSize];
        for (size_t i = 0; i < size; i++) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        capacity = newSize;
    }

    DynamicArray& operator=(const DynamicArray<T>& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            capacity = other.capacity;
            data = new T[capacity];
            for (size_t i = 0; i < size; i++) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }
};


#endif
