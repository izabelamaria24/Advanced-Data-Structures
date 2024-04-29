    #include <memory>
    #include <random>
    #include <chrono>
    #include "Structure.h"
    using namespace std;

    template<typename T>
    struct NodeTreap {
        T key;
        T priority;
        shared_ptr<NodeTreap<T>> left;
        shared_ptr<NodeTreap<T>> right;

        NodeTreap(T key, T priority) : key(key), priority(priority), left(nullptr), right(nullptr) {}
    };

    template<typename T>
    class Treap : public Structure<T>{
    private:
        shared_ptr<NodeTreap<T>> root;
        mt19937 gen;

        shared_ptr<NodeTreap<T>> rotateRight(shared_ptr<NodeTreap<T>> node) {
            shared_ptr<NodeTreap<T>> newRoot = node->left;
            node->left = newRoot->right;
            newRoot->right = node;
            return newRoot;
        }

        shared_ptr<NodeTreap<T>> rotateLeft(shared_ptr<NodeTreap<T>> node) {
            shared_ptr<NodeTreap<T>> newRoot = node->right;
            node->right = newRoot->left;
            newRoot->left = node;
            return newRoot;
        }

        shared_ptr<NodeTreap<T>> insertNode(shared_ptr<NodeTreap<T>> node, T key, T priority) {
            if (!node)
                return make_shared<NodeTreap<T>>(key, priority);

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

        void searchNode(shared_ptr<NodeTreap<T>> node, T key) {
            if (!node)
                return;
            if (node->key == key) {
               // std::cout << "Found " << key << std::endl;
                return;
            }
            if (key < node->key)
                searchNode(node->left, key);
            else
                searchNode(node->right, key);
        }

        shared_ptr<NodeTreap<T>> removeNode(shared_ptr<NodeTreap<T>> node, T key) {
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

        void displayInOrder(shared_ptr<NodeTreap<T>> node) {
                if (node) {
                    displayInOrder(node->left);
                    cout << "(" << node->key << ", " << node->priority << ") ";
                    displayInOrder(node->right);
                }
            }

    public:
        Treap() : root(nullptr), gen(chrono::system_clock::now().time_since_epoch().count()) {}

        void insert(T key) override{
            T priority = static_cast<T>(gen());
            root = insertNode(root, key, priority);
        }

        void search(T key) override{
            return searchNode(root, key);
        }

        void remove(T key) override{
            root = removeNode(root, key);
        }

        void display() {
                displayInOrder(root);
        }
    };
