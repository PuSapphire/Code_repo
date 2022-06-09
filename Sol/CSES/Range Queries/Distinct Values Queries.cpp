#pragma GCC optimize("O3", "unroll-loops")
#pragma GCC target("avx2")

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>
using namespace std;
 
template <typename T> using pr = pair<T, T>;
template <typename T> using maxh = priority_queue<T>;
template <typename T> using minh = priority_queue<T, vector<T>, greater<T>>;
typedef long long ll;
typedef long double ld;
#define ft  first
#define sd  second
#define pb  push_back
#define qIO ios_base::sync_with_stdio(false); cin.tie(0)

const int N = 2e5+5;
int n, q, arr[N], bit[N], sol[N];
map<int, int> lst;
void upd(int i, int v) {
  for (; i<=n; i+=i&-i) bit[i] += v;
}
int qry(int i) {
  int s = 0;
  for (; i; i-=i&-i) s += bit[i];
  return s;
}
struct QRY {
  int l, r, idx;
};
vector<vector<pr<int>>> query(N);

signed main() {
  qIO;
  cin >> n >> q;
  for (int i=0; i<n; ++i) cin >> arr[i];
  for (int l,r,i=0; i<q; ++i)
    cin >> l >> r, query[l].pb({r, i});
  for (int i=n; i>0; --i) {
    int v = arr[i-1];
    if (lst[v]) upd(lst[v], -1);
    lst[v] = i;
    upd(i, 1);
    for (auto q : query[i])
      sol[q.sd] = qry(q.ft);
  }
  for (int i=0; i<q; ++i) cout << sol[i] << '\n';
  return 0;
}

