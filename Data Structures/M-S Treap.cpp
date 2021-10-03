#include <random>
#include <bitset>
using namespace std;
 
bitset<int(1e7)> set;
default_random_engine DRE;
uniform_int_distribution<int> gen(1, 1e7);

struct node {
  int p, k, len=1;
  node *l, *r;
  node (int s) {
    k = s; l = r = NULL;
    do { p = gen(DRE); } while (set[p]);
    set[p] = 1;
  }
} *top=NULL;

int sz(node *n) { return n ? n->len : 0; }
void upd(node *t) { if(t) t->len = 1+sz(t->l)+sz(t->r); }

void split(node *t, int k, node *&l, node *&r) {
  if (!t) l = r = NULL;
  else if (t->k > k)
    split(t->l, k, l, t->l), r=t, upd(r);
  else 
    split(t->r, k, t->r, r), l=t, upd(l);
}
void merge(node *&t, node *l, node *r) {
  if (!l) t = r;
  else if (!r) t = l;
  else if (l->p > r->p) merge(l->r, l->r, r), t=l;
  else merge(r->l, l, r->l), t=r;
  upd(t);
}
void ins(node *&t, node *it) {
  if (!t) t = it;
  else if (t->p < it->p) split(t, it->k, it->l, it->r), t=it;
  else ins((t->k > it->k)? t->l : t->r, it);
  upd(t);
}
bool del(node *&t, int k) {
  if (!t) return 0;
  if (t->k == k) {
    node *path = t;
    merge(t, t->l, t->r);
    set[path->p] = 0;
    delete path;
    return 1;
  }
  bool b = del((t->k > k)? t->l : t->r, k);
  if (b) upd(t); return b;
}
int kth(node *t, int k) {
  if (!t) return -1;
  int lsz = sz(t->l) + 1;
  if (lsz == k) return t->k;
  if (lsz < k) return kth(t->r, k-lsz);
  return kth(t->l, k);
}
