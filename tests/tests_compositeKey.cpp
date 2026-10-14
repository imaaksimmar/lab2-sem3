#include <gtest/gtest.h>
#include "../include/CompositeKey.hpp"

TEST(CompositeKey, LastNameWhenDifferent) {
    CompositeKey a("Ivan", "Ivanov", 2000);
    CompositeKey b("Petr", "Petrov", 2000);

    EXPECT_TRUE(a<b);
    EXPECT_FALSE(b<a);
}

TEST(CompositeKey, FirstName) {
    CompositeKey a("Anna", "Ivanov", 2000);
    CompositeKey b("Boris", "Ivanov", 2000);

    EXPECT_TRUE(a<b);
    EXPECT_FALSE(b<a);
}

TEST(CompositeKey, Year) {
    CompositeKey a("Ivan", "Ivanov", 1999);
    CompositeKey b("Ivan", "Ivanov", 2000);

    EXPECT_TRUE(a<b);
    EXPECT_FALSE(b<a);
}

TEST(CompositeKey, GreaterByLastNameWhenDifferent) {
    CompositeKey a("Ivan", "Petrov", 2000);
    CompositeKey b("Ivan", "Ivanov", 2000);

    EXPECT_TRUE(a>b);
    EXPECT_FALSE(b>a);
}

TEST(CompositeKey, GreaterByFirstNameWhenLastNameEqual) {
    CompositeKey a("Boris", "Ivanov", 2000);
    CompositeKey b("Anna", "Ivanov", 2000);

    EXPECT_TRUE(a>b);
    EXPECT_FALSE(b>a);
}

TEST(CompositeKey, GreaterByYear) {
    CompositeKey a("Ivan", "Ivanov", 2001);
    CompositeKey b("Ivan", "Ivanov", 2000);

    EXPECT_TRUE(a>b);
    EXPECT_FALSE(b>a);
}

TEST(CompositeKey, EqualKeysAreNeitherLessNorGreater) {
    CompositeKey a("Ivan", "Ivanov", 2000);
    CompositeKey b("Ivan", "Ivanov", 2000);

    EXPECT_FALSE(a<b);
    EXPECT_FALSE(a>b);
}