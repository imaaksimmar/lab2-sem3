#pragma once 
#include <string>
#include <cstddef>

class CompositeKey {
public:
    std::string firstName;
    std::string lastName;
    size_t birthYear;

    CompositeKey(std::string fName, std::string lName, size_t bYear) 
    : firstName(fName), lastName(lName), birthYear(bYear) {}

    bool operator<(const CompositeKey& other) const {
        if(this->lastName!=other.lastName) {
            return this->lastName < other.lastName;
        }
        if(this->firstName!=other.firstName) {
            return this->firstName < other.firstName;
        }
        return birthYear < other.birthYear;
    }

    bool operator>(const CompositeKey& other) const {
        if(this->lastName!=other.lastName) {
            return this->lastName > other.lastName;
        }
        if(this->firstName!=other.firstName) {
            return this->firstName > other.firstName;
        }
        return birthYear > other.birthYear;
    }

};
