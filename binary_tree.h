#ifndef PERSISTENT_BINARY_TREE_H
#define PERSISTENT_BINARY_TREE_H

#include <iostream>
#include <optional>
#include <memory>

namespace Persistent {

template<class T>
class BinaryTree {

  struct Data {
    Data(T val, std::shared_ptr<Data> left, std::shared_ptr<Data> right)
      : val_(val)
      , left_(left)
      , right_(right)
    {}

    const T val_;
    std::shared_ptr<Data> left_;
    std::shared_ptr<Data> right_;
  };


  std::shared_ptr<BinaryTree::Data> data_;

  explicit BinaryTree(std::shared_ptr<BinaryTree::Data> data)
    : data_(data) {}


public:

  BinaryTree();
  BinaryTree(const T& val);
  BinaryTree(const T& val,
             const BinaryTree& left,
             const BinaryTree& right);

  bool isEmpty() {
    return !data_.get();
  }

  const T& root() const;
  BinaryTree<T> left() const;
  BinaryTree<T> right() const;

};

template<class T>
BinaryTree<T>::BinaryTree()
  : data_(nullptr)
{}

template<class T>
BinaryTree<T>::BinaryTree(const T& val)
  : data_(std::make_shared<BinaryTree<T>::Data>(val, nullptr, nullptr))
{}

template<class T>
BinaryTree<T>::BinaryTree(const T& val,
    const BinaryTree<T>& left,
    const BinaryTree<T>& right)
  : data_(std::make_shared<BinaryTree<T>::Data>(val, left.data_, right.data_))
{}

template<class T>
const T& BinaryTree<T>::root() const {
  if (!data_.get()) {
    std::cout << "trying to root an empty tree" << std::endl;
    throw;
  }
  return data_->val_;
}

template<class T>
BinaryTree<T> BinaryTree<T>::left() const {
  if (!data_.get())
    return {}; // throw
  return BinaryTree<T>(data_->left_);
}

template<class T>
BinaryTree<T> BinaryTree<T>::right() const {
  if (!data_.get())
    return {}; // throw
  return BinaryTree<T>(data_->right_);
}

}

#endif
