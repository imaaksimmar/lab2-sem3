#include <gtest/gtest.h>
#include <stdexcept>
#include <utility>
#include "../include/DynamicArray.hpp"

TEST(DynamicArray, DefaultConstructorIsEmpty) {
    DynamicArray<int> a;
    EXPECT_EQ(a.GetSize(), 0u);
}

TEST(DynamicArray, SizeConstructorDefaultValues) {
    DynamicArray<int> a(5);
    EXPECT_EQ(a.GetSize(), 5u);
    for(size_t i= 0;i<5; ++i) { EXPECT_EQ(a[i], 0); }
}

TEST(DynamicArray, AddIncreasesSize) {
    DynamicArray<int> a;
    a.Add(10);
    a.Add(20);
    a.Add(30);

    EXPECT_EQ(a.GetSize(), 3u);
    EXPECT_EQ(a[0], 10);
    EXPECT_EQ(a[1], 20);
    EXPECT_EQ(a[2], 30);
}

TEST(DynamicArray, IndexOutOfRangeThrows) {
    DynamicArray<int> a;
    a.Add(1);

    EXPECT_THROW(a[1], std::out_of_range);
    EXPECT_THROW(a[100], std::out_of_range);
}

TEST(DynamicArray, CopyConstructorIsIndependent) {
    DynamicArray<int> a;
    a.Add(1);
    a.Add(2);

    DynamicArray<int> copy(a);
    a.Add(3); 

    EXPECT_EQ(copy.GetSize(), 2u);
    EXPECT_EQ(copy[0], 1);
    EXPECT_EQ(copy[1], 2);
}

TEST(DynamicArray, CopyAssignmentIsIndependent) {
    DynamicArray<int> a;
    a.Add(1);
    a.Add(2);

    DynamicArray<int> b;
    b.Add(100);
    b = a;

    a.Add(3);  
    EXPECT_EQ(b.GetSize(), 2u);
    EXPECT_EQ(b[0], 1);
    EXPECT_EQ(b[1], 2);
}

TEST(DynamicArray, SelfAssignmentIsSafe) {
    DynamicArray<int> a;
    a.Add(1);
    a.Add(2);

    a = a;

    EXPECT_EQ(a.GetSize(), 2u);
    EXPECT_EQ(a[0], 1);
    EXPECT_EQ(a[1], 2);
}

TEST(DynamicArray, MoveConstructorTransfersData) {
    DynamicArray<int> a;
    a.Add(1);
    a.Add(2);

    DynamicArray<int> moved(std::move(a));

    EXPECT_EQ(moved.GetSize(), 2u);
    EXPECT_EQ(moved[0], 1);
    EXPECT_EQ(moved[1], 2);
    EXPECT_EQ(a.GetSize(), 0u);
}

TEST(DynamicArray, MoveAssignmentTransfersData) {
    DynamicArray<int> a;
    a.Add(1);
    a.Add(2);

    DynamicArray<int> b;
    b = std::move(a);

    EXPECT_EQ(b.GetSize(), 2u);
    EXPECT_EQ(b[0], 1);
    EXPECT_EQ(b[1], 2);
    EXPECT_EQ(a.GetSize(), 0u);
}

TEST(DynamicArray, Resize) {
    DynamicArray<int> a;
    a.Add(1);
    a.Add(2);
    a.Add(3);

    a.Resize(1);

    EXPECT_EQ(a.GetSize(), 1u);
    EXPECT_EQ(a[0], 1);
}