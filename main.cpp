#include "SkipList.h"

int main() {
  SkipList<int>list(5);

  list.insert(10);
  list.insert(100);
  list.insert(1);
  list.insert(14);
  list.insert(26);

  list.display();

  list.search(26);
  list.search(1);
  list.search(101);
}
