#pragma once
#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <functional>

// Linked List Node
template <typename T>
struct ListNode {
    T data;
    ListNode* next;
    ListNode(const T& val) : data(val), next(nullptr) {}
};

// Linked List Class
template <typename T>
class LinkedList {
private:
    ListNode<T>* head;

public:
    LinkedList();
    ~LinkedList();
    void append(const T& val);
    ListNode<T>* getHead() const;
};

// Dictionary (Hash Table) Class
template <typename K, typename V>
class Dictionary {
private:
    struct Node {
        K key;
        V value;
        Node* next;
        Node(const K& k, const V& v) : key(k), value(v), next(nullptr) {}
    };

    int TABLE_SIZE; // Current size of the hash table
    int numElements; // Number of elements in the hash table
    Node** table; // Array of linked lists

    int hash(const K& key) const;
    void resize();

public:
    Dictionary(int initialSize = 100);
    ~Dictionary();
    void insert(const K& key, const V& value);
    V* find(const K& key);
    bool remove(const K& key);
    void traverse(std::function<void(const K&, const V&)> callback) const;
    int getTableSize() const { return TABLE_SIZE; }
    Node** getTable() const { return table; }
};


// Linked List Implementation
template <typename T>
LinkedList<T>::LinkedList() : head(nullptr) {}

template <typename T>
LinkedList<T>::~LinkedList() {
    while (head) {
        ListNode<T>* temp = head;
        head = head->next;
        delete temp;
    }
}

template <typename T>
void LinkedList<T>::append(const T& val) {
    if (!head) {
        head = new ListNode<T>(val);
    }
    else {
        ListNode<T>* current = head;
        while (current->next) {
            current = current->next;
        }
        current->next = new ListNode<T>(val);
    }
}

template <typename T>
ListNode<T>* LinkedList<T>::getHead() const {
    return head;
}

// Dictionary Implementation
template <typename K, typename V>
Dictionary<K, V>::Dictionary(int initialSize) : TABLE_SIZE(initialSize), numElements(0) {
    table = new Node * [TABLE_SIZE]();
}

template <typename K, typename V>
Dictionary<K, V>::~Dictionary() {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        Node* current = table[i];
        while (current) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }
    delete[] table;
}

template <typename K, typename V>
int Dictionary<K, V>::hash(const K& key) const {
    std::hash<K> hasher;
    return hasher(key) % TABLE_SIZE;
}

template <typename K, typename V>
void Dictionary<K, V>::resize() {
    int oldSize = TABLE_SIZE;
    TABLE_SIZE *= 2;
    Node** newTable = new Node * [TABLE_SIZE]();

    for (int i = 0; i < oldSize; ++i) {
        Node* current = table[i];
        while (current) {
            Node* next = current->next;
            int newIndex = hash(current->key);
            current->next = newTable[newIndex];
            newTable[newIndex] = current;
            current = next;
        }
    }

    delete[] table;
    table = newTable;
}

template <typename K, typename V>
void Dictionary<K, V>::insert(const K& key, const V& value) {
    if ((double)numElements / TABLE_SIZE > 0.7) {
        resize();
    }

    int index = hash(key);
    Node* newNode = new Node(key, value);
    newNode->next = table[index];
    table[index] = newNode;
    numElements++;
}

template <typename K, typename V>
V* Dictionary<K, V>::find(const K& key) {
    int index = hash(key);
    Node* current = table[index];
    while (current) {
        if (current->key == key) {
            return &(current->value);
        }
        current = current->next;
    }
    return nullptr;
}

template <typename K, typename V>
bool Dictionary<K, V>::remove(const K& key) {
    int index = hash(key);
    Node* current = table[index];
    Node* prev = nullptr;
    while (current) {
        if (current->key == key) {
            if (prev) {
                prev->next = current->next;
            }
            else {
                table[index] = current->next;
            }
            delete current;
            numElements--;
            return true;
        }
        prev = current;
        current = current->next;
    }
    return false;
}

template <typename K, typename V>
void Dictionary<K, V>::traverse(std::function<void(const K&, const V&)> callback) const {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        Node* current = table[i];
        while (current) {
            callback(current->key, current->value);
            current = current->next;
        }
    }
}

#endif // DICTIONARY_H
