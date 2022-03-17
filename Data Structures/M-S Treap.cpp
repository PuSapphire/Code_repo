#include <random>
using namespace std;
 
random_device seed;
mt19937 mt(seed());

struct node {
  int p, k, len=1;
  node *l, *r;
  node (int s) {
    k = s; l = r = NULL;
    p = mt();
  }
} *top=NULL;

int sz(node *n) { return n ? n->len : 0; }
void pull(node *t) { if(t) t->len = 1+sz(t->l)+sz(t->r); }

void cut(node *t, int k, node *&l, node *&r) {
  if (!t) l = r = NULL;
  else if (t->k > k)
    cut(t->l, k, l, t->l), r=t, pull(r);
  else 
    cut(t->r, k, t->r, r), l=t, pull(l);
}
void tie(node *&t, node *l, node *r) {
  if (!l) t = r;
  else if (!r) t = l;
  else if (l->p > r->p) tie(l->r, l->r, r), t=l;
  else tie(r->l, l, r->l), t=r;
  pull(t);
}
void ins(node *&t, node *it) {
  if (!t) t = it;
  else if (t->p < it->p) split(t, it->k, it->l, it->r), t=it;
  else ins((t->k > it->k)? t->l : t->r, it);
  pull(t);
}
bool del(node *&t, int k) {
  if (!t) return 0;
  if (t->k == k) {
    node *path = t;
    tie(t, t->l, t->r);
    delete path;
    return 1;
  }
  bool b = del((t->k > k)? t->l : t->r, k);
  if (b) pull(t); return b;
}
int kth(node *t, int k) {
  if (!t) return -1;
  int lsz = sz(t->l) + 1;
  if (lsz == k) return t->k;
  if (lsz < k) return kth(t->r, k-lsz);
  return kth(t->l, k);
}
