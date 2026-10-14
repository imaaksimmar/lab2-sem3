#pragma once
#include <string>
#include <cstddef>

class Person {
private:
    std::string firstName;
    std::string lastName;
    size_t birthYear;

public:
    Person() : firstName(""), lastName(""), birthYear(0) {}
    Person(std::string fName, std::string lName, size_t year) :
    firstName(fName), lastName(lName), birthYear(year) {}

    std::string GetFirstName() const { return firstName; }
    std::string GetLastName() const { return lastName; }
    std::string GetFullName() const { return lastName + " " + firstName; }

    size_t GetBirthYear() const { return birthYear; }
    size_t GetAge(size_t year) const { return year-birthYear; }
};