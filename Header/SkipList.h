#include "Structure.h"
#include <random>

template <typename t>
class Skiplist : public Structure<t>{
private:
    class Node;

public:
    Skiplist() {
        random_engine.seed(std::random_device()());
        head = nullptr;
        this->insert(-inf);
    }

    void search(t target) override{
        if (head == nullptr) return;
        Node* p = findNode(target);
        bool found = p->val == target;
    }

    void insert(t num) override {
        if (head == nullptr) {
            head = new Node(num);
            level = 1;
            return;
        }

        Node* p = findNode(num);
        Node* q = new Node(num);
        int i = 1;
        add(p, q);
        while (coinflip()) {
            i = i + 1;
            if (i > level) {
                level = level + 1;
                createNewLevel();
            }
            while (p->up == nullptr) {
                p = p->prev;
            }
            p = p->up;
            Node* new_q = new Node(num);
            new_q->bottom = q;
            q->up = new_q;
            q = new_q;
            add(p, q);
        }
    }

    void remove(t num) override {
        Node* p = findNode(num);
        if (p == nullptr || p->val != num) return;
        while (true) {
            p->prev->next = p->next;
            if (p->next != nullptr) p->next->prev = p->prev;
            if (p->up == nullptr) break;
            p = p->up;
            delete p->bottom;
            p->bottom = nullptr;
        }
    }

private:
    class Node{
    public:

        explicit Node(t _val) {
            this->val = _val;
            this->prev = nullptr;
            this->next = nullptr;
            this->up = nullptr;
            this->bottom = nullptr;
        }

        Node(t _val, Node* _prev, Node* _next, Node* _up, Node* _bottom) {
            this->val = _val;
            this->prev = _prev;
            this->next = _next;
            this->up = _up;
            this->bottom = _bottom;
        }

        Node* prev;
        Node* next;
        Node* up;
        Node* bottom;
        int val;
    };

    bool coinflip() {
        std::uniform_int_distribution<int> dist(0, 1);
        return dist(random_engine) == 0;
    }

    Node* findNode(t target) {
        if (head == nullptr) return nullptr;
        Node* p = head;
        while (p->bottom != nullptr) {
            p = p->bottom;
            while (p->next != nullptr && target >= p->next->val) {
                p = p->next;
            }
        }
        while (p->next != nullptr && target >= p->next->val) {
            p = p->next;
        }
        return p;
    }

    void createNewLevel() {
        Node* new_topleft = new Node(head->val);
        new_topleft->bottom = head;
        head->up = new_topleft;
        head = new_topleft;
    }

    void add(Node* a, Node* b) {
        // insert b after a
        b->next = a->next;
        if (a->next != nullptr) a->next->prev = b;
        a->next = b;
        b->prev = a;
    }

    Node* head;
    int level;
    const int inf = (1<<30);
    std::mt19937 random_engine;
};