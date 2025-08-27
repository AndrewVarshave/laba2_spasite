#ifndef MUTABLELISTSEQUENCE_H
#define MUTABLELISTSEQUENCE_H

#include "../ListSequence.h"

template <class T>
class MutableListSequence: public ListSequence<T> {
public:
    using ListSequence<T>::items;

    MutableListSequence() : ListSequence<T>() {}
    MutableListSequence(T* array, size_t size): ListSequence<T>(array, size) {}
    MutableListSequence(const LinkedList<T>& list): ListSequence<T>(list) {}
    MutableListSequence(const ListSequence<T>& seq): ListSequence<T>(seq) {}

    Sequence<T>* GetSubsequence(size_t start, size_t end) const override {
        if (start > end || end >= this -> GetLength()) {
            throw out_of_range("Incorrect index!");
        }

        LinkedList<T>* subList = this -> items -> GetSubList(start, end);
        return new MutableListSequence<T>(*subList);
    }

    Sequence<T>* Append(const T& item) override {
        items -> Append(item);
        return this;
    }

    Sequence<T>* Prepend(const T& item) override {
        items -> Prepend(item);
        return this;
    }

    Sequence<T>* InsertAt(const T& item, size_t index) override {
        if (index > items -> GetLength()) {
            throw out_of_range("Index out of range!");
        }
        items -> InsertAt(item, index);
        return this;
    }

    Sequence<T>* Concat(const Sequence<T>* other) override {
        for (size_t i = 0; i < other -> GetLength(); i++) {
            items -> Append(other -> Get(i));
        }
        return this;
    }

    Sequence<T>* Clone() override {
        return new MutableListSequence<T>(*this);
    }
};

#endif
