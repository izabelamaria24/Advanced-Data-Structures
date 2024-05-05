#include "Structure.h"

template<typename T>
struct NodeRedBlack{
    T data;
    std::shared_ptr<NodeRedBlack<T>> parent;
    std::shared_ptr<NodeRedBlack<T>> left;
    std::shared_ptr<NodeRedBlack<T> > right;
    int color;
};

template <typename T>
class RedBlack : public Structure<T>{
private:
    using NodePtr = std::shared_ptr<NodeRedBlack<T> >;
    NodePtr root;
    NodePtr T_null;

    void initializeNULLNode(NodePtr node, NodePtr parent) {
        node->data = T();
        node->parent = parent;
        node->left = T_null;
        node->right = T_null;
        node->color = 0;
    }

    void fixDelete(NodePtr x) {
        NodePtr s;
        while (x != root && x->color == 0) {
            if (x == x->parent->left) {
                s = x->parent->right;
                if (s->color == 1) {
                    s->color = 0;
                    x->parent->color = 1;
                    leftRotate(x->parent);
                    s = x->parent->right;
                }

                if (s->left->color == 0 && s->right->color == 0) {
                    s->color = 1;
                    x = x->parent;
                } else {
                    if (s->right->color == 0) {
                        s->left->color = 0;
                        s->color = 1;
                        rightRotate(s);
                        s = x->parent->right;
                    }

                    s->color = x->parent->color;
                    x->parent->color = 0;
                    s->right->color = 0;
                    leftRotate(x->parent);
                    x = root;
                }
            } else {
                s = x->parent->left;
                if (s->color == 1) {
                    s->color = 0;
                    x->parent->color = 1;
                    rightRotate(x->parent);
                    s = x->parent->left;
                }

                if (s->right->color == 0 && s->right->color == 0) {
                    s->color = 1;
                    x = x->parent;
                } else {
                    if (s->left->color == 0) {
                        s->right->color = 0;
                        s->color = 1;
                        leftRotate(s);
                        s = x->parent->left;
                    }
                    s->color = x->parent->color;
                    x->parent->color = 0;
                    s->left->color = 0;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = 0;
    }

    void fixInsert(NodePtr k){
        NodePtr u;
        while (k->parent->color == 1) {
            if (k->parent == k->parent->parent->right) {
                u = k->parent->parent->left;
                if (u->color == 1) {
                    u->color = 0;
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->left) {
                        k = k->parent;
                        rightRotate(k);
                    }
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    leftRotate(k->parent->parent);
                }
            } else {
                u = k->parent->parent->right;

                if (u->color == 1) {
                    u->color = 0;
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->right) {
                        k = k->parent;
                        leftRotate(k);
                    }
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    rightRotate(k->parent->parent);
                }
            }
            if (k == root) {
                break;
            }
        }
        root->color = 0;
    }

    void deleteNodeHelper(NodePtr node, int key) {

        NodePtr z = T_null;
        NodePtr x, y;
        while (node != T_null){
            if (node->data == key) {
                z = node;
            }

            if (node->data <= key) {
                node = node->right;
            } else {
                node = node->left;
            }
        }

        if (z == T_null) {
            //std::cout<<"Value was not found in the tree"<<std::endl;
            return;
        }

        y = z;
        int y_original_color = y->color;
        if (z->left == T_null) {
            x = z->right;
            rbTransplant(z, z->right);
        } else if (z->right == T_null) {
            x = z->left;
            rbTransplant(z, z->left);
        } else {
            y = minimum(z->right);
            y_original_color = y->color;
            x = y->right;
            if (y->parent == z) {
                x->parent = y;
            } else {
                rbTransplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }

            rbTransplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        if (y_original_color == 0){
            fixDelete(x);
        }
    }

    NodePtr searchTreeHelper(NodePtr node, int key) {
        if (node == T_null || key == node->data) {
            return node;
        }

        if (key < node->data) {
            return searchTreeHelper(node->left, key);
        }
        return searchTreeHelper(node->right, key);
    }

    void printHelper(NodePtr node, std::string indent = "", bool isLast = true) const {
        if (node != T_null) {
            std::cout << indent;

            if (isLast) {
                std::cout << "└──";
                indent += "   ";
            } else {
                std::cout << "├──";
                indent += "|  ";
            }
            std::string sColor;
            if(node->color){
                sColor = "Red";
            }else{
                sColor = "Black";
            }
            std::cout << node->data << " (" << sColor << ")" << std::endl;

            printHelper(node->left, indent, false);
            printHelper(node->right, indent, true);
        }
    }


    void rbTransplant(NodePtr u, NodePtr v){
        if (u->parent == nullptr) {
            root = v;
        } else if (u == u->parent->left){
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }

    NodePtr minimum(NodePtr node) {
        while (node->left != T_null) {
            node = node->left;
        }
        return node;
    }

    void leftRotate(NodePtr x) {
        NodePtr y = x->right;
        x->right = y->left;
        if (y->left != T_null) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    void rightRotate(NodePtr x) {
        NodePtr y = x->left;
        x->left = y->right;
        if (y->right != T_null) {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        } else if (x == x->parent->right) {
            x->parent->right = y;
        } else {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }

    void printInRange(NodePtr node, T X, T Y) const {
        if (node == T_null) return;
        if (X < node->data) printInRange(node->left, X, Y);
        if (X <= node->data && node->data <= Y) std::cout << node->data << " ";
        if (Y > node->data) printInRange(node->right, X, Y);
    }

public:
    explicit RedBlack() {
        T_null = std::make_shared<NodeRedBlack<T> >();
        initializeNULLNode(T_null, nullptr);
        root = T_null;
    }

    void insert(T key) override {
        NodePtr node = std::make_shared<NodeRedBlack<T> >();
        node->parent = nullptr;
        node->data = key;
        node->left = T_null;
        node->right = T_null;
        node->color = 1;

        NodePtr y = nullptr;
        NodePtr x = this->root;

        while (x != T_null) {
            y = x;
            if (node->data < x->data) {
                x = x->left;
            } else {
                x = x->right;
            }
        }

        node->parent = y;
        if (y == nullptr) {
            root = node;
        } else if (node->data < y->data) {
            y->left = node;
        } else {
            y->right = node;
        }

        if (node->parent == nullptr){
            node->color = 0;
            return;
        }

        if (node->parent->parent == nullptr) {
            return;
        }

        fixInsert(node);
    }

    void remove(T data) override {
        deleteNodeHelper(this->root, data);
    }


    void search (T key) override{
        NodePtr result = searchTreeHelper(this->root, key);
       /* if (result != T_null) {
            std::cout << "1" << std::endl;
        } else {
            std::cout << "0" << std::endl;
        }*/
    }

    void display() const override{
        if (root != T_null) {
            printHelper(root, "", true);
        }
    }

    void maxSmallerOrEqual(T X) override{
        NodePtr node = root;
        NodePtr best = T_null;

        while (node != T_null) {
            if (node->data <= X) {
                best = node;
                node = node->right;
            } else {
                node = node->left;
            }
        }

        if (best != T_null) {
            std::cout << "Largest number <= " << X << " is: " << best->data << std::endl;
        } else {
            std::cout << "No number <= " << X << std::endl;
        }
    }

    void minLargerOrEqual(T X) override{
        NodePtr node = root;
        NodePtr best = T_null;

        while (node != T_null) {
            if (node->data >= X) {
                best = node;
                node = node->left;
            } else {
                node = node->right;
            }
        }

        if (best != T_null) {
            std::cout << "Smallest number >= " << X << " is: " << best->data << std::endl;
        } else {
            std::cout << "No number >= " << X << std::endl;
        }
    }

    void displaySequence(T X, T Y) const override{
        std::cout << "Numbers in range [" << X << ", " << Y << "]: ";
        printInRange(root, X, Y);
        std::cout << std::endl;
    }

};