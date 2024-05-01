#pragma once
#include <iostream>

template<typename T>
class Structure {
  // 1
  virtual void insert(T value) = 0; 
  // 2
  virtual void remove(T value) = 0;
  // 3
  virtual void search(T value) = 0;
  // 4
  virtual void maxSmallerOrEqual(T value) {
    std::cout << "Search max value less than given value";
  }
  // 5 
  virtual void minLargerOrEqual(T value) {
    std::cout << "Search min value greater than given value";
  }
  // 6
  virtual void display() const {
    std::cout << "Display data structure";
  }
};
