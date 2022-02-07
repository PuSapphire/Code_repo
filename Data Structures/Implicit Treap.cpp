#include <iostream>
#include <algorithm>
#include <random>
using namespace std;

random_device seed;
mt19937 mt(seed());
typedef long long ll;

struct node {
  ll v, p, len=1;
  ll mn; 
  ll lz = 9e18;
  node *l, *r;
  node (ll x) {
    v = mn = x; p = mt();
    l = r = 0;
  }
} *top = 0; 

int sz(node *t) { return t ? t->len : 0; }
ll nv(node *t) { return t ? t->v : 9e18;}
void pull(node *t) {
  if (!t) return;
  t->mn = min(t->mn, min(nv(t->l), nv(t->r)));
  t->len = 1 + sz(t->l) + sz(t->r);
}
void push(node *t) {
  if (!t || t->lz == 9e18) return;
  t->mn = min(t->mn, t->lz);
  if (t->l) t->l->lz = min(t->l->lz, t->lz);
  if (t->r) t->r->lz = min(t->r->lz, t->lz);
  t->lz = 9e18;
}

void cut(node *t, node *&l, node *&r, int idx, int cs=0) {
  push(t);
  if (!t) return void(l = r = 0);
  int ik = cs + sz(t->l);
  if (idx <= ik) {
    cut(t->l, l, t->l, idx, cs);
    r = t; pull(r);
  } else {
    cut(t->r, t->r, r, idx, ik+1);
    l = t; pull(l);
  }
}
void tie(node *&t, node *l, node *r) {
  push(l); push(r);
  if (!l) t = r;
  else if (!r) t = l;
  else if (l->p > r->p) tie(l->r, l->r, r), t=l;
  else tie(r->l, l, r->l), t=r;
  pull(t);
}

void ins(ll v, int idx) {
  if (!top) return void(top = new node(v));
  node *l, *r;
  cut(top, l, r, idx);
  tie(r, new node(v), r);
  tie(top, l, r);
}
void inord(node *t) {
  if (!t) return;
  inord(t->l);
  cout << t->v << ' ';
  inord(t->r);
}
int qry(int ql, int qr) {
  if (ql > qr) return -1;
  node *l, *r, *m;
  cut(top, l, m, ql);
  cut(m, m, r, qr-ql+1);
  cout << "RMQ on [ "; inord(m); cout << "]: ";
  int ans = m->mn;
  tie(r, m, r);
  tie(top, l, r);
  return ans;
}

signed main() {
  for (int i=0; i<10; ++i) ins(i, i);
  inord(top); cout << '\n';
  cout << qry(5, 8);
  return 0;
}
