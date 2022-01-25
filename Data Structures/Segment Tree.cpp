#include <iostream>
using namespace std;

const int N = 1e5+5;
int n, st[N<<2], lz[N<<2], arr[N]; 

int pull(int a, int b) { 
  return min(a, b); 
}
void push(int idx, int l, int r) {
  if (lz[idx] != -1) {
    int m=(l+r)>>1, ln=idx<<1, rn=idx<<1|1;
    lz[ln] = lz[rn] = lz[idx];
    st[ln] = (r-l+1) * lz[ln];
    st[rn] = (r-m) * lz[rn];
    lz[idx] = -1;
  }
}

void build(int idx=1, int l=0, int r=n-1) {
  if (l == r) st[idx] = arr[l];
  else {
    int m=(l+r)>>1, ln=idx<<1, rn=idx<<1|1;
    build(ln, l, m); build(rn, m+1, r);
    st[idx] = pull(st[ln], st[rn]);
  }
}

int qry(int ql, int qr, int idx=1, int l=0, int r=n-1) {
  if (l != r) push(idx, l, r);
  if (ql > r || qr < l) return 2e9;
  if (ql <= l && qr >= r) return st[idx];
  int m=(r+l)>>1, ln=idx<<1, rn=idx<<1|1;
  if (qr <= m) return qry(ql, qr, ln, l, m);
  if (ql > m) return qry(ql, qr, rn, m+1, r);
  return pull(qry(ql, qr, ln, l, m), qry(ql, qr, rn, m+1, r));
}

void upd(int p, int v, int idx=1, int l=0, int r=n-1) {
  if (l == r) st[idx] = v;
  else {
    int m=(l+r)>>1, ln=idx<<1, rn=idx<<1|1;
    if (p <= m) upd(p, v, ln, l, m);
    else upd(p, v, rn, m+1, r);
    st[idx] = pull(st[ln], st[rn]);
  }
}

void rupd(int ql, int qr, int v, int idx=1, int l=0, int r=n-1) {
  if (ql <= l && qr >= r) {
    st[idx] = (r-l+1) * v;
    lz[idx] = v;
  }
  else {
    push(idx, l, r);
    int m=(l+r)>>1, ln=idx<<1, rn=idx<<1|1;
    if (ql <= m) rupd(ql, qr, ln, l, m);
    if (qr > m) rupd(ql, qr, rn, m+1, r);
    st[idx] = pull(st[ln], st[rn]);
  }
}
 
