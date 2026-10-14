#include <iostream>
#include <string>
#include <chrono> 
#include <functional>
#include "Person.hpp"
#include "DynamicArray.hpp"
#include "TreeDictionary.hpp"
#include "HashTable.hpp"


size_t SimpleHashString(std::string key) {
    return std::hash<std::string>{}(key);
}

class Benchmark 
{
public:
    static Person* LinearSearch(DynamicArray<Person>& arr, const std::string& targetName) {
        for(size_t i=0; i<arr.GetSize(); ++i) {
            if(arr[i].GetLastName()==targetName) {
                return &arr[i];
            }
        }
        return nullptr;
    }

    static void Run(size_t n) {
        std::cout << "Замер времени для " << n << " элементов \n";

        DynamicArray<Person> array;
        TreeDictionary<std::string, size_t> tree;
        HashTable<std::string, size_t> hash(SimpleHashString, n);

        std::string targetKey = "";

        for(size_t i=0; i<n; ++i) {
            std::string name = "Person_" + std::to_string(i);
            Person p("Ivan", name, 2000);
            
            array.Add(p);
            tree.Add(name, i);
            hash.Add(name, i);

            if(i==n/2) { targetKey = name; }
        }

        auto start1 = std::chrono::high_resolution_clock::now(); 
        LinearSearch(array, targetKey);                          
        auto end1 = std::chrono::high_resolution_clock::now();  
        auto timeArray = std::chrono::duration_cast<std::chrono::microseconds>(end1 - start1).count();

    
        auto start2 = std::chrono::high_resolution_clock::now();
        tree.Get(targetKey);
        auto end2 = std::chrono::high_resolution_clock::now();
        auto timeTree = std::chrono::duration_cast<std::chrono::microseconds>(end2 - start2).count();


        auto start3 = std::chrono::high_resolution_clock::now();
        hash.Get(targetKey);
        auto end3 = std::chrono::high_resolution_clock::now();
        auto timeHash = std::chrono::duration_cast<std::chrono::microseconds>(end3 - start3).count();

       
        std::cout << "Массив          : " << timeArray << " мкс \n";
        std::cout << "Бинарное дерево : " << timeTree << " мкс \n";
        std::cout << "Хеш-таблица     : " << timeHash << " мкс \n\n";
    }
};

int main() {
    Benchmark::Run(10000);
    Benchmark::Run(15000);
    Benchmark::Run(20000);
}