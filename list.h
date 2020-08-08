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

  std::shared_ptr<Data> data_;
  List(std::shared_ptr<Data> data) : data_(data) {}

  static List EmptyList;

public:

  List();
  List(T val, const List & tail);

  bool isEmpty() {
    return !data_.get();
  }

  const T& head();
  List<T> tail();

};


//template<class T> 
//List<T>::List() : data_(nullptr) {}

template<class T>  // not thread safe?
List<T>::List() {
  static List<T>* EmptyList;

  if (!EmptyList)
    EmptyList = new List<T>(nullptr);

  *this = *EmptyList;

}

template<class T>
List<T>::List(T val, const List& tail) 
  : data_(std::make_shared<List<T>::Data>(val, tail.data_))
{ }

template<class T>
const T&
List<T>::head() {

  if (isEmpty()) {
    throw;
  }
  return data_.val_;
}

template<class T>
List<T>
List<T>::tail() {

  if (isEmpty()) {
    throw;
  }

  return List(data_->rest_);
}

}

/* Questions:

   Can we make a small optimization by having a private static empty list? Or is this impossible due to instatiation

 */
