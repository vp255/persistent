#ifndef PERSISTENT_COMPLETE_BINARY_TREE_H
#define PERSISTENT_COMPLETE_BINARY_TREE_H

#include <optional>
#include <memory>

#include "persistent/binary_tree.h"

namespace Persistent {

template<class T>
class CompleteBinaryTree {

  explicit CompleteBinaryTree(const BinaryTree<T>&,
                              unsigned);

  CompleteBinaryTree(const T&,
                     const CompleteBinaryTree&,
                     const CompleteBinaryTree&);

public: // interface

  CompleteBinaryTree();
  CompleteBinaryTree(const T&);

  bool isEmpty() const {
    return rank_ == 0;
  }

  static
  std::optional<CompleteBinaryTree>
  CreateCompleteBinaryTree(const T&,
                           const CompleteBinaryTree&,
                           const CompleteBinaryTree&);

  const T& root() const;
  CompleteBinaryTree<T> left() const;
  CompleteBinaryTree<T> right() const;

  unsigned rank() const;

private: // data

  BinaryTree<T> tree_;
  unsigned rank_;

};

template <class T>
CompleteBinaryTree<T>::CompleteBinaryTree(const BinaryTree<T>& tree, unsigned rank)
  : tree_(tree)
  , rank_(rank) {}

template<class T>
CompleteBinaryTree<T>::CompleteBinaryTree()
  : tree_()
  , rank_(0)
{}

template<class T>
CompleteBinaryTree<T>::CompleteBinaryTree(const T& val)
  : tree_(val)
  , rank_(1)
{}

template<class T>
CompleteBinaryTree<T>::CompleteBinaryTree(const T& val,
    const CompleteBinaryTree<T>& left,
    const CompleteBinaryTree<T>& right)
  : tree_(val, left.tree_, right.tree_)
  , rank_(left.rank() + 1)
{}

template<class T>
std::optional<CompleteBinaryTree<T>> 
CompleteBinaryTree<T>::CreateCompleteBinaryTree(const T& val,
                                                const CompleteBinaryTree& left,
                                                const CompleteBinaryTree& right)
{
  if (left.rank() == right.rank())
    return CompleteBinaryTree<T>(val, left, right);
  return {};
}

template<class T>
CompleteBinaryTree<T>
CompleteBinaryTree<T>::left() const {
  if (rank_ == 0)
    return {}; // throw
  return CompleteBinaryTree<T>(tree_.left(), rank_ - 1);
}

template<class T>
const T&
CompleteBinaryTree<T>::root() const {
  return tree_.root();
}

template<class T>
CompleteBinaryTree<T>
CompleteBinaryTree<T>::right() const {
  if (rank_ == 0)
    return {}; // throw
  return CompleteBinaryTree<T>(tree_.right(), rank_ - 1);
}

template<class T>
unsigned CompleteBinaryTree<T>::rank() const {
  return rank_;
}



}

#endif
