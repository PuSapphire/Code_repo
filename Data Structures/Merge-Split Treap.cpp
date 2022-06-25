
/*  ########  *\
無旋式樹堆積 Merge-Split Treap
時間複雜度: 平衡二搜樹
資節用途: 平衡二搜樹
\*  ########  */
#include <iostream>
#include <algorithm>
#include <random>
using namespace std;

using ll = long long;

random_device seed;
mt19937 rng(seed());
struct Node {
    ll k;
    int sz=1, p=rng();
    Node *l=0, *r=0;
} *top = 0;
inline ll gs(Node*t) { return t?t->sz:0; } //提取樹大小
inline void pull(Node *t) { if(t) t->sz = 1 + gs(t->l) + gs(t->r); }
void split(Node *t, Node *&l, Node *&r, ll k) { //Treap分裂
    if (!t) return void(l = r = 0);
    if (t->k >= k) split(t->l, l, t->l, k), r=t;
    else split(t->r, t->r, r, k), l=t;
}
void merge(Node *&t, Node *l, Node *r) { //Treap合併
    if (!l || !r) t = l?l:r;
    else if (l->p > r->p) merge(l->r, l->r, r), t=l;
    else merge(r->l, l, r->l), t=r;
    pull(t);
}


void inorder(Node *t) { //中序，即排序後陣列
    if (!t) return;
    inorder(t->l);
    cout << t->k << ' ';
    inorder(t->r);
}
void insert(ll v, int i) { //插入
    if (!top) return void(top = new Node{v});
    Node *l, *r;
    split(top, l, r, i);
    merge(r, new Node{v}, r);
    merge(top, l, r);
}
bool dels(Node *&t, ll v) { //若有多個k=v，只刪除一個
    if (!t) return 0;
    if (t->k == v) {
        Node *path = t;
        merge(t, t->l, t->r);
        delete path;
        return 1;
    }
    bool b = dels((t->k > v)? t->l : t->r, v);
    if (b) pull(t); return b;
}
bool del(Node *&t, ll v) { //刪除所有k=v
    Node *l, *r, *q;
    split(top, l, q, v);
    split(q, q, r, v+1);
    merge(top, l, r);
    delete q;
}
ll kth(Node *t, int k) { //第k大
    if (!t) return -1;
    int lsz = gs(t->l) + 1;
    if (lsz == k) return t->k;
    if (lsz < k) return kth(t->r, k-lsz);
    return kth(t->l, k);
}