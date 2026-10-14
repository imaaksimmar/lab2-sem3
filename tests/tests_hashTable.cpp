#include <gtest/gtest.h>
#include <stdexcept>
#include <string>
#include <functional>
#include "../include/HashTable.hpp"

size_t HashInt(int key) { return key; }
size_t HashString(std::string key) { return (int)std::hash<std::string>{}(key); }

TEST(HashTable, EmptyTable) {
    HashTable<int, int> table(HashInt, 5);

    EXPECT_EQ(table.GetCount(), 0u);
    EXPECT_FALSE(table.ContainsKey(1));
    EXPECT_THROW(table.Get(1), std::out_of_range);
}

TEST(HashTable, CapacityIsStored) {
    HashTable<int, int> table(HashInt, 7);

    EXPECT_EQ(table.GetCapacity(), 7u);
}

TEST(HashTable, ZeroCapacityThrows) {
    EXPECT_THROW((HashTable<int, int>(HashInt, 0)), std::invalid_argument);
}

TEST(HashTable, AddAndGet) {
    HashTable<int, int> table(HashInt, 5);
    table.Add(1, 10);
    table.Add(2, 20);
    table.Add(3, 30);

    EXPECT_EQ(table.GetCount(), 3u);
    EXPECT_EQ(table.Get(1), 10);
    EXPECT_EQ(table.Get(2), 20);
    EXPECT_EQ(table.Get(3), 30);
}

TEST(HashTable, ContainsKey) {
    HashTable<int, int> table(HashInt, 5);
    table.Add(1, 10);

    EXPECT_TRUE(table.ContainsKey(1));
    EXPECT_FALSE(table.ContainsKey(2));
}

TEST(HashTable, MissingKeyThrows) {
    HashTable<int, int> table(HashInt, 5);
    table.Add(1, 10);

    EXPECT_THROW(table.Get(2), std::out_of_range);
}

TEST(HashTable, DuplicateKeyOverwrites) {
    HashTable<int, int> table(HashInt, 5);
    table.Add(1, 10);
    table.Add(1, 99);

    EXPECT_EQ(table.GetCount(), 1u);
    EXPECT_EQ(table.Get(1), 99);
}

TEST(HashTable, Remove) {
    HashTable<int, int> table(HashInt, 5);
    table.Add(1, 10);
    table.Add(2, 20);

    table.Remove(1);

    EXPECT_FALSE(table.ContainsKey(1));
    EXPECT_TRUE(table.ContainsKey(2));
    EXPECT_EQ(table.GetCount(), 1u);
}

TEST(HashTable, Collisions) {
    HashTable<int, int> table(HashInt, 5);
    table.Add(1, 10);
    table.Add(6, 60);
    table.Add(11, 110);

    EXPECT_EQ(table.GetCount(), 3u);
    EXPECT_EQ(table.Get(1), 10);
    EXPECT_EQ(table.Get(6), 60);
    EXPECT_EQ(table.Get(11), 110);
}

TEST(HashTable, RemoveFromCollisionChain) {
    HashTable<int, int> table(HashInt, 5);
    table.Add(1, 10);
    table.Add(6, 60);
    table.Add(11, 110);

    table.Remove(6);

    EXPECT_FALSE(table.ContainsKey(6));
    EXPECT_EQ(table.Get(1), 10);
    EXPECT_EQ(table.Get(11), 110);
    EXPECT_EQ(table.GetCount(), 2u);
}

TEST(HashTable, StringKeys) {
    HashTable<std::string, int> table(HashString, 5);
    table.Add("Ivanov", 1);
    table.Add("Petrov", 2);

    EXPECT_EQ(table.Get("Ivanov"), 1);
    EXPECT_EQ(table.Get("Petrov"), 2);
    EXPECT_FALSE(table.ContainsKey("Sidorov"));
}