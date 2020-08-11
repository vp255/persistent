#ifndef LIST_TEST_H
#define LIST_TEST_H

#include <iostream>

#include "persistent/list.h"

namespace ListsTests {

void run() {
  std::cout << "Running List Tests ..." << std::endl;
  auto empty = Persistent::List<int>();
  auto list1 = Persistent::List<int>(5, empty);
  auto list2 = Persistent::List<int>(4, list1);
  std::cout << " Node1: " << list2.head()
            << " Node2: " << list2.tail().head() << std::endl;
}

} // end of ListTests namespace

#endif
