#include <iostream>
#include "SkipList.cpp"

using namespace std;

int main() {
  SkipList<int> list(10);

  list.insert(6);
  list.insert(7);
  list.insert(114);
  list.insert(1);
  list.insert(20);

  list.display();
}
