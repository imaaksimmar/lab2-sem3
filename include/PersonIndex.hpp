#pragma once
#include <string>
#include <stdexcept>
#include "TreeDictionary.hpp"
#include "Person.hpp"
#include "DynamicArray.hpp"
#include "CompositeKey.hpp"


class PersonIndex {
private:
    DynamicArray<Person> people;

    TreeDictionary<std::string, DynamicArray<size_t>> lastNameIndex;
    TreeDictionary<size_t, DynamicArray<size_t>> birthYearIndex;
    TreeDictionary<CompositeKey, size_t> compositeIndex;
    
    template <typename TKey>
    void AddToIndex(TreeDictionary<TKey, DynamicArray<size_t>>& indexTree, TKey key, size_t position) {
        DynamicArray<size_t>* list = indexTree.Find(key);
        if(list==nullptr) {
            DynamicArray<size_t> newList;
            newList.Add(position);
            indexTree.Add(key, newList);
        }
        else { list->Add(position); }
    }

public:
    PersonIndex() : people(), lastNameIndex(), birthYearIndex(), compositeIndex() {}

    void AddPerson(const std::string& fName, const std::string& lName, size_t year) {
        people.Add(Person(fName, lName, year));
        size_t index = people.GetSize()-1;

        AddToIndex(lastNameIndex, lName, index);
        AddToIndex(birthYearIndex, year, index);

        CompositeKey cKey(fName, lName, year);
        compositeIndex.Add(cKey, index);
    }

    DynamicArray<Person*> FindByLastName(const std::string lastName) {
       DynamicArray<Person*> result;
       DynamicArray<size_t>* cellNumbers = lastNameIndex.Find(lastName);
       if(cellNumbers!=nullptr) {
            for(size_t i=0; i<cellNumbers->GetSize(); ++i) {
                size_t personIndex = (*cellNumbers)[i];
                Person* person = &people[personIndex];
                result.Add(person);
            }
       }
       return result;
    }

    DynamicArray<Person*> FindByBirthYear(size_t year) {
        DynamicArray<Person*> result;
        DynamicArray<size_t>* cellNumbers = birthYearIndex.Find(year);
        if(cellNumbers!=nullptr) {
            for(size_t i=0; i<cellNumbers->GetSize(); ++i) {
                size_t personIndex = (*cellNumbers)[i];
                Person* person = &people[personIndex];
                result.Add(person);
            }
        }
        return result;  
    }

    Person* FindByCompositeKey(const std::string& fName, const std::string& lName, size_t year) {
        CompositeKey cKey(fName, lName, year);
        size_t* personIndex = compositeIndex.Find(cKey);

        if(personIndex==nullptr) { return nullptr; }
        return &people[*personIndex];
    }

    size_t GetCount() const { return people.GetSize(); }

    

    DynamicArray<Person*> FindPeopleInYearRange(size_t fromYear, size_t toYear) {
        DynamicArray<Person*> result;
        DynamicArray<DynamicArray<size_t>> yearsData = birthYearIndex.RangeSearch(fromYear, toYear);

        for(size_t i=0; i<yearsData.GetSize(); ++i) {
            DynamicArray<size_t> cellNumbers = yearsData[i];
            for(size_t j=0; j<cellNumbers.GetSize(); ++j) {
                size_t personIndex = cellNumbers[j];
                Person* person = &people[personIndex];
                result.Add(person);
            }
        }
        return result;
    }

};