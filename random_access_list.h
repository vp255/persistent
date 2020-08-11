#ifndef RANDOM_ACCESS_LIST_H
#define RANDOM_ACCESS_LIST_H

#include <utility>
#include <optional>

namespace Persistent {

template <template<class> class T, class A>
concept RandomAccessList = requires(const T<A>& t, const A& a) {
  { t.isEmpty() } -> bool
  { T<A>::Cons(a, t ) } -> T
  { t.head() } -> const A&
  { t.tail() } -> const T<A>& ; 
  { t.lookup(1)  } -> A ;
  { T<A>::Update(1, a, t)  } -> const T<A>& ; 
};

}

/* example Concept

template <class T>
concept Num = requires(T a, T b) {
  {a + b} -> T
  {a * b} -> T
  {a / b} -> T
};

*/



#endif
