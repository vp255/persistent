#ifndef SKEW_BINARY_RANDOM_ACCESS_LIST_H
#define SKEW_BINARY_RANDOM_ACCESS_LIST_H

#include <utility>
#include <functional>

#include "persistent/random_access_list.h"
#include "persistent/complete_binary_tree.h"
#include "persistent/list.h"

namespace Persistent {

template <class T>
class SkewBinaryRandomAccessList {

public:

typedef std::pair<unsigned, Persistent::CompleteBinaryTree<T>> WeightAndTree;
typedef Persistent::List<WeightAndTree> TreeList;

private:

const T& lookup(unsigned, const TreeList&) const;
const T& lookupTree(unsigned, unsigned, const Persistent::CompleteBinaryTree<T>&) const;
SkewBinaryRandomAccessList(const TreeList&);


static
Persistent::CompleteBinaryTree<T> updateTree(unsigned weight, unsigned idx, const T& val, const Persistent::CompleteBinaryTree<T>& tree);
static
TreeList update(unsigned idx, const T& val, const typename SkewBinaryRandomAccessList<T>::TreeList& treeList);




public:

SkewBinaryRandomAccessList();

bool isEmpty() const;

static SkewBinaryRandomAccessList<T> Cons(const T&, const SkewBinaryRandomAccessList<T>&);

const T& head() const;

SkewBinaryRandomAccessList<T> tail() const;

const T& lookup(unsigned) const;

static SkewBinaryRandomAccessList<T> Update( unsigned idx, const T& , const SkewBinaryRandomAccessList<T>&);

private: // data

TreeList treeList_;

};

template <class T>
SkewBinaryRandomAccessList<T>::SkewBinaryRandomAccessList() { }

template <class T>
SkewBinaryRandomAccessList<T>::SkewBinaryRandomAccessList(const TreeList& treeList) : treeList_(treeList) {}


template <class T>
bool
SkewBinaryRandomAccessList<T>::isEmpty() const {
  return treeList_.isEmpty();
}

template <class T>
SkewBinaryRandomAccessList<T>
SkewBinaryRandomAccessList<T>::Cons(const T& val, const SkewBinaryRandomAccessList<T>& sbral) {
  auto treeList = sbral.treeList_;

  if (!treeList.isEmpty()) {
    const auto& [weight1, tree1] = treeList.head();
    auto treeListTail = treeList.tail();

    if(!treeListTail.isEmpty()) {
      const auto& [weight2, tree2] = treeListTail.head();

      if (auto newTree = CompleteBinaryTree<T>::CreateCompleteBinaryTree(val, tree1, tree2)) {
        auto rest = treeListTail.tail();
        return SkewBinaryRandomAccessList<T>(TreeList(WeightAndTree(1 + weight1 + weight2, *newTree), rest));
      }
    }
  }
  return SkewBinaryRandomAccessList<T>(TreeList(std::make_pair<unsigned, CompleteBinaryTree<T>>(1, val), treeList));
}

template <class T>
const T&
SkewBinaryRandomAccessList<T>::head() const {
   const auto& [_, tree] = treeList_.head();
   return tree.root();
}

template <class T>
SkewBinaryRandomAccessList<T>
SkewBinaryRandomAccessList<T>::tail() const {
  const auto& [weight, tree] = treeList_.head();
  if (weight == 1)
    return SkewBinaryRandomAccessList<T>(treeList_.tail());

  const auto& tail = treeList_.tail();

  auto left = tree.left();
  auto right = tree.right();

  return SkewBinaryRandomAccessList<T>(TreeList(
                                        WeightAndTree(weight / 2, left), TreeList( 
                                        WeightAndTree(weight / 2, right), tail)));
}

template <class T>
const T&
SkewBinaryRandomAccessList<T>::lookupTree(unsigned weight, unsigned idx, const Persistent::CompleteBinaryTree<T>& tree) const {
  if (idx == 0)
    return tree.root();

  return (idx <= weight / 2) ? lookupTree(weight / 2, idx - 1, tree.left())
                             : lookupTree(weight / 2, idx - 1 - weight / 2, tree.right());
}

template <class T>
const T&
SkewBinaryRandomAccessList<T>::lookup(unsigned idx, const TreeList& treeList) const {
  const auto& [weight, tree] = treeList.head();
  return idx < weight ? lookupTree(weight, idx, tree)
                      : lookup(idx - weight, treeList.tail());
}

template <class T>
const T&
SkewBinaryRandomAccessList<T>::lookup(unsigned idx) const {
  return lookup(idx, treeList_);
}

template <class T>
Persistent::CompleteBinaryTree<T>
SkewBinaryRandomAccessList<T>::updateTree(unsigned weight, unsigned idx, const T& val, const Persistent::CompleteBinaryTree<T>& tree) {
  if (idx == 0)
    return *Persistent::CompleteBinaryTree<T>::CreateCompleteBinaryTree(val, tree.left(), tree.right());
  return idx > weight / 2 ? *Persistent::CompleteBinaryTree<T>::CreateCompleteBinaryTree(tree.root(), tree.left(), updateTree(weight / 2, idx - 1 - weight / 2, val, tree.right()))
                          : *Persistent::CompleteBinaryTree<T>::CreateCompleteBinaryTree(tree.root(), updateTree(weight / 2, idx - 1, val, tree.left()), tree.right());
}

template <class T>
SkewBinaryRandomAccessList<T>::TreeList
SkewBinaryRandomAccessList<T>::update(unsigned idx, const T& val, const typename SkewBinaryRandomAccessList<T>::TreeList& treeList)
{
  const auto& [weight, tree] = treeList.head();
  return idx < weight ? TreeList(WeightAndTree(weight, updateTree(weight, idx, val, tree)), treeList.tail())
                      : TreeList(WeightAndTree(weight, tree), update(idx - weight, val, treeList.tail()));
}

template <class T>
SkewBinaryRandomAccessList<T>
SkewBinaryRandomAccessList<T>::Update(unsigned idx, const T& val, const SkewBinaryRandomAccessList<T>& sbral) {
  return SkewBinaryRandomAccessList(update(idx, val, sbral.treeList_));
}

} // end of Persistent namespace

#endif
