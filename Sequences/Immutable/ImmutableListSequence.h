
#ifndef LAB2_TIMUR_IMMUTABLELISTSEQUENCE_H
#define LAB2_TIMUR_IMMUTABLELISTSEQUENCE_H

#include "../ListSequence.h"

#include "../ListSequence.h"

template <class T>
class ImmutableListSequence: public ListSequence<T> {
public:
    using ListSequence<T>::items;

    ImmutableListSequence(): ListSequence<T>() {}
    ImmutableListSequence(T* array, size_t size): ListSequence<T>(array, size) {}
    ImmutableListSequence(const LinkedList<T>& list): ListSequence<T>(list) {}
    ImmutableListSequence(const ListSequence<T>& seq): ListSequence<T>(seq) {}

    Sequence<T>* GetSubsequence(size_t start, size_t end) const override {
        if (start > end || end >= this->GetLength()) {
            throw out_of_range("Incorrect index!");
        }

        LinkedList<T>* subList = this->items->GetSubList(start, end);
        ImmutableListSequence<T>* result = new ImmutableListSequence<T>(*subList);
        delete subList;
        return result;
    }

    Sequence<T>* Append(const T& item) override {
        ImmutableListSequence<T>* result = new ImmutableListSequence<T>(*this);
        result->items->Append(item);
        return result;
    }

    Sequence<T>* Prepend(const T& item) override {
        ImmutableListSequence<T>* result = new ImmutableListSequence<T>(*this);
        result->items->Prepend(item);
        return result;
    }

    Sequence<T>* InsertAt(const T& item, size_t index) override {
        if (index > this->items->GetLength()) {
            throw out_of_range("Incorrect index!");
        }

        ImmutableListSequence<T>* result = new ImmutableListSequence<T>(*this);
        result->items->InsertAt(item, index);
        return result;
    }

    Sequence<T>* Concat(const Sequence<T>* other) override {
        ImmutableListSequence<T>* result = new ImmutableListSequence<T>(*this);

        for (size_t i = 0; i < other->GetLength(); i++) {
            result->items->Append(other->Get(i));
        }

        return result;
    }

    Sequence<T>* Clone() override {
        return new ImmutableListSequence<T>(*this);
    }
};

#endif
