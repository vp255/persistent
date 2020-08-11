#ifndef PERSISTENT_LIST_H
#define PERSISTENT_LIST_H

#include <iostream>
#include <memory>

namespace Persistent {

template<class T>
class List {

  struct Data {
    Data(T val, std::shared_ptr<Data> rest)
      : val_(val)
      , rest_(rest) {}

    const T val_;
    std::shared_ptr<Data> rest_;
  };

  explicit List(std::shared_ptr<Data> data) : data_(data) {}

  static List EmptyList;

public:

  List() = default;
  List(const List&) = default;
  ~List() = default;
  List(List&&) = default;
  List& operator=(List&&) = default;

  List(T val, const List & tail);

  bool isEmpty() const {
    return !data_.get();
  }

  const T& head() const;
  List<T> tail() const;

private:

  std::shared_ptr<Data> data_;

};

template<class T>
List<T>::List(T val, const List& tail) 
  : data_(std::make_shared<List<T>::Data>(val, tail.data_))
{ }

template<class T>
const T&
List<T>::head() const {

  if (isEmpty()) {
    std::cout << "trying to head an empty list" << std::endl;
    throw;
  }
  return data_->val_;
}

template<class T>
List<T>
List<T>::tail() const {

  if (isEmpty()) {
    std::cout << "trying to tail an empty list" << std::endl;
    throw;
  }

  return List(data_->rest_);
}

} // end of Persistent namespace

#endif
