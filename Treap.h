#include <memory>
#include <random>
#include <chrono>
#include "Structure.h"
using namespace std;

template<typename T>
struct Node {
    T key;
    T priority;
    shared_ptr<Node<T>> left;
    shared_ptr<Node<T>> right;

    Node(T key, T priority) : key(key), priority(priority), left(nullptr), right(nullptr) {}
};

template<typename T>
class Treap : public Structure<T>{
private:
    shared_ptr<Node<T>> root;
    mt19937 gen;

    shared_ptr<Node<T>> rotateRight(shared_ptr<Node<T>> node) {
        shared_ptr<Node<T>> newRoot = node->left;
        node->left = newRoot->right;
        newRoot->right = node;
        return newRoot;
    }

    shared_ptr<Node<T>> rotateLeft(shared_ptr<Node<T>> node) {
        shared_ptr<Node<T>> newRoot = node->right;
        node->right = newRoot->left;
        newRoot->left = node;
        return newRoot;
    }

    shared_ptr<Node<T>> insertNode(shared_ptr<Node<T>> node, T key, T priority) {
        if (!node)
            return make_shared<Node<T>>(key, priority);

        if (key < node->key) {
            node->left = insertNode(node->left, key, priority);
            if (node->left->priority > node->priority)
                node = rotateRight(node);
        } else if (key > node->key) {
            node->right = insertNode(node->right, key, priority);
            if (node->right->priority > node->priority)
                node = rotateLeft(node);
        }
        return node;
    }

    bool searchNode(shared_ptr<Node<T>> node, T key) {
        if (!node)
            return false;
        if (node->key == key)
            return true;
        if (key < node->key)
            return searchNode(node->left, key);
        else
            return searchNode(node->right, key);
    }

    shared_ptr<Node<T>> removeNode(shared_ptr<Node<T>> node, T key) {
        if (!node)
            return nullptr;

        if (key < node->key)
            node->left = removeNode(node->left, key);
        else if (key > node->key)
            node->right = removeNode(node->right, key);
        else {
            if (!node->left) {
                return node->right;
            } else if (!node->right) {
                return node->left;
            }

            if (node->left->priority > node->right->priority) {
                node = rotateRight(node);
                node->right = removeNode(node->right, key);
            } else {
                node = rotateLeft(node);
                node->left = removeNode(node->left, key);
            }
        }
        return node;
    }
   
    shared_ptr<Node<T>> mergeTreaps(shared_ptr<Node<T>> treap1, shared_ptr<Node<T>> treap2) 
    {
        if (!treap1)
            return treap2;
        if (!treap2)
            return treap1;

        if (treap1->priority < treap2->priority) 
        {
            treap1->right = mergeTreaps(treap1->right, treap2);
            return treap1;
        } 
        else
        {
            treap2->left = mergeTreaps(treap1, treap2->left);
            return treap2;
        }
    }
    
    shared_ptr<Node<T>> mergeTreaps(Treap<T>& treap1, Treap<T>& treap2) 
    {
        return mergeTreaps(treap1.getRoot(), treap2.getRoot());
    }
    T findMaxSmallerOrEqualNode(shared_ptr<Node<T>> node, T X, T best_so_far) {
        if (!node)
            return best_so_far;
        
        if (node->key <= X) {
            if (node->key > best_so_far)
                best_so_far = node->key;
            return findMaxSmallerOrEqualNode(node->right, X, best_so_far);
        } else {
            return findMaxSmallerOrEqualNode(node->left, X, best_so_far);
        }
    }
    T findMaxSmallerOrEqual(Treap<T>& treap, T X) {
        return findMaxSmallerOrEqualNode(treap.getRoot(), X, numeric_limits<T>::min());
    }
    
    T findMinLargerOrEqualNode(shared_ptr<Node<T>> node, T X, T best_so_far) {
        if (!node)
            return best_so_far;
        
        if (node->key >= X) {
            if (node->key < best_so_far)
                best_so_far = node->key;
            return findMinLargerOrEqualNode(node->left, X, best_so_far);
        } else {
            return findMinLargerOrEqualNode(node->right, X, best_so_far);
        }
    }
    
    T findMinLargerOrEqual(Treap<T>& treap, T X) {
        return findMinLargerOrEqualNode(treap.getRoot(), X, numeric_limits<T>::max());
    }
    
    void displayinorder(shared_ptr<Node<T>> node) {
        if (node) {
            displayinorder(node->left);
            cout << "(" << node->key << ", " << node->priority << ") ";
            displayinorder(node->right);
            }
        }
    void displaySequenceInRange(shared_ptr<Node<T>> node, T x, T y) {
            if (!node) return;
            
            if (node->key >= x && node->key <= y) {
                displaySequenceInRange(node->left, x, y);
                cout << "(" << node->key << ", " << node->priority << ") ";
                displaySequenceInRange(node->right, x, y);
            } else if (node->key < x) {
                displaySequenceInRange(node->right, x, y);
            } else {
                displaySequenceInRange(node->left, x, y);
            }
        }

public:
    Treap() : root(nullptr), gen(chrono::system_clock::now().time_since_epoch().count()) {}

    void insert(T key) override{
        T priority = static_cast<T>(gen());
        root = insertNode(root, key, priority);
    }

    bool search(T key) override{
        return searchNode(root, key);
    }

    void remove(T key) override{
        root = removeNode(root, key);
    }
    
    shared_ptr<Node<T>> getRoot() const { return root; }
    
    void reunion(Treap<T>& other) override {
        root = mergeTreaps(*this, other);
        other.clear();
    }
    
    T maxSmallerOrEqual(T X) override{
        return findMaxSmallerOrEqual(*this, X);
    }
    
    T minLargerOrEqual(T X) override{
        return findMinLargerOrEqual(*this, X);
    }
    
    void displayInOrdine() override{
        display(root);
    }
    void displaySequence(T x, T y) override {
        displaySequenceInRange(root, x, y);
    }
};
