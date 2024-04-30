
#include <random>
#include <chrono>
#include <memory>
#include <vector>
#include "Structure.h"

using namespace std;

template<typename T>
struct NodeSkipList {
    T data;
    vector<shared_ptr<NodeSkipList>>nextNode;
    NodeSkipList() = default;
    explicit NodeSkipList(int data, int maxLevel) : data(data), nextNode(maxLevel + 1, nullptr) {}

};


template<typename T>
class SkipList : public Structure<T> {
  private:
    shared_ptr<NodeSkipList<T>> head;
    shared_ptr<NodeSkipList<T>> tail;
    int maxLevel;

    int randomize() {
        std::mt19937 gen(std::chrono::system_clock::now().time_since_epoch().count());
        std::uniform_real_distribution<double> dis(0.0, 1.0);

        int level = 0;

        while (dis(gen) < 0.5 && level < maxLevel - 1)
            level++;

        return level;
    }

  public:
  explicit SkipList(int maxL) : maxLevel(maxL){
      head = make_shared<NodeSkipList<T>>(-1, maxL);
      tail = make_shared<NodeSkipList<T>>(-1, maxL);

      for (int i = 0; i < maxLevel; ++i) {
          head->nextNode[i] = tail;
      }
    };

  void display() const override {

    for (int level = maxLevel - 1; level >= 0; level--) {

        shared_ptr<NodeSkipList<T>> current = head->nextNode[level];
        while (current != tail) {
            cout << current->data << " ";
            current = current->nextNode[level];
        }

    }
  }

  void insert(T value) override {
    int newLevel = randomize();
    shared_ptr<NodeSkipList<T>> newNode(new NodeSkipList<T>(value, maxLevel));
      
      int currentLevel = maxLevel - 1;
      shared_ptr<NodeSkipList<T>>currentNode = head;

      while (currentLevel >= 0) {

        while (currentNode->nextNode[currentLevel] != tail && currentNode->nextNode[currentLevel] != nullptr && currentNode->nextNode[currentLevel]->data < value) {
          currentNode = currentNode->nextNode[currentLevel];
        }
        
        // check duplicates
        if (currentNode->nextNode[currentLevel] != tail && currentNode->nextNode[currentLevel] != nullptr && currentNode->nextNode[currentLevel]->data == value) return;

        if (currentLevel <= newLevel) {
          newNode->nextNode[currentLevel] = currentNode->nextNode[currentLevel];
          currentNode->nextNode[currentLevel] = newNode;
        }
        
        currentLevel--;
      }
  }

  
void remove(T value) override {
    int currentLevel = maxLevel - 1;
    shared_ptr<NodeSkipList<T>> currentNode = head;

    vector<shared_ptr<NodeSkipList<T>>> prevNodes(maxLevel, nullptr);

    while (currentLevel >= 0) {
        while (currentNode->nextNode[currentLevel] != nullptr && currentNode->nextNode[currentLevel] != tail && currentNode->nextNode[currentLevel]->data < value) {
            currentNode = currentNode->nextNode[currentLevel];
        }

        prevNodes[currentLevel] = currentNode;
        currentLevel--;
    }

    if (currentNode->nextNode[0] != nullptr && currentNode->nextNode[0] != tail && currentNode->nextNode[0]->data == value) {
        shared_ptr<NodeSkipList<T>> nodeToRemove = currentNode->nextNode[0];
        
        for (int i = 0; i < maxLevel; ++i) {
            if (prevNodes[i] != nullptr && prevNodes[i]->nextNode[i] == nodeToRemove) {
                prevNodes[i]->nextNode[i] = nodeToRemove->nextNode[i];
            }
        }

        nodeToRemove->nextNode.clear();
        
    } else {
    }
}
  
    void search(T value) override {
      int currentLevel = maxLevel - 1;
      shared_ptr<NodeSkipList<T>> currentNode = head;

      while (currentLevel >= 0) {
          while (currentNode->nextNode[currentLevel] != nullptr && currentNode->nextNode[currentLevel] != tail && currentNode->nextNode[currentLevel]->data < value) {
              currentNode = currentNode->nextNode[currentLevel];
          }

          if (currentNode->nextNode[currentLevel] != nullptr && currentNode->nextNode[currentLevel] != tail && currentNode->nextNode[currentLevel]->data == value) {
              return;
          }

          currentLevel--;
      }
  }
};
