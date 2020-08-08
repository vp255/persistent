#include <memory>

namespace Persistent {

template<class T>
class BinaryTree {

  struct Data {
    Data(T val, std::shared_ptr<Data> left, std::shared_ptr<Data> right)
      : val_(val)
      , left_(left)
      , right_(right)
    {}

    const T val_;
    std::shared_ptr<Data> left_;
    std::shared_ptr<Data> right_;
  };


  std::shared_ptr<BinaryTree::Data> data_;

  explicit BinaryTree(std::shared_ptr<BinaryTree::Data> data)
    : data_(data) {}


public:

  BinaryTree();
  BinaryTree(T val,
                         const BinaryTree& left,
                         const BinaryTree& right);

  bool isEmpty() {
    return !data_.get();
  }

  BinaryTree<T> left();
  BinaryTree<T> right();

};

template<class T>
BinaryTree<T>::BinaryTree()
  : data_(nullptr)
{}

template<class T>
BinaryTree<T>::BinaryTree(T val,
    const BinaryTree<T>& left,
    const BinaryTree<T>& right)
  : data_(std::make_shared<BinaryTree<T>::Data>(val, left.data_, right.data_))
{}

template<class T>
BinaryTree<T> BinaryTree<T>::left() {
  return BinaryTree<T>(data_->left_);
}

template<class T>
BinaryTree<T> BinaryTree<T>::right() {
  return BinaryTree<T>(data_->right_);
}

}
