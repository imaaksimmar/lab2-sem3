#include <gtest/gtest.h>
#include "../include/TreeDictionary.hpp"
#include <stdexcept>
#include <string>


TEST(TreeDictionary, EmptyDictionary) {
    TreeDictionary<int, int> dict;
    EXPECT_EQ(dict.GetCount(), 0u);
    EXPECT_FALSE(dict.ContainsKey(1));
    EXPECT_THROW(dict.Get(1), std::out_of_range);
}

TEST(TreeDictionary, AddAndGet) {
    TreeDictionary<int, std::string> dict;
    dict.Add(50, "a");
    dict.Add(30, "b");  
    dict.Add(70, "c");  

    EXPECT_EQ(dict.GetCount(), 3u);
    EXPECT_EQ(dict.Get(50), "a");
    EXPECT_EQ(dict.Get(30), "b");
    EXPECT_EQ(dict.Get(70), "c");
}

TEST(TreeDictionary, MissingKey) {
    TreeDictionary<int, int> dict;
    dict.Add(1, 10);
    EXPECT_FALSE(dict.ContainsKey(2));
    EXPECT_THROW(dict.Get(2), std::out_of_range);
}

TEST(TreeDictionary, RemoveLeaf) {
    TreeDictionary<int, int> dict;
    dict.Add(50, 50);
    dict.Add(30, 30);
    dict.Add(70, 70);

    dict.Remove(30); 
    EXPECT_FALSE(dict.ContainsKey(30));
    EXPECT_EQ(dict.GetCount(), 2u);
}

TEST(TreeDictionary, RemoveNodeWithOneChild) {
    TreeDictionary<int, int> dict;

    dict.Add(50, 50);
    dict.Add(30, 30);
    dict.Add(20, 20);

    dict.Remove(30); 

    EXPECT_FALSE(dict.ContainsKey(30));
    EXPECT_TRUE(dict.ContainsKey(20));
}

TEST(TreeDictionary, RemoveNodeWithTwoChildren) {
    TreeDictionary<int, int> d;
    d.Add(50, 50);
    d.Add(30, 30);
    d.Add(70, 70);
    d.Add(60, 60);
    d.Add(80, 80);

    d.Remove(70); 

    EXPECT_FALSE(d.ContainsKey(70));
    EXPECT_TRUE(d.ContainsKey(60));
    EXPECT_TRUE(d.ContainsKey(80));
    EXPECT_EQ(d.GetCount(), 4u);
}

TEST(TreeDictionary, RemoveRoot) {
    TreeDictionary<int, int> d;
 
    d.Add(50, 50);
    d.Add(30, 30);
    d.Add(70, 70);

    d.Remove(50);  

    EXPECT_FALSE(d.ContainsKey(50));
    EXPECT_TRUE(d.ContainsKey(30));
    EXPECT_TRUE(d.ContainsKey(70));
}

TEST(TreeDictionary, RemoveMissingKey) {
    TreeDictionary<int, int> dict;
    dict.Add(1, 10);
    dict.Remove(999);
    EXPECT_EQ(dict.GetCount(), 1u);
}

TEST(TreeDictionary, StringKeys) {
    TreeDictionary<std::string, int> dict;
    dict.Add("sixseven", 2);
    dict.Add("pupupu", 1);
    EXPECT_EQ(dict.Get("pupupu"), 1);
    EXPECT_FALSE(dict.ContainsKey("cherry"));
}

TEST(TreeDictionary, DuplicateKeyOverwrites) {
    TreeDictionary<int, int> dict;
    dict.Add(1, 10);
    dict.Add(1, 99);

    EXPECT_EQ(dict.GetCount(), 1u);   
    EXPECT_EQ(dict.Get(1), 99);       
}