#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include <string>
#include "Dict.h"
#include "TableEntry.h"

#include "../PRA_2526_P1/ListLinked.h"

template <typename V>
class HashTable : public Dict<V> {
private:
    int n;
    int max;
    ListLinked<TableEntry<V>>** table;

    int h(std::string key) {
        int sum = 0;
        for (size_t i = 0; i < key.size(); i++) sum += int(key.at(i));
        return sum % max;
    }

    int findPos(int idx, const std::string& key) {
        int len = table[idx]->size();
        for (int i = 0; i < len; i++) {
            if (table[idx]->get(i).key == key) return i;
        }
        return -1;
    }

public:
    HashTable(int size) : n(0), max(size) {
        if (size <= 0) throw std::runtime_error("Invalid hash table size");
        table = new ListLinked<TableEntry<V>>*[max];
        for (int i = 0; i < max; i++) table[i] = new ListLinked<TableEntry<V>>();
    }

    ~HashTable() {
        for (int i = 0; i < max; i++) delete table[i];
        delete[] table;
    }

    void insert(std::string key, V value) override {
        int idx = h(key);
        if (findPos(idx, key) != -1) throw std::runtime_error("Key already exists");
        int len = table[idx]->size();
        table[idx]->insert(len, TableEntry<V>(key, value));
        n++;
    }

    V search(std::string key) override {
        int idx = h(key);
        int pos = findPos(idx, key);
        if (pos == -1) throw std::runtime_error("Key not found");
        return table[idx]->get(pos).value;
    }

    V remove(std::string key) override {
        int idx = h(key);
        int pos = findPos(idx, key);
        if (pos == -1) throw std::runtime_error("Key not found");
        TableEntry<V> te = table[idx]->remove(pos);
        n--;
        return te.value;
    }

    int entries() override {
        return n;
    }

    int capacity() {
        return max;
    }

    V operator[](std::string key) {
        return search(key);
    }

    friend std::ostream& operator<<(std::ostream &out, const HashTable<V> &th) {
        out << "HashTable(n=" << th.n << ", max=" << th.max << ")\n";
        for (int i = 0; i < th.max; i++) {
            out << "[" << i << "] " << *(th.table[i]) << "\n";
        }
        return out;
    }
};

#endif

