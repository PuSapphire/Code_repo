#include <iostream>
using namespace std;

int n;
const int MAXN = 1e5+5;
long long st[MAXN<<2], arr[MAXN]; 

int cmb(int a, int b) { return a + b; }

void build(int idx=1, int l=0, int r=n-1) {
  if (l == r) st[idx] = arr[l];
  else {
    int m = (l + r) >> 1;
    build(idx<<1, l, m);
    build(idx<<1|1, m+1, r);
    st[idx] = cmb(st[idx<<1], st[idx<<1|1]);
  }
}

int qry(int ql, int qr, int idx=1, int l=0, int r=n-1) {
	if (ql > r || qr < l)	return 0; //dummy no
  if (ql <= l && qr >= r) return st[idx];
  int m = (l + r) >> 1;
  if (qr <= m) return qry(ql, qr, idx<<1, l, m);
  if (ql > m) return qry(ql, qr, idx<<1|1, m+1, r);
  return cmb(qry(ql, qr, idx<<1, l, m), qry(ql, qr, idx<<1|1, m+1, r));
}

void upd(int p, int v, int idx=1, int l=0, int r=n-1) {
  if (l == r) st[idx] = v;
  else {
    int m = (l + r) >> 1;
    if (p <= m) upd(p, v, idx<<1, l, m);
    else upd(p, v, idx<<1|1, m+1, r);
    st[idx] = cmb(st[idx<<1], st[idx<<1|1]);
  }
}
