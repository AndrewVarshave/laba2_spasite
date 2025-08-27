
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdexcept>
#include <iostream>

using namespace std;

template <class T>
class LinkedList {
private:
    struct Node {
        T item;
        Node* next;

        Node(const T& item, Node* next = nullptr): item(item), next(next) {}
    };
    Node* head;
    Node* tail;
    size_t size;
public:
    LinkedList(): head(nullptr), tail(nullptr), size(0) {}

    LinkedList(T* items, size_t count): head(nullptr), tail(nullptr), size(0) {
        for (size_t i = 0; i < count; i++) {
            Append(items[i]);
        }
    }

    LinkedList(const LinkedList<T>& list): head(nullptr), tail(nullptr), size(0) {
        Node* current = list.head;
        while (current != nullptr) {
            Append(current->item);
            current = current->next;
        }
    }

    ~LinkedList() {
        Clear();
    }

    void Clear() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }

        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    void Append(const T& item) {
        Node* newNode = new Node(item);
        if (size == 0) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    void Prepend(const T& item) {
        Node* newNode = new Node(item);
        if (size == 0) {
            head = newNode;
            tail = newNode;
        } else {
            newNode->next = head;
            head = newNode;
        }
        size++;
    }

    T GetFirst() {
        if (size == 0) {
            throw out_of_range("List is empty!");
        }

        return head->item;
    }

    T GetLast() {
        if (size == 0) {
            throw out_of_range("List is empty!");
        }

        return tail->item;
    }

    size_t GetLength() {
        return size;
    }

    T Get(size_t index) {
        if (index >= size) {
            throw out_of_range("Incorrect Index!");
        }

        Node* current = head;
        for (size_t i = 0; i < index; i++) {
            current = current->next;
        }

        return current->item;
    }

    LinkedList<T>* GetSubList(size_t startIndex, size_t endIndex) {
        if (startIndex >= size || endIndex >= size) {
            throw out_of_range("Incorrect index!");
        }

        if (startIndex > endIndex) {
            throw logic_error("StartIndex > EndIndex - Error!");
        }

        LinkedList<T>* subList = new LinkedList<T>();
        Node* current = head;
        for (size_t i = 0; i <= endIndex; i++) {
            if (i >= startIndex) {
                subList->Append(current->item);
            }
            current = current->next;
        }

        return subList;
    }

    void InsertAt(const T& item, size_t index) {
        if (index > size) {
            throw out_of_range("Incorrect index!");
        }

        if (index == 0) {
            Prepend(item);
            return;
        }

        if (index == size) {
            Append(item);
            return;
        }

        Node* prev = head;
        for (size_t i = 0; i < index - 1; i++) {
            prev = prev->next;
        }

        Node* newNode = new Node(item, prev->next);
        prev->next = newNode;
        size++;
    }

    void Concat(const LinkedList<T>& other) {
        Node* current = other.head;
        while (current != nullptr) {
            Append(current->item);
            current = current->next;
        }
    }

};


#endif
