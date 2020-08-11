#ifndef RANDOM_ACCESS_LIST_TEST_H
#define RANDOM_ACCESS_LIST_TEST_H

#include "persistent/random_access_list.h"
#include "persistent/skew_binary_random_access_list.h"
#include <iostream>

namespace RandomAccessListTests {

template<template <class> class R, class T> requires Persistent::RandomAccessList<R, T>
bool Foo(const R<T>& t) 
{
  return t.isEmpty();
}


namespace SkewBinaryRandomAccessListTests {


void run() {
  std::cout << "Running SkewBinaryRandomAccessList Tests ..." << std::endl;

  auto sbral  = Persistent::SkewBinaryRandomAccessList<int>();
  auto sbral1 = Persistent::SkewBinaryRandomAccessList<int>::Cons(1, sbral);
  auto sbral2 = Persistent::SkewBinaryRandomAccessList<int>::Cons(2, sbral1);
  auto sbral3 = Persistent::SkewBinaryRandomAccessList<int>::Cons(3, sbral2);

  auto updated = Persistent::SkewBinaryRandomAccessList<int>::Update(1, 99, sbral3);

  std::cout << "SBRAL: " << std::endl;

  for (int i : {0,1,2}) {
    std::cout << "Node: " << i << std::endl;
    std::cout << sbral3.lookup(i) << std::endl;
    std::cout << updated.lookup(i) << std::endl;
  }

}

} // end of SkewBinaryRandomAccessListTests namespace

} // end of RandomAccessListTests namespace

#endif
