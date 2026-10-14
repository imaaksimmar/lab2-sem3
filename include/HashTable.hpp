#pragma once
#include <stdexcept>
#include "IDictionary.hpp"
#include "DynamicArray.hpp"

template <typename TKey, typename TElement>
class Pair
{
public:
    TKey key;
    TElement value;

    Pair() : key(), value() {} 
    Pair(TKey k, TElement val) : key(k), value(val) {}
}; 


template <typename TKey, typename TElement>
class HashTable : public IDictionary<TKey, TElement>
{
private:
    DynamicArray<DynamicArray<Pair<TKey, TElement>>> data;
    size_t count;
    size_t capacity;
    size_t (*hashFunc)(TKey);

    size_t GetIndex(TKey key) { return hashFunc(key) % capacity; }

public:
    HashTable(size_t (*hashFunc)(TKey), size_t initialCapacity) : 
    data(initialCapacity), count(0), capacity(initialCapacity), hashFunc(hashFunc) {
        if(initialCapacity==0) {
             throw std::invalid_argument("Capacity must be >0"); 
        }
    }

    void Add(TKey key, TElement element) override {
        size_t index = GetIndex(key);
        DynamicArray<Pair<TKey, TElement>>& bucket = data[index];
        for(size_t i=0; i<bucket.GetSize(); ++i) {
            if(bucket[i].key==key) {
                bucket[i].value = element;
                return;
            }
        }
        bucket.Add(Pair<TKey, TElement>(key, element));
        ++count;
    }
    void Remove(TKey key) override {
         size_t index = GetIndex(key);
         DynamicArray<Pair<TKey, TElement>>& bucket = data[index];
         for(size_t i=0; i<bucket.GetSize(); ++i) {
            if(bucket[i].key==key) {
                bucket[i] = bucket[bucket.GetSize()-1];
                bucket.Resize(bucket.GetSize()-1);
                --count;
                return;
            }
         }
         throw std::out_of_range("Key is not found in the dictionary");
    }
    bool ContainsKey(TKey key) override {
        size_t index = GetIndex(key);
        DynamicArray<Pair<TKey, TElement>>& bucket = data[index];
        for(size_t i=0; i<bucket.GetSize(); ++i) {
            if(bucket[i].key==key) { return true; }
        }
        return false;
    }
    TElement Get(TKey key) override {
        size_t index = GetIndex(key);
        DynamicArray<Pair<TKey, TElement>>& bucket = data[index];
        for(size_t i=0; i<bucket.GetSize(); ++i) {
            if(bucket[i].key==key) { return bucket[i].value; }
        }
        throw std::out_of_range("Key is not found in the dictionary");
    }

    size_t GetCount() override { return count; }
    size_t GetCapacity() const { return capacity; }

};