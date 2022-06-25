#include <iostream>
#include <algorithm>
#include <random>
using namespace std;
 
random_device seed;
mt19937 mt(seed());
 
struct node {
  int v, p, len=1;
  bool rev = 0;
  node *l, *r;
  node (int x) {
    v = x; p = mt(); 
    l = r = 0;
  }
} *top=0;
 
int sz(node *n) { return n ? n->len : 0; }
void upd(node *t) { if(t) t->len = 1 + sz(t->l) + sz(t->r); }
void push(node *&t) {
  if (!t) return;
  if (t->rev) swap(t->l, t->r);
  if (t->l) t->l->rev ^= t->rev;
  if (t->r) t->r->rev ^= t->rev;
  t->rev = 0;
}
 
void split(node *t, node *&l, node *&r, int idx, int cs=0) {
  if (!t) return void(l = r = NULL);
  push(t);
  int ik = cs + sz(t->l);
  if (ik >= idx)
    split(t->l, l, t->l, idx, cs), r=t;
  else
    split(t->r, t->r, r, idx, ik+1), l=t;
  upd(t);
}
void merge(node *&t, node *l, node *r) {
  push(l); push(r);
  if (!l) t = r;
  else if (!r) t = l;
  else if (l->p > r->p) merge(l->r, l->r, r), t=l;
  else merge(r->l, l, r->l), t=r;
  upd(t);
}
 
void ins(int v, int idx) {
  if (!top) return void(top = new node(v));
  node *l, *r;
  split(top, l, r, idx);
  merge(r, new node(v), r); merge(top, l, r);
}
 
int pos_v(int idx) { //get val at pos idx
  if (idx < 0 || idx > sz(top)) return -1;
  node *l, *r, *m;
  split(top, l, r, idx);
  split(r, m, r, 1);
  int ans = m? m->v : -1;
 
  merge(r, m, r); merge(top, l, r);
  return ans;
}
void reverse(int ql, int qr) {
  node *l, *r, *m;
  split(top, l, r, ql);
  split(r, m, r, qr-ql+1);
 
  m->rev ^= 1;
  merge(r, m, r); merge(top, l, r);
}
void shift(int ql, int qr, int k) { 
  if (ql == qr) return;
  int range = qr - ql + 1;
  k %= range;
 
  node *l, *r, *m, *sl, *sr;
  split(top, l, r, ql);
  split(r, m, r, range); 
 
  split(m, sr, sl, range - k);
  merge(m, sl, sr);
 
  merge(r, m, r); merge(top, l, r);
}
 
signed main() {
  int n, m, q; cin >> n >> m >> q;
  for (int x, i=0; i<n; ++i) cin >> x, ins(x, i);
  for (int l, r, k; m--; ) {
    cin >> k >> l >> r; --l; --r;
    if (k == 2) reverse(l, r);
    else shift(l, r, 1);
  }
  for (int x; q--; ) {
    cin >> x; cout << pos_v(--x) << ' ';
  }
  return 0;
}