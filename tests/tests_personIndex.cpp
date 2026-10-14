#include <gtest/gtest.h>
#include "../include/PersonIndex.hpp"

TEST(PersonIndex, EmptyIndex) {
    PersonIndex index;
    EXPECT_EQ(index.GetCount(), 0u);
}

TEST(PersonIndex, AddPerson) {
    PersonIndex index;
    index.AddPerson("Ivan", "Ivanov", 2000);

    EXPECT_EQ(index.GetCount(), 1u);
}


TEST(PersonIndex, FindByLastName) {
    PersonIndex index;
    index.AddPerson("Ivan", "Ivanov", 2000);

    DynamicArray<Person*> found = index.FindByLastName("Ivanov");
    
    EXPECT_EQ(found.GetSize(), 1u); 
    EXPECT_EQ(found[0]->GetFirstName(), "Ivan");
    EXPECT_EQ(found[0]->GetLastName(), "Ivanov");
    EXPECT_EQ(found[0]->GetBirthYear(), 2000u);
}


TEST(PersonIndex, FindByLastNameMissingReturnsEmpty) {
    PersonIndex index;
    index.AddPerson("Ivan", "Ivanov", 2000);

    DynamicArray<Person*> found = index.FindByLastName("Petrov");
    EXPECT_EQ(found.GetSize(), 0u);
}


TEST(PersonIndex, FindByBirthYearReturnsCorrectPerson) {
    PersonIndex index;
    index.AddPerson("Ivan", "Ivanov", 2000);

    DynamicArray<Person*> found = index.FindByBirthYear(2000);
    
    EXPECT_EQ(found.GetSize(), 1u);
    EXPECT_EQ(found[0]->GetLastName(), "Ivanov");
}

TEST(PersonIndex, FindByBirthYearMissingReturnsEmpty) {
    PersonIndex index;
    index.AddPerson("Ivan", "Ivanov", 2000);

    DynamicArray<Person*> found = index.FindByBirthYear(1990);
    EXPECT_EQ(found.GetSize(), 0u);
}


TEST(PersonIndex, FindByCompositeKeyReturnsCorrectPerson) {
    PersonIndex index;
    index.AddPerson("Ivan", "Ivanov", 2000);

    Person* found = index.FindByCompositeKey("Ivan", "Ivanov", 2000);
    EXPECT_NE(found, nullptr); 
    EXPECT_EQ(found->GetFirstName(), "Ivan");
}

TEST(PersonIndex, FindByCompositeKeyMissingReturnsNullptr) {
    PersonIndex index;
    index.AddPerson("Ivan", "Ivanov", 2000);

    EXPECT_EQ(index.FindByCompositeKey("Petr", "Petrov", 1999), nullptr);
}


TEST(PersonIndex, AddingSeveralDifferentPersonsKeepsCount) {
    PersonIndex index;
    index.AddPerson("Ivan", "Ivanov", 2000);
    index.AddPerson("Petr", "Petrov", 1999);
    index.AddPerson("Anna", "Sidorova", 2001);

    EXPECT_EQ(index.GetCount(), 3u);
    
    EXPECT_EQ(index.FindByLastName("Ivanov").GetSize(), 1u);
    EXPECT_EQ(index.FindByLastName("Petrov").GetSize(), 1u);
    EXPECT_EQ(index.FindByLastName("Sidorova").GetSize(), 1u);
}

TEST(PersonIndex, FindPeopleInYearRange) {
    PersonIndex index;
  
    index.AddPerson("Ivan", "Ivanov", 2000);
    index.AddPerson("Petr", "Petrov", 2002);
    index.AddPerson("Anna", "Sidorova", 2005);

    DynamicArray<Person*> found = index.FindPeopleInYearRange(2000, 2003);
    EXPECT_EQ(found.GetSize(), 2u); 
}