#include <iostream>
using namespace std;

struct Node {
    int key;
    Node *l=0, *r=0;
};

class bst {
    Node *root = 0;
    int len = 0;

    void rotate_r(Node*, Node*);
    void inord(Node*);
    Node *search(int);

    public:
    int size() { return len; }
    void print();
    bool ins(int);
    bool del(int);
    pair<bool, int> find(int);
};



//private
void bst::inord(Node *t) { 
    if (t->l) inord(t->l);
    cout << t->key << ' '; //node->data
    if (t->r) inord(t->r);
}

Node* bst::search(int num) {
    Node *t = root;
    while (t) {
        (t->key < num)?
            t = t->r:
            t = t->l;
        if (t->key == num) break;
    }
    return t;
}

//public
void bst::print() { if(root)inord(root); }

pair<bool, int> bst::find(int key) { 
    Node *t = search(key);
    if (t == 0) return {0, 0};
    else return {1, t->key}; //node->data
};

bool bst::ins(int num) {
    Node *t = root;
    Node *par = 0;
    while (t) {
        par = t;
        if (t->key == num) return 0;
        if (t->key < num) t = t->r;
        else t = t->l;
    }
    ++len;
    t = new Node{num};
    if (!par) 
        this->root = t;
    else 
        (par->key > num)? 
            par->l = t:
            par->r = t;
    return 1;
}

bool bst::del(int num) {
    Node *dt = root;
    Node *par = NULL;
    while (dt) {
        if (dt->key == num) break;
        par = dt;
        (dt->key > num)?
        dt = dt->l:
        dt = dt->r;
    }
    //node not found
    if (dt == NULL) return 0;

    --len;
    //2 children
    if (dt->l && dt->r) { 
        //swap to deleting replacement
        //replace = max in l || min in r
        par = dt;
        Node *replace = dt->l;
        while (replace->r) {
            par = replace;
            replace = replace->r;
        }
        dt->key = replace->key;
        dt = replace;
    }

    //may be NULL
    Node *del = dt -> l; 
    if (!del) del = dt -> r;

    par->l == dt?
        par->l = del:
        par->r = del;

    delete dt;
    return 1;
}
