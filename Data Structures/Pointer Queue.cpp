#include <iostream>

struct Queue {
    struct Node {
        int v;
        Node *nxt=0;
    } *front=0, *back=0;
    int sz = 0;

    void print() {
        Node *t = this->front;
        for (; t; t=t->nxt) std::cout << t->v << ' ';
    }
    int size() { return sz; }
    void push(int v) {
        ++this->sz;
        if (!front) return void(this->front = this->back = new Node{v});
        Node *tmp = new Node{v, this->front};
        this->front->nxt = this->front;
        front = tmp;
    }
    int pop() {
        if (!sz) throw std::runtime_error("Tried to pop from an empty queue.");
        Node *tmp = this->front; this->front = this->front->nxt;
        int v = tmp->v;
        if (!--sz) this->back = 0;
        delete tmp;
        return v;
    }
};