#ifndef MUTABLEARRAYSEQUENCE_H
#define MUTABLEARRAYSEQUENCE_H

#include "../ArraySequence.h"

template <class T>
class MutableArraySequence: public ArraySequence<T> {
public:
    using ArraySequence<T>::items;

    MutableArraySequence() : ArraySequence<T>() {}

    MutableArraySequence(T *array, size_t size) : ArraySequence<T>(array, size) {}

    MutableArraySequence(const DynamicArray<T> &arr) : ArraySequence<T>(arr) {}

    MutableArraySequence(const ArraySequence<T> &seq) : ArraySequence<T>(seq) {}

    Sequence<T>* GetSubsequence(size_t start, size_t end) const override {
        if (start > end || end >= this->GetLength()) {
            throw std::out_of_range("Invalid index!");
        }

        size_t len = end - start + 1;
        DynamicArray<T> arr(len);

        for (size_t i = start; i <= end; ++i) {
            arr.Append(this->items->Get(i));
        }

        return new MutableArraySequence<T>(arr);
    }

    Sequence<T>* Append(const T &item) override {
        items->Append(item);
        return this;
    }

    Sequence<T>* Prepend(const T& item) override {
        DynamicArray<T>* array = new DynamicArray<T>(items->GetLength() + 1);
        array->Append(item);
        for (size_t i = 0; i < items->GetLength(); ++i) {
            array->Append(items -> Get(i));
        }
        delete items;
        items = array;
        return this;
    }

    Sequence<T>* InsertAt(const T &item, size_t index) override {
        if (index > items -> GetLength()) {
            throw std::out_of_range("Index out of range");
        }

        DynamicArray<T>* newArray = new DynamicArray<T>(items -> GetLength() + 1);
        for (size_t i = 0; i < index; ++i) {
            newArray->Append(items->Get(i));
        }
        newArray->Append(item);
        for (size_t i = index; i < items -> GetLength(); ++i) {
            newArray->Append(items->Get(i));
        }
        delete items;
        items = newArray;
        return this;
    }

    Sequence<T>* Concat(const Sequence<T> *other) override {
        for (size_t i = 0; i < other->GetLength(); ++i) {
            items->Append(other->Get(i));
        }
        return this;
    }

    Sequence<T>* Clone() override {
        return new MutableArraySequence<T>(*this);
    }

};

#endif
