#pragma once
#include <iostream>

template<typename T>
class Structure {
  virtual void insert(T value) = 0;
  virtual void remove(T value) = 0;
  virtual void search(T value) = 0;
  virtual void display() const {
    std::cout << "Display data structure";
  }
};