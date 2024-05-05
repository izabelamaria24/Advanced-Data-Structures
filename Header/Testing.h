//
// Created by Alex Pascaru on 30.04.2024.
//

#ifndef ADVANCED_DATA_STRUCTURES_TESTING_H
#define ADVANCED_DATA_STRUCTURES_TESTING_H

#include <chrono>
#include <fstream>
#include <random>
#include <vector>
#include <thread>
#include <future>

#include "RedBlack.h"
#include "SkipList.h"
#include "Treap.h"

enum {
    ALGO_REDBLACK,
    ALGO_SKIPLIST,
    ALGO_TREAP
};

template<typename T>
void testOperation(std::vector<T>& data, std::ostream& os, int algorithm, const int N, const int maxValue) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(data.begin(), data.end(), gen);  // Ensure different operation orders

    auto start = std::chrono::steady_clock::now();
    float elapsed_seconds;

    switch (algorithm) {
        case ALGO_REDBLACK: {
            RedBlack<T> rbTree;

            //Insertion
            for (auto& item : data) {
                rbTree.insert(item);
            }
            auto finish = std::chrono::steady_clock::now();
            elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<float>>(finish - start).count();
            os << "Red-Black Tree insertion time for " << N << " elements with max value " << maxValue <<": " << elapsed_seconds << " seconds\n";

            // Deletion
            std::shuffle(data.begin(), data.end(), gen);  // Shuffle the data
            start = std::chrono::steady_clock::now();
            for (int i = 0; i < N / 2; ++i) {
                rbTree.remove(data[i]);
            }
             finish = std::chrono::steady_clock::now();
            elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<float>>(finish - start).count();
            os << "Red-Black Tree deletion time for " << N / 2 << " elements with max value " << maxValue <<": " << elapsed_seconds << " seconds\n";

            std::shuffle(data.begin(), data.end(), gen);

            // Search for N/4 elements
            start = std::chrono::steady_clock::now();
            for (int i = 0; i < N / 4; ++i) {
                rbTree.search(data[i]);
            }
            finish = std::chrono::steady_clock::now();
            elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<float>>(finish - start).count();
            os << "Red-Black Tree search time for " << N / 4 << " elements with max value " << maxValue <<": " << elapsed_seconds << " seconds\n";
            break;
        }
        case ALGO_SKIPLIST: {
            Skiplist<T> skipList;

            //Insertion
            for (auto& item : data) {
                skipList.insert(item);
            }
            auto finish = std::chrono::steady_clock::now();
            elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<float>>(finish - start).count();
            os << "SkipList insertion time for " << N << " elements with max value " << maxValue <<": " << elapsed_seconds << " seconds\n";

            // Deletion
            std::shuffle(data.begin(), data.end(), gen);
            start = std::chrono::steady_clock::now();
            for (int i = 0; i < N / 2; ++i) {
                skipList.remove(data[i]);
            }
            finish = std::chrono::steady_clock::now();
            elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<float>>(finish - start).count();
            os << "SkipList deletion time for " << N / 2 << " elements with max value " << maxValue <<": " << elapsed_seconds << " seconds\n";

            std::shuffle(data.begin(), data.end(), gen);

            // Search for N/4
            start = std::chrono::steady_clock::now();
            for (int i = 0; i < N / 4; ++i) {
                skipList.search(data[i]);
            }
            finish = std::chrono::steady_clock::now();
            elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<float>>(finish - start).count();
            os << "SkipList search time for " << N / 4 << " elements with max value " << maxValue <<": " << elapsed_seconds << " seconds\n";
            break;
        }
        case ALGO_TREAP: {
            Treap<T> treap;

            // Insertion
            for (auto& item : data) {
                treap.insert(item);
            }
            auto finish = std::chrono::steady_clock::now();
            elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<float>>(finish - start).count();
            os << "Treap insertion time for " << N << " elements with max value " << maxValue <<": " << elapsed_seconds << " seconds\n";

            // Deletion
            std::shuffle(data.begin(), data.end(), gen);
            start = std::chrono::steady_clock::now();
            for (int i = 0; i < N / 2; ++i) {
                treap.remove(data[i]);
            }
            finish = std::chrono::steady_clock::now();
            elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<float>>(finish - start).count();
            os << "Treap deletion time for " << N / 2 << " elements with max value " << maxValue <<": " << elapsed_seconds << " seconds\n";
            std::shuffle(data.begin(), data.end(), gen);

            // Search for N/4 elements
            start = std::chrono::steady_clock::now();
            for (int i = 0; i < N / 4; ++i) {
                treap.search(data[i]);
            }
            finish = std::chrono::steady_clock::now();
            elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<float>>(finish - start).count();
            os << "Treap search time for " << N / 4 << " elements with max value " << maxValue <<": "<< elapsed_seconds << " seconds\n";
            break;
        }
        default:{
        }
    }
}

template<typename T>
void runRandomTest(std::ostream& os, const int N, const int maxValue) {
    std::vector<T> data(N);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, maxValue);

    for (auto& item : data) {
        item = dist(gen);
    }

    auto rbFuture = std::async(std::launch::async, testOperation<T>, std::ref(data), std::ref(os), ALGO_REDBLACK, N, maxValue);
    auto slFuture = std::async(std::launch::async, testOperation<T>, std::ref(data), std::ref(os), ALGO_SKIPLIST, N, maxValue);
    auto trFuture = std::async(std::launch::async, testOperation<T>, std::ref(data), std::ref(os), ALGO_TREAP, N, maxValue);

    rbFuture.get();
    slFuture.get();
    trFuture.get();
}

template<typename T>
void runTestsFromFiles(std::ostream& os) {
    std::string filenames[] = {
            "CustomTests/data_set_1.txt", "CustomTests/data_set_2.txt", "CustomTests/data_set_3.txt",
            "CustomTests/data_set_4.txt", "CustomTests/data_set_5.txt", "CustomTests/data_set_6.txt",
            "CustomTests/data_set_7.txt"
    };

    for (auto& filename : filenames) {
        std::ifstream file(filename);
        if (!file) {
            os << "Failed to open file: " << filename << std::endl;
            continue;
        }

        int N, maxValue = 0;
        std::vector<T> data;

        file >> N;
        data.reserve(N);
        T value;
        while (file >> value) {
            data.push_back(value);
            if (value > maxValue) {
                maxValue = value;
            }
        }

        os << "Running tests for file: " << filename << std::endl;
        std::future<void> rbFuture = std::async(std::launch::async, testOperation<T>, std::ref(data), std::ref(os), ALGO_REDBLACK, N, maxValue);
        std::future<void> slFuture = std::async(std::launch::async, testOperation<T>, std::ref(data), std::ref(os), ALGO_SKIPLIST, N, maxValue);
        std::future<void> trFuture = std::async(std::launch::async, testOperation<T>, std::ref(data), std::ref(os), ALGO_TREAP, N, maxValue);

        rbFuture.get();
        slFuture.get();
        trFuture.get();
    }
}

#endif //ADVANCED_DATA_STRUCTURES_TESTING_H