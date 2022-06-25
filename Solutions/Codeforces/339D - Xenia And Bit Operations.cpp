#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
 
template <typename T>
using pr = pair<T, T>;
typedef long long ll;
typedef long double ld;
#define ft  first
#define sd  second
#define pb  push_back
#define qIO ios_base::sync_with_stdio(false); cin.tie(0)
 
const int N = 1<<17;
int n, q, st[N<<2];
int pull(bool s, int lv, int rv) {
  return s&1? lv|rv : lv^rv;
}
void upd(int p, int v, bool s=n&1, int i=1, int l=0, int r=(1<<n)-1) {
  if (l == r) return void(st[i] = v);
  int m=(l+r)>>1, ln=i<<1, rn=i<<1|1;
  if (p <= m) upd(p, v, s^1, ln, l, m);
  else upd(p, v, s^1, rn, m+1, r);
  st[i] = pull(s, st[ln], st[rn]);
}
void build(int s=n&1, int i=1, int l=0, int r=(1<<n)-1) {
  if (l == r) return void(cin >> st[i]);
  int m=(l+r)>>1, ln=i<<1, rn=i<<1|1;
  build(s^1, ln, l, m);
  build(s^1, rn, m+1, r);
  st[i] = pull(s, st[ln], st[rn]);
}
 
signed main() {
  qIO;
  cin >> n >> q;
  build();
  for (int p,v,i=0; i<q; ++i) {
    cin >> p >> v; upd(p-1, v);
    cout << st[1] << '\n';
  }
  return 0;
}