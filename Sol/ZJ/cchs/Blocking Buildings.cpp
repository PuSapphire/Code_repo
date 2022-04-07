//Source: NCTU PCCA
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

template<typename T>
using p = pair<T, T>;
typedef long long ll;
#define ft  first
#define sd  second
#define pb  push_back
#define qIO ios_base::sync_with_stdio(false); cin.tie(0)

const int sz = 2e5+1;
int n, q;
vector<int> st[sz<<2];
inline int R();
void build(int idx=1, int l=1, int r=n);
int qry(int ql, int qr, int k, int idx=1, int l=1, int r=n);

signed main() {
  qIO;
  n = R(); q = R();
  //for (int i=1; i<=n; ++i) cin >> arr[i];
  
  build();
  for (int l, r, k; q--; ) {
    l = R(); r = R(); k = R();
    cout << qry(l, r, k) << '\n';
  }
  return 0;
}

inline int R() {
  int x = 0, c = getchar_unlocked();
  while (('0' > c || c > '9') && c != EOF) c = getchar_unlocked();
  for (; '0'<=c && c<='9'; c=getchar_unlocked()) x = x*10 + (c^'0');
  return x;
}
void build(int idx, int l, int r) {
  if (l == r) st[idx] = { R() };
  else {
    int m = (l + r) >> 1;
    build(idx<<1, l, m);
    build(idx<<1|1, m+1, r);
    int j=0, k=0;
    st[idx].resize(st[idx<<1].size() + st[idx<<1|1].size());
    for (int i=0; i<st[idx<<1].size(); ++i) {
      while (j < st[idx<<1|1].size() && st[idx<<1|1][j] < st[idx<<1][i])
        st[idx][k++] = st[idx<<1|1][j++];
      st[idx][k++] = st[idx<<1][i];
    }
    while (j<st[idx<<1|1].size()) st[idx][k++] = st[idx<<1|1][j++];
  }
}
int qry(int ql, int qr, int k, int idx, int l, int r) {
  if (ql > r || qr < l) return 0;
  if (ql <= l && qr >= r) 
    return upper_bound(st[idx].begin(), st[idx].end(), k) - st[idx].begin();
  int m = (l + r) >> 1;
  if (qr <= m) return qry(ql, qr, k, idx<<1, l, m);
  if (ql > m)  return qry(ql, qr, k, idx<<1|1, m+1, r);
  return qry(ql, qr, k, idx<<1, l, m) + qry(ql, qr, k, idx<<1|1, m+1, r);
}
