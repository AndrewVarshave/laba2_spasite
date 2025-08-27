#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <string>
#include "../Containers/DynamicArray.h"
#include "../Containers/LinkedList.h"
#include "../Sequences/Sequence.h"
#include "../Sequences/Mutable/MutableArraySequence.h"
#include "../Sequences/Mutable/MutableListSequence.h"
#include "../Sequences/Immutable/ImmutableArraySequence.h"
#include "../Sequences/Immutable/ImmutableListSequence.h"

template <class T>
void printSequence(const Sequence<T>* seq) {
    if (seq->GetLength() == 0) {
        std::cout << "{}" << std::endl;
        return;
    }

    std::cout << "{" << seq->Get(0);
    for (size_t i = 1; i < seq->GetLength(); i++) {
        std::cout << ", " << seq->Get(i);
    }
    std::cout << "}" << std::endl;
}

void printMainMenu() {
    std::cout << "\n==== Sequence Menu ====\n";
    std::cout << "1. Sequences\n";
    std::cout << "2. Run tests\n";
    std::cout << "0. Abort programm\n";
    std::cout << "Select action: ";
}

void printSequenceMenu() {
    std::cout << "\n==== Select Sequence gender ====\n";
    std::cout << "1. MutableArraySequence\n";
    std::cout << "2. MutableListSequence\n";
    std::cout << "3. ImmutableArraySequence\n";
    std::cout << "4. ImmutableListSequence\n";
    std::cout << "0. Return\n";
    std::cout << "Select gender: ";
}

void printDataTypeMenu() {
    std::cout << "\n==== Type menu  ====\n";
    std::cout << "1. Int\n";
    std::cout << "2. Double\n";
    std::cout << "3. String\n";
    std::cout << "0. Rerutn\n";
    std::cout << "Select type: ";
}

void printOperationsMenu() {
    std::cout << "\n==== Operations ====\n";
    std::cout << "1. Append\n";
    std::cout << "2. Prepend\n";
    std::cout << "3. InsertAt\n";
    std::cout << "4. Get\n";
    std::cout << "5. GetSubsequence\n";
    std::cout << "6. Concat\n";
    std::cout << "7. Clone\n";
    std::cout << "8. Print\n";
    std::cout << "0. Return\n";
    std::cout << "Select operation ";
}

template <class T>
Sequence<T>* createSequence(int sequenceType) {
    size_t n;
    std::cout << "Input number of elements ";
    std::cin >> n;

    T* arr = new T[n];
    std::cout << "input elements: ";
    for (size_t i = 0; i < n; i++) {
        std::cin >> arr[i];
    }

    Sequence<T>* seq = nullptr;

    switch (sequenceType) {
        case 1:
            seq = new MutableArraySequence<T>(arr, n);
            break;
        case 2:
            seq = new MutableListSequence<T>(arr, n);
            break;
        case 3:
            seq = new ImmutableArraySequence<T>(arr, n);
            break;
        case 4:
            seq = new ImmutableListSequence<T>(arr, n);
            break;
    }

    delete[] arr;
    return seq;
}

template <class T>
Sequence<T>* createEmptySequence(int sequenceType) {
    Sequence<T>* seq = nullptr;

    switch (sequenceType) {
        case 1:
            seq = new MutableArraySequence<T>();
            break;
        case 2:
            seq = new MutableListSequence<T>();
            break;
        case 3:
            seq = new ImmutableArraySequence<T>();
            break;
        case 4:
            seq = new ImmutableListSequence<T>();
            break;
    }

    return seq;
}

template <class T>
Sequence<T>* handleImmutableOperation(Sequence<T>* original, Sequence<T>* result, bool isMutable) {
    if (!isMutable) {
        delete original;
        return result;
    }
    return original;
}

template <class T>
void operateOnSequence(Sequence<T>* &seq, bool isMutable) {
    while (true) {
        printOperationsMenu();
        int choice;
        std::cin >> choice;

        if (choice == 0) {
            break;
        }

        T value;
        size_t index, start, end;
        Sequence<T>* result = nullptr;
        Sequence<T>* otherSeq = nullptr;

        switch (choice) {
            case 1:
                std::cout << "Input Element: ";
                std::cin >> value;
                result = seq->Append(value);
                seq = handleImmutableOperation(seq, result, isMutable);
                std::cout << "Element is added." << std::endl;
                break;

            case 2:
                std::cout << "Input Element: ";
                std::cin >> value;
                result = seq->Prepend(value);
                seq = handleImmutableOperation(seq, result, isMutable);
                std::cout << "Element is added." << std::endl;
                break;

            case 3:
                std::cout << "Input Element: ";
                std::cin >> value;
                std::cout << "Input index: ";
                std::cin >> index;
                try {
                    result = seq->InsertAt(value, index);
                    seq = handleImmutableOperation(seq, result, isMutable);
                    std::cout << "Element is added." << std::endl;
                } catch (const std::exception& e) {
                    std::cout << "Some's wrong with " << e.what() << std::endl;
                }
                break;

            case 4:
                std::cout << "Input index ";
                std::cin >> index;
                try {
                    std::cout << "Element[" << index << "] = " << seq->Get(index) << std::endl;
                } catch (const std::exception& e) {
                    std::cout <<"Some's wrong with " << e.what() << std::endl;
                }
                break;

            case 5:
                std::cout << "Input first index: ";
                std::cin >> start;
                std::cout << "Input last index: ";
                std::cin >> end;
                try {
                    result = seq->GetSubsequence(start, end);
                    std::cout << "Subsequence: ";
                    printSequence(result);
                    delete result;
                } catch (const std::exception& e) {
                    std::cout << "Some's wrong with " << e.what() << std::endl;
                }
                break;

            case 6:
                std::cout << "Create a new sequence for concatetion:" << std::endl;
                otherSeq = createSequence<T>(isMutable ? 1 : 3);
                result = seq->Concat(otherSeq);
                seq = handleImmutableOperation(seq, result, isMutable);
                delete otherSeq;
                std::cout << "Sequences are concated." << std::endl;
                break;

            case 7:
                result = seq->Clone();
                std::cout << "clone is created: ";
                printSequence(result);
                delete result;
                break;

            case 8:
                std::cout << "Sequence: ";
                printSequence(seq);
                break;

            default:
                std::cout << "Wrong chose." << std::endl;
        }
    }
}

template <class T>
void runSequenceOperations(int sequenceType) {
    bool isMutable = (sequenceType == 1 || sequenceType == 2);
    std::cout << "Create Sequence:" << std::endl;
    Sequence<T>* seq = createSequence<T>(sequenceType);

    std::cout << "Start sequence: ";
    printSequence(seq);

    operateOnSequence(seq, isMutable);

    delete seq;
}


#endif