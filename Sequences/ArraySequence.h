#ifndef ARRAYSEQUENCE_H
#define ARRAYSEQUENCE_H

#include "Sequence.h"
#include "../Containers/DynamicArray.h"

template <class T>
class ArraySequence: public Sequence<T> {
protected:
    DynamicArray<T>* items;
public:
    ArraySequence(): items(new DynamicArray<T>()) {}
    ArraySequence(size_t size): items(new DynamicArray<T>(size)) {}
    ArraySequence(T* array, size_t size): items(new DynamicArray<T>(array, size)) {}
    ArraySequence(const DynamicArray<T>& array): items(new DynamicArray<T>(array)) {}
    ArraySequence(const ArraySequence<T>& other): items(new DynamicArray(*other.items)) {}

    virtual ~ArraySequence() { delete items; }
    T GetFirst() const override { return items->Get(0); }
    T GetLast() const override { return items->Get(items->GetLength() - 1); }
    T Get(size_t index) const override { return items->Get(index); }
    size_t GetLength() const override { return items->GetLength(); }
    virtual Sequence<T>* GetSubsequence(size_t start, size_t end) const = 0;
    virtual Sequence<T>* Append(const T& item) = 0;
    virtual Sequence<T>* Prepend(const T& item) = 0;
    virtual Sequence<T>* InsertAt(const T& item, size_t index) = 0;
    virtual Sequence<T>* Concat(const Sequence<T>* other) = 0;
    virtual Sequence<T>* Clone() = 0;
};


#endif 
