#include <map>
#include <memory>
#include <random>
#include <chrono>

#include "Structure.h"

using namespace std;

template<typename T>
struct NodeSkipList {
    T data;
    map<int, shared_ptr<NodeSkipList>>nextNode;

    NodeSkipList() = default;
    explicit NodeSkipList(int data) : data(data){};
};


template<typename T>
class SkipList : public Structure<T> {
  private:
    shared_ptr<NodeSkipList<T>> head;
    shared_ptr<NodeSkipList<T>> tail;
    const int maxLevel;

    int randomize() {
        std::mt19937 gen(std::chrono::system_clock::now().time_since_epoch().count());
        std::uniform_real_distribution<double> dis(0.0, 1.0);

        int level = 0;

        while (dis(gen) < 0.5 && level < maxLevel)
            level++;

        return level;
    }

  public:
  explicit SkipList(int maxL) : maxLevel(maxL){
      head = make_shared<NodeSkipList<T>>();
      tail = make_shared<NodeSkipList<T>>();

      for (int i = 0; i < maxLevel; ++i) {
          head->nextNode[i] = tail;
      }
    };

  void display() const override {

    for (int level = maxLevel - 1; level >= 0; level--) {
        cout << "Level " << level << ": ";

        shared_ptr<NodeSkipList<T>> current = head->nextNode[level];
        while (current != tail) {
            cout << current->data << " ";
            current = current->nextNode[level];
        }

        cout << '\n';
    }
  }

  void insert(T value) override {
    int newLevel = randomize();
    shared_ptr<NodeSkipList<T>> newNode(new NodeSkipList<T>(value));
      
      int currentLevel = maxLevel - 1;
      shared_ptr<NodeSkipList<T>>currentNode = head;

      while (currentLevel >= 0) {

        while (currentNode->nextNode[currentLevel] != tail && currentNode->nextNode[currentLevel]->data < value) {
          currentNode = currentNode->nextNode[currentLevel];
        }
        
        // check duplicates
        if (currentNode->nextNode[currentLevel] != tail && currentNode->nextNode[currentLevel]->data == value) return;

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
            while (currentNode->nextNode[currentLevel] != tail && currentNode->nextNode[currentLevel]->data < value) {
                currentNode = currentNode->nextNode[currentLevel];
            }

            prevNodes[currentLevel] = currentNode;
            currentLevel--;
        }

        if (currentNode->nextNode[0] == tail || currentNode->nextNode[0]->data != value) {
            cout << "Value " << value << " not found in SkipList. Cannot remove." << endl;
            return;
        }

        shared_ptr<NodeSkipList<T>> nodeToRemove = currentNode->nextNode[0];
        for (int i = 0; i < maxLevel; ++i) {
            if (prevNodes[i] != nullptr && prevNodes[i]->nextNode[i] == nodeToRemove) {
                prevNodes[i]->nextNode[i] = nodeToRemove->nextNode[i];
            }
        }

        nodeToRemove->nextNode.clear();
        cout << "Value " << value << " removed from SkipList" << endl;
    }

    void search(T value) override {
      int currentLevel = maxLevel - 1;
      shared_ptr<NodeSkipList<T>> currentNode = head;

      while (currentLevel >= 0) {
          while (currentNode->nextNode[currentLevel] != tail && currentNode->nextNode[currentLevel]->data < value) {
              currentNode = currentNode->nextNode[currentLevel];
          }

          if (currentNode->nextNode[currentLevel] != tail && currentNode->nextNode[currentLevel]->data == value) {
              cout << "Value " << value << " found in SkipList" << '\n';
              return;
          }

          currentLevel--;
      }

      cout << "Value " << value << " not found in SkipList" << '\n';
  }
};