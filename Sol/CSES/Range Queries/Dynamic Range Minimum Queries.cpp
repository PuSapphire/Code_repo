#include <iostream>

using namespace std;
#define qIO ios_base::sync_with_stdio(false); cin.tie(0)
const int MAXN = 2e5;
int sT[4 * MAXN+5], arr[MAXN+5];
void build(int idx, int l, int r);
int qry(int ql, int qr, int idx, int l, int r);
void upd(int pos, int idx, int l, int r, int v);

int main() {
  qIO;
  int n, q;
  cin >> n >> q;
  for (int i=0; i<n; i++) cin >> arr[i];
  build(1, 0, n-1);
  for (int i=0, a, l, r; i<q; i++) {
    cin >> a >> l >> r;
    if (a == 1) upd(l-1, 1, 0, n-1, r);
    else cout << qry(l-1, r-1, 1, 0, n-1) << '\n';
  }
  return 0;
}

void build(int idx, int l, int r) {
  if (l == r) sT[idx] = arr[l];
  else {
    int m = (l + r) >> 1;
    build(idx<<1, l, m);
    build(idx<<1|1, m+1, r);
    sT[idx] = min(sT[idx<<1], sT[idx<<1|1]);
  }
}

int qry(int ql, int qr, int idx, int l, int r) {
  //if (qr < l || ql > r) return 1e9;
  if (ql <= l && qr >= r) return sT[idx];
  int m = (l + r) >> 1;
  if (qr <= m) return qry(ql, qr, idx<<1, l, m);
  if (ql > m) return qry(ql, qr, idx<<1|1, m+1, r);
  return min(qry(ql, qr, idx<<1, l, m), qry(ql, qr, idx<<1|1, m+1, r));
}

void upd(int pos, int idx, int l, int r, int v) {
  if (l == r) {sT[idx] = v; return;}
  int m = (l + r) >> 1;
  if (pos <= m) upd(pos, idx<<1, l, m, v);
  else upd(pos, idx<<1|1, m+1, r, v);
  sT[idx] = min(sT[idx<<1], sT[idx<<1|1]);
}
