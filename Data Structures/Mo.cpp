#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;
 
template <typename T> using pr = pair<T, T>;
#define ft  first
#define sd  second
#define pb  push_back

//Ex. find mode(number of most occurences)
const int N = 1e5+5, S = sqrt(N);
int n, q, arr[N];
pr<int> sol[N];
int frq[N], cnt[N], mode; //frq of x; count of frq = x

struct QRY {
  int l, r, lb, idx; //lb -> block of left
  QRY(){};
  QRY(int a, int b, int c, int d): l(a),r(b),lb(c),idx(d){};
  bool operator< (const QRY &o) const {
    if (lb == o.lb) return lb&1? r<o.r : r>o.r; //parity sort
    return lb < o.lb;
  }
};
vector<QRY> qry;

inline void inc(int v) { //operation when increasing range
  --cnt[frq[v]];
  ++frq[v];
  ++cnt[frq[v]];
  if(cnt[frq[v]] == 1) mode = max(mode, frq[v]);
}
inline void dec(int v) { //operation when decreasing range
  --cnt[frq[v]];
  --frq[v];
  ++cnt[frq[v]];
  if(mode==frq[v]+1 && !cnt[frq[v]+1]) mode = frq[v];
}
inline pr<int> ans() { //operation when retrieving answer
  return {mode, cnt[mode]};
}

signed main() {
  cin >> n >> q;
  for (int i=1; i<=n; ++i) cin >> arr[i];
  for (int l,r,i=0; i<q; ++i) {
    cin >> l >> r; 
    qry.pb(QRY(l, r, l/S, i));
  }
  sort(qry.begin(), qry.end());
  cnt[0] = n;
  int cl=1, cr=0;
  for (auto q : qry) {
    while (cl > q.l) --cl, inc(arr[cl]);
    while (cl < q.l) dec(arr[cl]), ++cl;
    while (cr > q.r) dec(arr[cr]), --cr;
    while (cr < q.r) ++cr, inc(arr[cr]);
    sol[q.idx] = ans();
  }
  for (int i=0; i<q; ++i) 
    cout << sol[i].ft << ' ' << sol[i].sd << '\n';
  return 0;
}

