
class SkipList : public BST {
  private:
    shared_ptr<Node> head;
    shared_ptr<Node> tail;
    const int maxLevel;

    void randomize() {
        int level = 0;

        while ((double)rand() / RAND_MAX < 0.5 && level < maxLevel) level++;
    
        return level;
    }

  public:

  SkipList() = default;

  void insert(T value) override {
    int newLevel = randomize();
    shared_ptr<Node> newNode(new Node(value, newLevel));

    if (head->nextNode[0] == tail) {
      // if the list is empty

      for (int i = 0; i < newLevel; i++) {
        head->nextNode[i] = newNode;
        newNode->nextNode[i] = tail;
      }

    } else {
      // starting from the max level
      
      int currentLevel = maxLevel - 1;
      shared_ptr<Node>currentNode = head;

      while (currentNode >= 0) {

        while (currentNode->nextNode[currentLevel] != tail && currentNode->nextNode[currentLevel]->data < value) {
          currentNode = currentNode->nextNode[currentLevel];
        }
        
        // check duplicates
        if (currentNode->nextNode[currentLevel] != tail && currentNode->nextNode[currentLevel]->data == value) return;

        if (currentLevel < newLevel) {
          newNode->nextNode[currentLevel] = currentNode->nextNode[currentLevel];
          currentNode->nextNode[currentLevel] = newNode;
        }
        
        currentLevel--;
      }
    }
  }

  void remove(T value) override {
    // TODO
  }

  void search(T value) override {
    // TODO
  }
}

class Node {
  private:
    int data;  
    int level;
    map<int, shared_ptr<Node>>nextNode; // for each level, define the next node;
  
  public:
    Node(int data, int level) : data(data), level(level){};
}
