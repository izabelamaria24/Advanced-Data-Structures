//
// Created by Alex Pascaru on 30.04.2024.
//

#ifndef ADVANCED_DATA_STRUCTURES_TESTING_H
#define ADVANCED_DATA_STRUCTURES_TESTING_H

#include <chrono>
#include <fstream>
#include <random>
#include <vector>
#include "RedBlack.h"
#include "SkipList.h"
#include "Treap.h"

enum {
    ALGO_REDBLACK,
    ALGO_SKIPLIST,
    ALGO_TREAP
};

template<typename T>
void runTest(std::ostream& os, const int N, const int maxValue, int algorithm) {
    std::vector<T> data(N);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, maxValue);

    // Generate numbers
    for (auto& item : data) {
        item = dist(gen);
    }

    auto start = std::chrono::steady_clock::now();
    auto finish = std::chrono::steady_clock::now();
    float elapsed_seconds;

    switch (algorithm) {
        case ALGO_REDBLACK: {
            RedBlack<T> rbTree;

            //Insertion
            for (auto& item : data) {
                rbTree.insert(item);
            }
            finish = std::chrono::steady_clock::now();
            elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<float>>(finish - start).count();
            os << "Red-Black Tree insertion time for " << N << " elements: " << elapsed_seconds << " seconds\n";

            // Deletion
            std::shuffle(data.begin(), data.end(), gen);  // Shuffle the data
            start = std::chrono::steady_clock::now();
            for (int i = 0; i < N / 2; ++i) {
                rbTree.remove(data[i]);
            }
            finish = std::chrono::steady_clock::now();
            elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<float>>(finish - start).count();
            os << "Red-Black Tree deletion time for " << N / 2 << " elements: " << elapsed_seconds << " seconds\n";

            std::shuffle(data.begin(), data.end(), gen);

            // Search for N/4 elements
            start = std::chrono::steady_clock::now();
            for (int i = 0; i < N / 4; ++i) {
                rbTree.search(data[i]);
            }
            finish = std::chrono::steady_clock::now();
            elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<float>>(finish - start).count();
            os << "Red-Black Tree search time for " << N / 4 << " elements: " << elapsed_seconds << " seconds\n";
            break;
        }
        case ALGO_SKIPLIST: {
            SkipList<T> skipList;

            //Insertion
            for (auto& item : data) {
                skipList.insert(item);
            }
            finish = std::chrono::steady_clock::now();
            elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<float>>(finish - start).count();
            os << "SkipList insertion time for " << N << " elements: " << elapsed_seconds << " seconds\n";

            // Deletion
            std::shuffle(data.begin(), data.end(), gen);
            start = std::chrono::steady_clock::now();
            for (int i = 0; i < N / 2; ++i) {
                skipList.remove(data[i]);
            }
            finish = std::chrono::steady_clock::now();
            elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<float>>(finish - start).count();
            os << "SkipList deletion time for " << N / 2 << " elements: " << elapsed_seconds << " seconds\n";

            std::shuffle(data.begin(), data.end(), gen);

            // Search for N/4
            start = std::chrono::steady_clock::now();
            for (int i = 0; i < N / 4; ++i) {
                skipList.search(data[i]);
            }
            finish = std::chrono::steady_clock::now();
            elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<float>>(finish - start).count();
            os << "SkipList search time for " << N / 4 << " elements: " << elapsed_seconds << " seconds\n";
            break;
        }
        case ALGO_TREAP: {
            Treap<T> treap;

            // Insertion
            for (auto& item : data) {
                treap.insert(item);
            }
            finish = std::chrono::steady_clock::now();
            elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<float>>(finish - start).count();
            os << "Treap insertion time for " << N << " elements: " << elapsed_seconds << " seconds\n";

            // Deletion
            std::shuffle(data.begin(), data.end(), gen);
            start = std::chrono::steady_clock::now();
            for (int i = 0; i < N / 2; ++i) {
                treap.remove(data[i]);
            }
            finish = std::chrono::steady_clock::now();
            elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<float>>(finish - start).count();
            os << "Treap deletion time for " << N / 2 << " elements: " << elapsed_seconds << " seconds\n";
            std::shuffle(data.begin(), data.end(), gen);

            // Search for N/4 elements
            start = std::chrono::steady_clock::now();
            for (int i = 0; i < N / 4; ++i) {
                treap.search(data[i]);
            }
            finish = std::chrono::steady_clock::now();
            elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<float>>(finish - start).count();
            os << "Treap search time for " << N / 4 << " elements: " << elapsed_seconds << " seconds\n";
            break;
        }
    }
}
#endif //ADVANCED_DATA_STRUCTURES_TESTING_H
