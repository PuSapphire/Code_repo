#include <iostream>
#include <algorithm>
using namespace std;
 
template <typename T>
using pr = pair<T, T>;
typedef long long ll;
typedef long double ld;
#define ft  first
#define sd  second
#define pb  push_back
#define qIO ios_base::sync_with_stdio(false); cin.tie(0)
 
//dp[i] := min cut tree[i]
//dp[i] = min_{j<i}(a[i]*b[j] + dp[j])
const int N = 1e5+5;
struct lin {
  ll m, c;
  lin(): m(0), c(1e18) {};
  lin(ll a, ll b): m(a), c(b){};
  ld operator() (ll x) { return ld(m)*x + c; }
};
struct node {
  lin line;
  ll l=0, r=0;
  node() {};
  node(ll a, ll b): l(a), r(b) {};
  ld operator() (ll x) { return line(x); }
};
 
ll n, rt, mem=0, a[N], b[N], dp[N];
node st[N<<4];
 
void upd(lin f, ll &idx=rt, ll l=0, ll r=1e18) {
  if (!idx) idx = ++mem;
  ll m = (l + r) >> 1;
  bool lb = f(l) < st[idx](l), mb = f(m) < st[idx](m);
  if (mb) swap(st[idx].line, f);
  if (l+1 == r) return;
  if (mb != lb) upd(f, st[idx].l, l, m);
  else upd(f, st[idx].r, m, r);
}
 
ll qry(int x, int idx=rt, ll l=0, ll r=1e18) {
  if (!idx) return 1e18;
  if (l+1 == r) return st[idx].line(x);
  ll m = (l + r) >> 1;
  if (x < m) return min(st[idx](x), ld(qry(x, st[idx].l, l, m)));
  return min(st[idx](x), ld(qry(x, st[idx].r, m, r)));
}
 
signed main() {
  qIO;
  cin >> n;
  for (int i=0; i<n; ++i) cin >> a[i];
  for (int i=0; i<n; ++i) cin >> b[i];
 
  dp[0] = 0; upd(lin(b[0], 0));
  for (int i=1; i<n; ++i) {
    dp[i] = qry(a[i]);
    upd(lin(b[i], dp[i]));
  }
 
  cout << dp[n-1];
  return 0;
}