#ifndef PERSISTENT_STANDALONE_COMPLETE_BINARY_TREE_H
#define PERSISTENT_STANDALONE_COMPLETE_BINARY_TREE_H

#include <optional>
#include <memory>

namespace Persistent {

template <class T>
std::optional<CompleteSABinaryTree>
CreateCompleteSABinaryTree(const T& val, const CompleteSABinaryTree& left, const CompleteSABinaryTree& right) {


}

template<class T>
class CompleteSABinaryTree {

  struct Data {
    Data(T val, std::shared_ptr<Data> left, std::shared_ptr<Data> right)
      : val_(val)
      , left_(left)
      , right_(right)
      , rank_(left->rank_ + 1)
    {}

    const T val_;
    std::shared_ptr<Data> left_;
    std::shared_ptr<Data> right_;
    unsigned rank_;
  };

  explicit CompleteSABinaryTree(std::shared_ptr<CompleteSABinaryTree::Data> data)
    : data_(data) {}

  CompleteSABinaryTree(T val,
                     const CompleteSABinaryTree& left,
                     const CompleteSABinaryTree& right);

public: // interface

  CompleteSABinaryTree();

  bool isEmpty() {
    return !data_.get();
  }

  static
  std::optional<CompleteSABinaryTree>
  CreateCompleteSABinaryTree(const T& val, const CompleteSABinaryTree& left, const CompleteSABinaryTree& right);

  CompleteSABinaryTree<T> left();
  CompleteSABinaryTree<T> right();

  unsigned rank();

private: // data

  std::shared_ptr<CompleteSABinaryTree::Data> data_;

};


template<class T>
CompleteSABinaryTree<T>::CompleteSABinaryTree()
  : data_(nullptr)
{}

template<class T>
CompleteSABinaryTree<T>::CompleteSABinaryTree(T val,
    const CompleteSABinaryTree<T>& left,
    const CompleteSABinaryTree<T>& right)
  : data_(std::make_shared<CompleteSABinaryTree<T>::Data>(val, left.data_, right.data_))
{}

template<class T>
std::optional<CompleteSABinaryTree> 
CompleteSABinaryTree<T>::CreateCompleteSABinaryTree(const T& val,
                                                const CompleteSABinaryTree& left,
                                                const CompleteSABinaryTree& right)
{
  if (left.rank() == right.rank())
    return CompleteSABinaryTree<T>(val, left, right);
  return {};
}

template<class T>
CompleteSABinaryTree<T> CompleteSABinaryTree<T>::left() {
  return CompleteSABinaryTree<T>(data_->left_);
}

template<class T>
CompleteSABinaryTree<T> CompleteSABinaryTree<T>::right() {
  return CompleteSABinaryTree<T>(data_->right_);
}

template<class T>
unsigned CompleteSABinaryTree<T>::rank() {
  return !data_.get() ? 0 : data->rank_;
}

#endif
