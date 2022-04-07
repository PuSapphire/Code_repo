#include <iostream>
#include <algorithm>
#include <random>
using namespace std;

random_device seed;
mt19937 mt(seed());

struct node {
  int k, p, len=1;
  bool rev = 0;
  node *l, *r;
  node (int x) {
    k = x; p = mt();
    l = r = 0;
  }
} *top = 0;
int sz(node *n) { return n? n->len : 0; }
void upd(node *t) { if(t) t->len = 1 + sz(t->l) + sz(t->r); }

void split(node *t, node *&l, node *&r, int k) {
  if (!t) return void(l = r = 0);
  if (t->k >= k) split(t->l, l, t->l, k), r=t;
  else split(t->r, t->r, r, k), l=t;
  upd(t);
}
void merge(node *&t, node *l, node *r) {
  if (!l) t = r; else if (!r) t = l;
  else if (l->p > r->p) merge(l->r, l->r, r), t=l;
  else merge(r->l, l, r->l), t=r;
  upd(t);
}
void ins(int v) {
  if (!top) return void(top = new node(v));
  node *l, *r;
  split(top, l, r, v);
  merge(r, new node(v), r); merge(top, l, r);
}
bool del(node *&t, int k) {
  if (!t) return 0;
  if (t->k == k) {
    node *path = t;
    merge(t, t->l, t->r);
    delete path;
    return 1;
  }
  bool b = del((t->k > k)? t->l : t->r, k);
  if (b) upd(t); return b;
}
int kth(node *t, int k) {
  if (!t) return -1;
  int lsz = sz(t->l)+1;
  if (lsz == k) return t->k;
  if (lsz < k) return kth(t->r, k-lsz);
  return kth(t->l, k);
}
int range(int q, int k) {
  node *t;
  split(top, t, top, k);
  int ans = sz(t);
  if (q == 1) ins(k + ans);
  merge(top, t, top);
  return ans;
}

signed main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  int n, k; cin >> n >> k;
  for (int a, b; n--;) {
    cin >> a;
    if (a == 1) cin >> b, ins(b);
    else {
      int r = kth(top, k);
      cout << r << '\n';
      del(top, r);
    }
  }
  return 0;
}
