#ifndef LISTSEQUENCE_H
#define LISTSEQUENCE_H

#include "Sequence.h"
#include "../Containers/LinkedList.h"

template <class T>
class ListSequence: public Sequence<T> {
protected:
    LinkedList<T>* items;
public:
    ListSequence(): items(new LinkedList<T>()) {}
    ListSequence(T* array, size_t size): items(new LinkedList<T>(array, size)) {}
    ListSequence(const LinkedList<T>& list): items(new LinkedList<T>(list)) {}
    ListSequence(const ListSequence<T>& other): items(new LinkedList<T>(*other.items)) {}

    virtual ~ListSequence() {delete items; }
    T GetFirst() const override { return items -> GetFirst(); }
    T GetLast() const override { return items -> GetLast(); }
    T Get(size_t index) const override { return items -> Get(index); }
    size_t GetLength() const override { return items -> GetLength(); }
    virtual Sequence<T>* GetSubsequence(size_t start, size_t end) const = 0;
    virtual Sequence<T>* Append(const T& item) = 0;
    virtual Sequence<T>* Prepend(const T& item) = 0;
    virtual Sequence<T>* InsertAt(const T& item, size_t index) = 0;
    virtual Sequence<T>* Concat(const Sequence<T>* other) = 0;
    virtual Sequence<T>* Clone() = 0;
};

#endif
