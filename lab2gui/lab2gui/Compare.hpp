#pragma once
#include <random>
#include <chrono>
#include "DynamicArray.hpp"
#include "TreeDictionary.hpp"
#include "HashTable.hpp"

struct CompareRow {
    double insertMillis;   
    double searchMicros;  
    size_t found;     
};

struct CompareResult {
    CompareRow linear;
    CompareRow tree;
    CompareRow hash;
};

inline size_t CompareHash(int key) { return key; }


class LinearList {
private:
    DynamicArray<int> array;
public:
    void Add(int key, int) { array.Add(key); }
    bool ContainsKey(int key) {
        for(size_t i=0; i<array.GetSize(); ++i) {
            if(array[i]==key) { return true; }
        }
        return false;
    }
};


template <typename Dict>
CompareRow Measure(Dict& dict, const DynamicArray<int>& keys, const DynamicArray<int>& queries) {
    using Clock = std::chrono::steady_clock;

    auto t0 = Clock::now();
    for(size_t i=0; i<keys.GetSize(); ++i) { dict.Add(keys[i], keys[i]); }
    auto t1 = Clock::now();

    size_t found = 0;
    for(size_t i=0; i<queries.GetSize(); ++i) {
        if(dict.ContainsKey(queries[i])) { ++found; }
    }
    auto t2 = Clock::now();

    CompareRow row;
    row.insertMillis = std::chrono::duration<double, std::milli>(t1-t0).count();
    row.searchMicros = std::chrono::duration<double, std::micro>(t2-t1).count() / queries.GetSize();
    row.found = found;
    return row;
}


inline CompareResult RunCompare(size_t n, int order) {
    DynamicArray<int> keys;
    for(size_t i=0; i<n; ++i) { keys.Add(static_cast<int>(i)); }

    std::mt19937 gen(42);
    if(order==1) {   
        for(size_t i=0; i<n/2; ++i) {
            int tmp = keys[i];
            keys[i] = keys[n-1-i];
            keys[n-1-i] = tmp;
        }
    }
    if(order==2) {  
        for(size_t i=n-1; i>0; --i) {
            size_t j = gen() % (i+1);
            int tmp = keys[i];
            keys[i] = keys[j];
            keys[j] = tmp;
        }
    }

    DynamicArray<int> queries;  
    for(int i=0; i<1000; ++i) { queries.Add(static_cast<int>(gen() % n)); }

    LinearList linear;
    TreeDictionary<int, int> tree;
    HashTable<int, int> table(CompareHash, n);

    CompareResult result;
    result.linear = Measure(linear, keys, queries);
    result.tree = Measure(tree, keys, queries);
    result.hash = Measure(table, keys, queries);
    return result;
}