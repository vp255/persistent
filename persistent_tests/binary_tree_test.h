#ifndef BINARY_TREE_TEST_H
#define BINARY_TREE_TEST_H

#include <iostream>

#include "persistent/binary_tree.h"

namespace BinaryTreeTests {

void run() {
  std::cout << "Running BinaryTree Tests ..." << std::endl;
  auto cblt  = Persistent::BinaryTree<int>();
  auto cblt2 = Persistent::BinaryTree<int>(4, cblt, cblt);
  std::cout << " Root: " << cblt2.root() << std::endl;
}

} // end of ListTests namespace
#endif
