#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <iostream>

using namespace std;

template <class T>
class Sequence {
public:
    virtual ~Sequence() {}
    virtual T GetFirst() const = 0;
    virtual T GetLast() const = 0;
    virtual T Get(const size_t index) const = 0;
    virtual size_t GetLength() const = 0;
    virtual Sequence<T>* GetSubsequence(size_t startIndex, size_t endIndex) const = 0;
    virtual Sequence<T>* Append(const T& item) = 0;
    virtual Sequence<T>* Prepend(const T& item) = 0;
    virtual Sequence<T>* InsertAt(const T& item, size_t index) = 0;
    virtual Sequence<T>* Concat(const Sequence<T>* list) = 0;
    virtual Sequence<T>* Clone() = 0;
};


#endif
