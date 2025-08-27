#ifndef IMMUTABLEARRAYSEQUENCE_H
#define IMMUTABLEARRAYSEQUENCE_H

#include "../ArraySequence.h"

template <class T>
class ImmutableArraySequence: public ArraySequence<T> {
public:
    using ArraySequence<T>::items;

    ImmutableArraySequence(): ArraySequence<T>() {}
    ImmutableArraySequence(T* array, size_t size): ArraySequence<T>(array, size) {}
    ImmutableArraySequence(const DynamicArray<T>& array): ArraySequence<T>(array) {}
    ImmutableArraySequence(const ArraySequence<T>& seq): ArraySequence<T>(seq) {}

    Sequence<T>* GetSubsequence(size_t start, size_t end) const override {
        if (start > end || end >= this->GetLength()) {
            throw std::out_of_range("Invalid index!");
        }

        size_t len = end - start + 1;

        T* newArray = new T[len];
        for (size_t i = 0; i < len; i++) {
            newArray[i] = this->items->Get(start + i);
        }

        ImmutableArraySequence<T>* result = new ImmutableArraySequence<T>(newArray, len);

        delete[] newArray;

        return result;
    }

    Sequence<T>* Append(const T& item) override {
        ImmutableArraySequence<T>* result = new ImmutableArraySequence<T>(*this);

        result->items->Append(item);

        return result;
    }

    Sequence<T>* Prepend(const T& item) override {
        DynamicArray<T>* array = new DynamicArray<T>(this->items->GetLength() + 1);

        array->Append(item);
        for (size_t i = 0; i < this->items->GetLength(); i++) {
            array->Append(this->items->Get(i));
        }

        ImmutableArraySequence<T>* result = new ImmutableArraySequence<T>(*array);
        delete array;

        return result;
    }

    Sequence<T>* InsertAt(const T& item, size_t index) override {
        if (index > this->items->GetLength()) {
            throw std::out_of_range("Index out of range");
        }

        DynamicArray<T>* newArray = new DynamicArray<T>(this->items->GetLength() + 1);

        for (size_t i = 0; i < index; i++) {
            newArray->Append(this->items->Get(i));
        }

        newArray->Append(item);

        for (size_t i = index; i < this->items->GetLength(); i++) {
            newArray->Append(this->items->Get(i));
        }
        ImmutableArraySequence<T>* result = new ImmutableArraySequence<T>(*newArray);

        delete newArray;
        return result;
    }

    Sequence<T>* Concat(const Sequence<T>* other) override {
        ImmutableArraySequence<T>* result = new ImmutableArraySequence<T>(*this);
        for (size_t i = 0; i < other->GetLength(); i++) {
            result->items->Append(other->Get(i));
        }

        return result;
    }

    Sequence<T>* Clone() override {
        return new ImmutableArraySequence<T>(*this);
    }
};

#endif

