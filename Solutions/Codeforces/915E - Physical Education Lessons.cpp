
#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std;
 
template <typename T>
using pr = pair<T, T>;
typedef long long ll;
#define ft  first
#define sd  second
#define pb  push_back
#define qIO ios_base::sync_with_stdio(false); cin.tie(0)
 
const int N = 1.5e7;
int n, q, ul, ur, v;
int st[N], ln[N], rn[N], lz[N], rt, mem=0;
 
void push(int idx, int l, int r) {
  if (lz[idx]) {
    if (!ln[idx]) ln[idx] = ++mem;
    if (!rn[idx]) rn[idx] = ++mem;
    
    int m = (l + r) >> 1;
    int lnc = ln[idx], rnc = rn[idx];
 
    lz[lnc] = lz[rnc] = lz[idx];
    st[lnc] = (m-l+1) * (lz[lnc]-1); 
    st[rnc] = (r-m) * (lz[rnc]-1);
 
    lz[idx] = 0;
  }
}
int pull(int v1, int v2) { return v1+v2; }
 
void rupd(int &idx=rt, int l=1, int r=n) {
  if (!idx) idx = ++mem;
  if (ul <= l && ur >= r) {
    st[idx] = (r-l+1) * (v-1);
    lz[idx] = v;
  }
  else {
    push(idx, l, r);
    int m = (l + r) >> 1;
    if (ul <= m) rupd(ln[idx], l, m);
    if (ur > m) rupd(rn[idx], m+1, r);
    st[idx] = pull(st[ln[idx]], st[rn[idx]]);
  }
}
 
signed main() {
  qIO;
  cin >> n >> q;
  while (q--) {
    cin >> ul >> ur >> v;
    v = 3-v; rupd();
    cout << n-st[1] << '\n';
  }
  return 0;
}