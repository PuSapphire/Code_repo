
/*  ########  *\
隱式樹堆積 Implicit Treap
時間複雜度: 
    區間更新 = O(log n)
    區間查詢 = O(log n)
資節用途: 更廣的區間操作，缺點是常數大
區間操作如循環位移、區間裁剪、區間反轉等
以區間加值區間和，及一些其他簡單的操作為例

實作方面，split(l, r, i)後l包含[0..i)，r包含[i..n]
\*  ########  */
#include <iostream>
#include <algorithm>
#include <random>
using namespace std;

using ll = long long;

random_device seed;
mt19937 rng(seed());
struct Node {
    ll v, rv, lz=0;
    int sz=1, p=rng();
    Node *l=0, *r=0;
    Node (){};
    Node (ll x) { rv = v = x; }
} *top = 0;
inline ll gs(Node*t) { return t?t->sz:0; } //提取區間大小
inline ll gv(Node*t) { return t?t->rv:0; } //提取區間值
inline void push(Node *t) { //懶標下推
    if (!t || !t->lz) return;
    t->v  += t->lz;
    t->rv += t->lz * t->sz;
    if (t->l) t->l->lz += t->lz;
    if (t->r) t->r->lz += t->lz;
    t->lz = 0;
}
inline void pull(Node *t) { //上拉更新
    if (!t) return;
    push(t->l); push(t->r);
    t->rv = t->v + gv(t->l) + gv(t->r);
    t->sz = 1 + gs(t->l) + gs(t->r);
}
void split(Node *t, Node *&l, Node *&r, ll i, ll cs=0) { //Treap分裂
    if (!t) return void(l = r = 0);
    push(t);
    ll ik = cs + gs(t->l);
    if (ik >= i) split(t->l, l, t->l, i, cs), r=t;
    else split(t->r, t->r, r, i, ik+1), l=t;
    pull(t);
}
void merge(Node *&t, Node *l, Node *r) { //Treap合併
    push(l); push(r);
    if (!l || !r) t = l?l:r;
    else if (l->p > r->p) merge(l->r, l->r, r), t=l;
    else merge(r->l, l, r->l), t=r;
    pull(t);
}


void inorder(Node *t) { //中序，即原陣列
    if (!t) return;
    inorder(t->l);
    cout << t->v << ' ';
    inorder(t->r);
}
void insert(ll v, int i) { //插入
    if (!top) return void(top = new Node(v));
    Node *l, *r;
    split(top, l, r, i);
    merge(r, new Node(v), r);
    merge(top, l, r);
}
ll query(int ql, int qr) { //查詢
    Node *l, *r, *q;
    split(top, l, q, ql); //ql = [ql..n]
    split(q, q, r, qr-ql+1); //ql = [ql..qr]
    ll ans = q->rv;
    merge(r, q, r);
    merge(top, l, r);
    return ans;
}
void rupdate(int ql, int qr, int k) { //更新
    Node *l, *r, *q;
    split(top, l, q, ql);
    split(q, q, r, qr-ql+1);
    q->lz += k;
    merge(r, q, r);
    merge(top, l, r);
}
void cshft(int ql, int qr, int k, char dir='l') { //循環位移
    Node *l, *r, *q, *sl, *sr;
    split(top, l, q, ql);
    split(q, q, r, qr-ql+1); //q包含[ql, qr]

    k = k % q->sz; //繞整圈無意義
    if (k == 0) return;
    if (dir == 'r') k = q->sz - k; //向右k等同於向左sz-k

    split(q, sl, sr, k); //sl含[ql..ql+k)、sr含[ql+k..qr]
    merge(q, sr, sl);
    merge(r, q, r);
    merge(top, l, r);
}
