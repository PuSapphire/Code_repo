#include <iostream>
#include <algorithm>
using namespace std;

template<typename T> using p = pair<T, T>;
using ll = long long;
using ld = long double;
#define ft  first
#define sd  second
#define pb  push_back
#define QIO ios_base::sync_with_stdio(false); cin.tie(0)

/*  ########  *\
演算法: 平衡二搜樹(Splay, AVL, Treap等)
時間複雜度: O(n log n)

就是單純的資結模板題
\*  ########  */

#include <random>
random_device seed;
mt19937 rng(seed());
struct Node {
    int k, p=rng(), sz=1;
    Node *l, *r;
} *top = 0;
int gs(Node *t) { return t?t->sz:0;}
void pull(Node *t) { if(t) t->sz = 1 + gs(t->l) + gs(t->r); }
void split(Node *t, int k, Node *&l, Node *&r) {
    if (!t) return void(l = r = 0);
    if (t->k >= k) split(t->l, k, l, t->l), r=t;
    else split(t->r, k, t->r, r), l=t;
    pull(t);
}
void merge(Node *&t, Node *l, Node *r) {
    if (!l || !r) return void(t = l? l : r);
    if (l->p > r->p) merge(l->r, l->r, r), t=l;
    else merge(r->l, l, r->l), t=r;
    pull(t);
}
void ins(int v) {
    if (!top) return void(top = new Node{v});
    Node *l, *r;
    split(top, v, l, r);
    merge(r, new Node{v}, r);
    merge(top, l, r);
}
bool del(int v, Node *&t=top) {
    if (!t) return 0;
    if (t->k == v) {
        Node *p = t;
        merge(t, t->l, t->r);
        delete(p);
        return 1;
    }
    bool chk = del(v, (t->k > v)? t->l : t->r);
    if (chk) pull(t);
    return chk;
}
int nth(Node *t, int n) {
    if (gs(t) < n) return -1;
    int lsz = gs(t->l) + 1;
    if (lsz == n) return t->k;
    if (lsz < n) return nth(t->r, n-lsz);
    return nth(t->l, n);
}

signed main() {
    QIO;
    int n, k; cin >> n >> k;
    for (int a, b; n--; ) {
        cin >> a;
        if (a == 1) cin >> b, ins(b);
        else {
            int r = nth(top, k);
            cout << r << '\n';
            del(r);
        }
    }
}