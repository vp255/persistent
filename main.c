#include "persistent_list.h"
#include "binary_tree.h"

int main() {
  auto empty = Persistent::List<int>();
  auto list1 = Persistent::List<int>(5, empty);
  auto list2 = Persistent::List<int>(4, list1);

  auto cblt  = Persistent::Tree<int>();
  auto cblt2 = Persistent::Tree<int>(4, cblt, cblt);
  return 0;
}
