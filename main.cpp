#include <iostream>
#include "Testing.h"

int main() {
    int N = 10000000;
    int maxValue = 10000000;

    std::cout << "Testing Red-Black Tree...\n";
    runTest<int>(std::cout, N, maxValue, ALGO_REDBLACK);
    //std::cout << "\nTesting SkipList...\n";
    //runTest<int>(std::cout, N, maxValue, ALGO_SKIPLIST);
    std::cout << "\nTesting Treap...\n";
    runTest<int>(std::cout, N, maxValue, ALGO_TREAP);
    return 0;
}

