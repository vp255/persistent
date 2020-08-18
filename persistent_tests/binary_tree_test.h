#ifndef BINARY_TREE_TEST_H
#define BINARY_TREE_TEST_H

#include <iostream>

#include "persistent/binary_tree.h"

namespace BinaryTreeTests {

template <template <class> class C, class A, template <class> class T>
C<A> InOrderTraversal(const T<A>& tree) {
  C<A> result;
  InOrderTraversal(tree, result);
  return result;
}

template <template <class> class C, class A, template <class> class T>
void InOrderTraversal(const T<A>& tree, C<A>& result) {
  // not yet implemented
}


void run() {
  std::cout << "Running BinaryTree Tests ..." << std::endl;
  // not yet implemented
  auto cblt  = Persistent::BinaryTree<int>();
  auto cblt2 = Persistent::BinaryTree<int>(4, cblt, cblt);
  std::cout << " Root: " << cblt2.root() << std::endl;
}

} // end of ListTests namespace
#endif
