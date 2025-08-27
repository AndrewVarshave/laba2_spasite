#ifndef TESTS_H
#define TESTS_H

#include <iostream>
#include <cassert>
#include <string>
#include "../Containers/DynamicArray.h"
#include "../Containers/LinkedList.h"
#include "../Sequences/Sequence.h"
#include "../Sequences/Mutable/MutableArraySequence.h"
#include "../Sequences/Mutable/MutableListSequence.h"
#include "../Sequences/Immutable/ImmutableArraySequence.h"
#include "../Sequences/Immutable/ImmutableListSequence.h"

template <class T>
bool sequencesEqual(const Sequence<T>* seq1, const Sequence<T>* seq2) {
    if (seq1->GetLength() != seq2->GetLength()) {
        return false;
    }

    for (size_t i = 0; i < seq1->GetLength(); i++) {
        if (seq1->Get(i) != seq2->Get(i)) {
            return false;
        }
    }

    return true;
}

void testDynamicArray() {
    std::cout << "Testing DynamicArray..." << std::endl;

    DynamicArray<int> arr1;
    assert(arr1.GetLength() == 0);

    arr1.Append(5);
    arr1.Append(10);
    arr1.Append(15);
    assert(arr1.GetLength() == 3);
    assert(arr1.Get(0) == 5);
    assert(arr1.Get(1) == 10);
    assert(arr1.Get(2) == 15);

    arr1.Resize(5);
    assert(arr1.Get(0) == 5);
    assert(arr1.Get(1) == 10);
    assert(arr1.Get(2) == 15);

    arr1.Set(1, 20);
    assert(arr1.Get(1) == 20);

    DynamicArray<int> arr2(arr1);
    assert(arr2.GetLength() == 3);
    assert(arr2.Get(0) == 5);
    assert(arr2.Get(1) == 20);
    assert(arr2.Get(2) == 15);

    int items[] = {1, 2, 3, 4};
    DynamicArray<int> arr3(items, 4);
    assert(arr3.GetLength() == 4);
    assert(arr3.Get(0) == 1);
    assert(arr3.Get(3) == 4);

    std::cout << "DynamicArray tests passed!" << std::endl;
}

void testLinkedList() {
    std::cout << "Testing LinkedList..." << std::endl;

    LinkedList<int> list1;
    assert(list1.GetLength() == 0);

    list1.Append(5);
    list1.Append(10);
    list1.Append(15);
    assert(list1.GetLength() == 3);
    assert(list1.Get(0) == 5);
    assert(list1.Get(1) == 10);
    assert(list1.Get(2) == 15);

    list1.Prepend(0);
    assert(list1.GetLength() == 4);
    assert(list1.Get(0) == 0);

    assert(list1.GetFirst() == 0);
    assert(list1.GetLast() == 15);

    list1.InsertAt(7, 2);
    assert(list1.GetLength() == 5);
    assert(list1.Get(2) == 7);

    LinkedList<int>* subList = list1.GetSubList(1, 3);
    assert(subList->GetLength() == 3);
    assert(subList->Get(0) == 5);
    assert(subList->Get(1) == 7);
    assert(subList->Get(2) == 10);
    delete subList;

    LinkedList<int> list2(list1);
    assert(list2.GetLength() == 5);
    assert(list2.Get(0) == 0);
    assert(list2.Get(2) == 7);

    int items[] = {1, 2, 3, 4};
    LinkedList<int> list3(items, 4);
    assert(list3.GetLength() == 4);
    assert(list3.Get(0) == 1);
    assert(list3.Get(3) == 4);

    std::cout << "LinkedList tests passed!" << std::endl;
}

void testMutableArraySequence() {
    std::cout << "Testing MutableArraySequence..." << std::endl;

    int items[] = {1, 2, 3, 4, 5};
    MutableArraySequence<int> seq(items, 5);
    assert(seq.GetLength() == 5);
    assert(seq.GetFirst() == 1);
    assert(seq.GetLast() == 5);

    Sequence<int>* result = seq.Append(6);
    assert(result == &seq);
    assert(seq.GetLength() == 6);
    assert(seq.GetLast() == 6);

    result = seq.Prepend(0);
    assert(result == &seq);
    assert(seq.GetLength() == 7);
    assert(seq.GetFirst() == 0);

    result = seq.InsertAt(10, 3);
    assert(result == &seq);
    assert(seq.GetLength() == 8);
    assert(seq.Get(3) == 10);

    Sequence<int>* subSeq = seq.GetSubsequence(2, 5);
    assert(subSeq->GetLength() == 4);
    assert(subSeq->Get(0) == 2);
    assert(subSeq->Get(1) == 10);
    assert(subSeq->Get(2) == 3);
    assert(subSeq->Get(3) == 4);

    int otherItems[] = {100, 200};
    MutableArraySequence<int> otherSeq(otherItems, 2);
    result = seq.Concat(&otherSeq);
    assert(result == &seq);
    assert(seq.GetLength() == 10);
    assert(seq.Get(8) == 100);
    assert(seq.Get(9) == 200);

    Sequence<int>* clone = seq.Clone();
    assert(clone != &seq);
    assert(clone->GetLength() == seq.GetLength());
    for (size_t i = 0; i < seq.GetLength(); i++) {
        assert(clone->Get(i) == seq.Get(i));
    }

    delete subSeq;
    delete clone;

    std::cout << "MutableArraySequence tests passed!" << std::endl;
}

void testMutableListSequence() {
    std::cout << "Testing MutableListSequence..." << std::endl;

    int items[] = {1, 2, 3, 4, 5};
    MutableListSequence<int> seq(items, 5);
    assert(seq.GetLength() == 5);
    assert(seq.GetFirst() == 1);
    assert(seq.GetLast() == 5);

    Sequence<int>* result = seq.Append(6);
    assert(result == &seq);
    assert(seq.GetLength() == 6);
    assert(seq.GetLast() == 6);

    result = seq.Prepend(0);
    assert(result == &seq);
    assert(seq.GetLength() == 7);
    assert(seq.GetFirst() == 0);

    result = seq.InsertAt(10, 3);
    assert(result == &seq);
    assert(seq.GetLength() == 8);
    assert(seq.Get(3) == 10);

    Sequence<int>* subSeq = seq.GetSubsequence(2, 5);
    assert(subSeq->GetLength() == 4);
    assert(subSeq->Get(0) == 2);
    assert(subSeq->Get(1) == 10);
    assert(subSeq->Get(2) == 3);
    assert(subSeq->Get(3) == 4);

    int otherItems[] = {100, 200};
    MutableListSequence<int> otherSeq(otherItems, 2);
    result = seq.Concat(&otherSeq);
    assert(result == &seq);
    assert(seq.GetLength() == 10);
    assert(seq.Get(8) == 100);
    assert(seq.Get(9) == 200);

    Sequence<int>* clone = seq.Clone();
    assert(clone != &seq);
    assert(clone->GetLength() == seq.GetLength());
    for (size_t i = 0; i < seq.GetLength(); i++) {
        assert(clone->Get(i) == seq.Get(i));
    }

    delete subSeq;
    delete clone;

    std::cout << "MutableListSequence tests passed!" << std::endl;
}

void testImmutableArraySequence() {
    std::cout << "Testing ImmutableArraySequence..." << std::endl;

    int items[] = {1, 2, 3, 4, 5};
    ImmutableArraySequence<int> seq(items, 5);
    assert(seq.GetLength() == 5);
    assert(seq.GetFirst() == 1);
    assert(seq.GetLast() == 5);

    Sequence<int>* result = seq.Append(6);
    assert(result != &seq);
    assert(seq.GetLength() == 5);
    assert(result->GetLength() == 6);
    assert(result->GetLast() == 6);

    ImmutableArraySequence<int>* seqWithAppend =
            dynamic_cast<ImmutableArraySequence<int>*>(result);

    result = seqWithAppend->Prepend(0);
    assert(result != seqWithAppend);
    assert(seqWithAppend->GetLength() == 6);
    assert(result->GetLength() == 7);
    assert(result->GetFirst() == 0);

    delete seqWithAppend;
    ImmutableArraySequence<int>* seqWithPrepend =
            dynamic_cast<ImmutableArraySequence<int>*>(result);

    result = seqWithPrepend->InsertAt(10, 3);
    assert(result != seqWithPrepend);
    assert(seqWithPrepend->GetLength() == 7);
    assert(result->GetLength() == 8);
    assert(result->Get(3) == 10);

    delete seqWithPrepend;
    ImmutableArraySequence<int>* seqWithInsert =
            dynamic_cast<ImmutableArraySequence<int>*>(result);

    Sequence<int>* subSeq = seqWithInsert->GetSubsequence(2, 5);
    assert(subSeq->GetLength() == 4);
    assert(subSeq->Get(0) == 2);
    assert(subSeq->Get(1) == 10);
    assert(subSeq->Get(2) == 3);
    assert(subSeq->Get(3) == 4);

    int otherItems[] = {100, 200};
    ImmutableArraySequence<int> otherSeq(otherItems, 2);
    result = seqWithInsert->Concat(&otherSeq);
    assert(result != seqWithInsert);
    assert(seqWithInsert->GetLength() == 8);
    assert(result->GetLength() == 10);
    assert(result->Get(8) == 100);
    assert(result->Get(9) == 200);

    Sequence<int>* clone = seqWithInsert->Clone();
    assert(clone != seqWithInsert);
    assert(clone->GetLength() == seqWithInsert->GetLength());
    for (size_t i = 0; i < seqWithInsert->GetLength(); i++) {
        assert(clone->Get(i) == seqWithInsert->Get(i));
    }

    delete subSeq;
    delete seqWithInsert;
    delete result;
    delete clone;

    std::cout << "ImmutableArraySequence tests passed!" << std::endl;
}

void testImmutableListSequence() {
    std::cout << "Testing ImmutableListSequence..." << std::endl;

    int items[] = {1, 2, 3, 4, 5};
    ImmutableListSequence<int> seq(items, 5);
    assert(seq.GetLength() == 5);
    assert(seq.GetFirst() == 1);
    assert(seq.GetLast() == 5);

    Sequence<int>* result = seq.Append(6);
    assert(result != &seq);
    assert(seq.GetLength() == 5);
    assert(result->GetLength() == 6);
    assert(result->GetLast() == 6);

    ImmutableListSequence<int>* seqWithAppend =
            dynamic_cast<ImmutableListSequence<int>*>(result);

    result = seqWithAppend->Prepend(0);
    assert(result != seqWithAppend);
    assert(seqWithAppend->GetLength() == 6);
    assert(result->GetLength() == 7);
    assert(result->GetFirst() == 0);

    delete seqWithAppend;
    ImmutableListSequence<int>* seqWithPrepend =
            dynamic_cast<ImmutableListSequence<int>*>(result);

    result = seqWithPrepend->InsertAt(10, 3);
    assert(result != seqWithPrepend);
    assert(seqWithPrepend->GetLength() == 7);
    assert(result->GetLength() == 8);
    assert(result->Get(3) == 10);

    delete seqWithPrepend;
    ImmutableListSequence<int>* seqWithInsert =
            dynamic_cast<ImmutableListSequence<int>*>(result);

    Sequence<int>* subSeq = seqWithInsert->GetSubsequence(2, 5);
    assert(subSeq->GetLength() == 4);
    assert(subSeq->Get(0) == 2);
    assert(subSeq->Get(1) == 10);
    assert(subSeq->Get(2) == 3);
    assert(subSeq->Get(3) == 4);

    int otherItems[] = {100, 200};
    ImmutableListSequence<int> otherSeq(otherItems, 2);
    result = seqWithInsert->Concat(&otherSeq);
    assert(result != seqWithInsert);
    assert(seqWithInsert->GetLength() == 8);
    assert(result->GetLength() == 10);
    assert(result->Get(8) == 100);
    assert(result->Get(9) == 200);

    Sequence<int>* clone = seqWithInsert->Clone();
    assert(clone != seqWithInsert);
    assert(clone->GetLength() == seqWithInsert->GetLength());
    for (size_t i = 0; i < seqWithInsert->GetLength(); i++) {
        assert(clone->Get(i) == seqWithInsert->Get(i));
    }

    delete subSeq;
    delete seqWithInsert;
    delete result;
    delete clone;

    std::cout << "ImmutableListSequence tests passed!" << std::endl;
}

void runAllTests() {
    std::cout << "===== Running all tests =====\n" << std::endl;

    try {
        testDynamicArray();
        testLinkedList();
        testMutableArraySequence();
        testMutableListSequence();
        testImmutableArraySequence();
        testImmutableListSequence();

        std::cout << "\nAll tests passed successfully!" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "\nTest failed with error: " << e.what() << std::endl;
    } catch (...) {
        std::cout << "\nTest failed with unknown error!" << std::endl;
    }
}

#endif