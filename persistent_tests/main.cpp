#include "persistent/list.h"
#include "persistent/binary_tree.h"
#include "random_access_list_test.h"
#include "list_test.h"
#include "binary_tree_test.h"

int main() {
  ListsTests::run();
  BinaryTreeTests::run();
  RandomAccessListTests::SkewBinaryRandomAccessListTests::run();
  return 0;
}
