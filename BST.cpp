#include <iostream>
using namespace std;

struct tnode {
    int key;
    tnode *l = NULL;
    tnode *r = NULL;
    tnode (int num) { key = num; }
};

class bst {
    tnode *root = NULL;
    int len = 0;

    void rotate_r(tnode*, tnode*);
    void inord(tnode*);
    tnode *search(int);

    public:
    int size() { return len; }
    void print();
    bool ins(int);
    bool del(int);
    pair<bool, int> find(int);
};



//private
void bst::inord(tnode *node) { 
    if (node->l) inord(node->l);
    cout << node->key << ' '; //node->data
    if (node->r) inord(node->r);
}

tnode* bst::search(int num) {
    tnode *node = root;
    while (node) {
        (node->key < num)?
        node = node->r:
        node = node->l;
        if (node->key == num) break;
    }
    return node;
}

//public
void bst::print() { if(root)inord(root); }

pair<bool, int> bst::find(int key) { 
    tnode *node = search(key);
    if (node == NULL) return {0, 0};
    else return {1, node->key}; //node->data
};

bool bst::ins(int num) {
    tnode *node = root;
    tnode *par = 0;
    while (node) {
        par = node;
        if (node->key == num) return 0;
        if (node->key < num) node = node->r;
        else node = node->l;
    }
    ++len;
    node = new tnode(num);
    if (!par) 
        this->root = node;
    else 
        (par->key > num)? 
        par->l = node:
        par->r = node;
    return 1;
}

bool bst::del(int num) {
    tnode *del_node = root;
    tnode *par = NULL;
    while (del_node) {
        if (del_node->key == num) break;
        par = del_node;
        (del_node->key > num)?
        del_node = del_node->l:
        del_node = del_node->r;
    }
    //node not found
    if (del_node == NULL) return 0;

    --len;
    //2 children
    if (del_node->l && del_node->r) { 
        //swap to deleting replacement
        //replace = max in l || min in r
        par = del_node;
        tnode *replace = del_node->l;
        while (replace->r) {
            par = replace;
            replace = replace->r;
        }
        del_node->key = replace->key;
        del_node = replace;
    }

    //may be NULL
    tnode *del = del_node -> l; 
    if (!del) del = del_node -> r;

    par->l == del_node?
    par->l = del:
    par->r = del;

    delete del_node;
    return 1;
}
