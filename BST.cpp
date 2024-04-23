
template<typename T>
class BST {

  virtual void insert(T value) = 0;
  virtual void remove(T value) = 0;
  virtual void search(T value) = 0;
  virtual void display() const {
    std::cout << "Display BST";
  }
}

