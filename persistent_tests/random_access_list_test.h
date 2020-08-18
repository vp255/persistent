#ifndef RANDOM_ACCESS_LIST_TEST_H
#define RANDOM_ACCESS_LIST_TEST_H

#include "persistent/random_access_list.h"
#include "persistent/skew_binary_random_access_list.h"
#include <iostream>
#include <thread>

namespace RandomAccessListTests {

template<template <class> class R, class T> requires Persistent::RandomAccessList<R, T>
R<T> Build() 
{
  auto sbral = R<T>();
  for ( int i=49; i >= 0 ; --i ) {
    sbral = R<T>::Cons(i, sbral);
  }
  return sbral;
}

template<template <class> class R, class T> requires Persistent::RandomAccessList<R, T>
R<T> Modify(const R<T>& t) 
{
  auto sbral = t;
  for (int i=0; i < 50 ; i ++) {
    sbral = R<T>::Update(i, i+50, sbral);
  }
  return sbral;
}

template <template <class> class R, class T> requires Persistent::RandomAccessList<R, T>
void CheckUpdateCheck(const R<T>& ral) {
  for (int i=0; i < 50; ++i) {
    if (ral.lookup(i) != i) {
      std::cout << "construction test failed, ral.lookup(i) != i, " << ral.lookup(i) << " != " << i << std::endl;
    }
  }

  auto updatedral = ral;

  for (int i=0; i < 50; i++) {
    updatedral = R<T>::Update(i, i+50, updatedral);
    auto lookup_value = updatedral.lookup(i);
    if (lookup_value != i+50) {
      std::cout << "modify test failed" << std::endl;
      std::cout << "lookup_value: " << lookup_value << ", i: " << i << " ";
    }
  }
  return;
}

template <template <class> class R, class T> requires Persistent::RandomAccessList<R, T>
void RALTest() {
  const auto ral = Build<R, T>();
  std::vector<std::thread> threads;
  for (int i=0; i < 10; i++) {
    threads.push_back(std::thread(CheckUpdateCheck<R, T>, ral));
  }
  for (auto&& thread : threads) {
    thread.join();
  }
}


namespace SkewBinaryRandomAccessListTests {

void run() {
  std::cout << "Running SkewBinaryRandomAccessList Tests ..." << std::endl;
  RALTest<Persistent::SkewBinaryRandomAccessList, int>();
}

} // end of SkewBinaryRandomAccessListTests namespace

} // end of RandomAccessListTests namespace

#endif
