#pragma once
#include <cstddef>
#include <stdexcept>

template <typename T>
class DynamicArray {
private:
    T* data;
    size_t size;

public:
    DynamicArray() : data(nullptr), size(0) {}
    explicit DynamicArray(size_t size) : data(nullptr), size(size) {
        if(size>0) { data = new T[size](); }
    }
    ~DynamicArray() { delete[] data; }

    DynamicArray(const DynamicArray& other) : data(nullptr), size(other.size) {
        if(size>0) { 
            data = new T[size];
            for(size_t i=0; i<size; ++i) {
                data[i] = other.data[i];
            }
        }
    } 
    DynamicArray& operator=(const DynamicArray& other) {
        if(this!=&other) {
            if(other.size==0) {
                delete[] data;
                data = nullptr;
                size = 0;
                return *this;
            }
            T* newData = new T[other.size];
            for(size_t i=0; i<other.size; ++i) {
                newData[i] = other.data[i];
            }
            delete[] data;
            data = newData;
            size = other.size;
        }
        return *this;

    }
    DynamicArray(DynamicArray&& other) noexcept : data(other.data), size(other.size) {
       other.data = nullptr;
       other.size = 0;
    }
    DynamicArray& operator=(DynamicArray&& other) noexcept {
        if(this!=&other) {
            delete[] data;
            data = other.data;
            size = other.size;

            other.data = nullptr;
            other.size = 0;
        }
        return *this;
    }

    void Add(const T& element) {
        T* newData = new T[size+1];
        for(size_t i=0; i<size; ++i) {
            newData[i] = data[i];
        }
        newData[size] = element;
        size = size+1;
        delete[] data;
        data = newData;
    }
    void Resize(size_t newSize) {
        if(size==newSize)  { return; }
        if(newSize==0) {
            delete[] data;
            data = nullptr; 
            size = 0;
            return;
        }
        else if(newSize>size) {
            T* newData = new T[newSize];
            for(size_t i=0; i<size; ++i) {
                newData[i] = data[i];
            }
            for(size_t i=size; i<newSize; ++i) {
                newData[i] = T();
            }
            delete[] data;
            data = newData;
            size = newSize;
        }
        else {
            T* newData = new T[newSize];
            for(size_t i=0; i<newSize; ++i) {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
            size = newSize;
        }
    }
    T& operator[](size_t index) {
        if(index>=size) { throw std::out_of_range("Index out of range"); }
        return data[index]; 
    }
    const T& operator[](size_t index) const {
        if(index>=size) { throw std::out_of_range("Index out of range"); }
        return data[index]; 
    }

    size_t GetSize() const { return size; }
};