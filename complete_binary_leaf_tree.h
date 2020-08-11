#ifndef PERSISTENT_COMPLETE_BINARY_LEAF_TREE_H
#define PERSISTENT_COMPLETE_BINARY_LEAF_TREE_H

#include <memory>

namespace Persistent {

template<class T>
class CompleteBinaryLeafTree {

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


  std::shared_ptr<CompleteBinaryLeafTree::Data> data_;

  explicit CompleteBinaryLeafTree(std::shared_ptr<CompleteBinaryLeafTree::Data> data)
    : data_(data) {}


public:

  CompleteBinaryLeafTree();
  CompleteBinaryLeafTree(T val,
                         const CompleteBinaryLeafTree& left,
                         const CompleteBinaryLeafTree& right);

  bool isEmpty() {
    return !data_.get();
  }

  CompleteBinaryLeafTree<T> left();
  CompleteBinaryLeafTree<T> right();

};

template<class T>
CompleteBinaryLeafTree<T>::CompleteBinaryLeafTree()
  : data_(nullptr)
{}

template<class T>
CompleteBinaryLeafTree<T>::CompleteBinaryLeafTree(T val,
    const CompleteBinaryLeafTree<T>& left,
    const CompleteBinaryLeafTree<T>& right)
  : data_(std::make_shared<CompleteBinaryLeafTree<T>::Data>(val, left.data_, right.data_))
{}

template<class T>
CompleteBinaryLeafTree<T> CompleteBinaryLeafTree<T>::left() {
  return CompleteBinaryLeafTree<T>(data_->left_);
}

template<class T>
CompleteBinaryLeafTree<T> CompleteBinaryLeafTree<T>::right() {
  return CompleteBinaryLeafTree<T>(data_->right_);
}

}

#endif
