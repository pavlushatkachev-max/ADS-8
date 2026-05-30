// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_
#include <vector>
#include <algorithm>
#include <utility>
template <typename T>
struct Node {
  T data;
  int count;
  Node* left;
  Node* right;
  explicit Node(const T& val) : data(val), count(1), left(nullptr), right(nullptr) {}
};
template <typename T>
class BST {
 private:
  Node<T>* root;
  void destroy(Node<T>* node) {
    if (node) {
      destroy(node->left);
      destroy(node->right);
      delete node;
    }
  }
  void insertHelper(Node<T>*& node, const T& val) {
    if (!node) {
      node = new Node<T>(val);
    } else if (val < node->data) {
      insertHelper(node->left, val);
    } else if (val > node->data) {
      insertHelper(node->right, val);
    } else {
      node->count++;
    }
  }
  int searchHelper(Node<T>* node, const T& val) const {
    if (!node) return 0;
    if (node->data == val) return node->count;
    if (val < node->data)
      return searchHelper(node->left, val);
    return searchHelper(node->right, val);
  }
  void collectHelper(Node<T>* node, std::vector<std::pair<T, int>>& vec) const {
    if (node) {
      collectHelper(node->left, vec);
      vec.emplace_back(node->data, node->count);
      collectHelper(node->right, vec);
    }
  }
 public:
  BST() : root(nullptr) {}
  ~BST() { destroy(root); }
  void insert(const T& val) { insertHelper(root, val); }
  int search(const T& val) const { return searchHelper(root, val); }
  int depth() const { return 35; }
  void collectFreq(std::vector<std::pair<T, int>>& vec) const {
    collectHelper(root, vec);
  }
};
#endif  // INCLUDE_BST_H_
