#pragma once
#include "IDictionary.hpp" 
#include "DynamicArray.hpp"
#include <stdexcept>
#include <cstddef>


template <typename TKey, typename TElement>
class Node {
public:
    TKey key;
    TElement value;
    Node<TKey, TElement>* left;
    Node<TKey, TElement>* right;

    Node(TKey k, TElement val) : key(k), value(val), left(nullptr), right(nullptr) {} 
};


template <typename TKey, typename TElement>
class TreeDictionary : public IDictionary<TKey, TElement> {
private:
    Node<TKey, TElement>* root;

    void ClearRec(Node<TKey, TElement>* node) {
        if(node==nullptr) { return; }
        ClearRec(node->left);
        ClearRec(node->right);
        delete node;
    }

    Node<TKey, TElement>* AddRec(Node<TKey, TElement>* node, TKey key, TElement element) {
        if(node == nullptr) { return new Node<TKey, TElement>(key, element); }
        if(key < node->key) { node->left = AddRec(node->left, key, element); }
        else if(key > node->key) { node->right = AddRec(node->right, key, element); }

        else { node->value = element; }
        return node;
    }

    Node<TKey, TElement>* RemoveRec(Node<TKey, TElement>* node, TKey key) {
        if(node==nullptr) { return nullptr; }
        if(key<node->key) { node->left = RemoveRec(node->left, key); }
        else if(key>node->key) { node->right = RemoveRec(node->right, key); }

        else { 
            if(node->left==nullptr) {
                Node<TKey, TElement>* temp = node->right;
                delete node;
                return temp;
            }
            else if(node->right==nullptr) {
                Node<TKey, TElement>* temp = node->left;
                delete node;
                return temp;
            }
            Node<TKey, TElement>* replacement = GetMinNode(node->right);
            node->key = replacement->key; 
            node->value = replacement->value;

            node->right = RemoveRec(node->right, replacement->key);
        }
        return node;
    }

    Node<TKey, TElement>* GetMinNode(Node<TKey, TElement>* node) {
        if(node==nullptr) { return nullptr; }
        while(node->left!=nullptr) {
            node = node->left;
        }
        return node;
    }

    bool ContainsRec(Node<TKey, TElement>* node, TKey key) {
        if(node==nullptr) { return false; }
        if(key<node->key) { return ContainsRec(node->left, key); }
        else if(key>node->key) { return ContainsRec(node->right, key); }
        else { return true; }
    }
    size_t GetCountRec(Node<TKey, TElement>* node) {
        if(node==nullptr) { return 0; }
        size_t leftCount = GetCountRec(node->left);
        size_t rightCount = GetCountRec(node->right);
        return leftCount + rightCount + 1;
    }
    TElement GetRec(Node<TKey, TElement>* node, TKey key) {
        if(node==nullptr) { throw std::out_of_range("Key is not found in the dictionary"); }
        if(key<node->key) { return GetRec(node->left, key); }
        else if(key>node->key) { return GetRec(node->right, key); }
        else { return node->value; }
    }
    Node<TKey, TElement>* FindNodeRec(Node<TKey, TElement>* node, TKey key) {
        if(node==nullptr) { return nullptr; }
        if(key<node->key) { return FindNodeRec(node->left, key); }
        else if(key>node->key) { return FindNodeRec(node->right, key); }
        else { return node; }
    }


    void RangeSearchRec(Node<TKey, TElement>* node, TKey from, TKey to, DynamicArray<TElement>& result) {
       if(node==nullptr) { return; }

       if(node->key>from) { RangeSearchRec(node->left, from, to, result); }
       if(node->key>=from && node->key<=to) { result.Add(node->value); }
       if(node->key<to) { RangeSearchRec(node->right, from, to, result); }
    } 


public:
    TreeDictionary() : root(nullptr) {}
    ~TreeDictionary() override { ClearRec(root); }

    void Add(TKey key, TElement element) override {
        root = AddRec(root, key, element);
    }
    void Remove(TKey key) override {
        root = RemoveRec(root, key);
    }

    bool ContainsKey(TKey key) override {
        return ContainsRec(root, key);
    }
    size_t GetCount() override {
        return GetCountRec(root);
    } 
    TElement Get(TKey key) override {
        return GetRec(root, key);
    }
    TElement* Find(TKey key) {
        Node<TKey, TElement>* node = FindNodeRec(root, key);
        if(node==nullptr) { return nullptr; }
        else { return &node->value; }
    }

    
    DynamicArray<TElement> RangeSearch(TKey from, TKey to) {
        DynamicArray<TElement> result;
        RangeSearchRec(root, from, to, result);
        return result;
    }
};