#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
 
template <typename T>
using pr = pair<T, T>;
typedef long long ll;
#define ft  first
#define sd  second
#define pb  push_back
#define qIO ios_base::sync_with_stdio(false); cin.tie(0)
 
const int N = 1e5+5, M = 1e5+5;
ll dis[N<<3], n, s, v, ql, qr, w;
bool rtos;
 
vector<int> tredx = {-1};
vector<vector<pr<int>>> st(N<<3); //{len, idx}
priority_queue<pr<ll>, vector<pr<ll>>, greater<pr<ll>>> pq;
 
void build(int idx=1, int l=1, int r=n);
void upd(int idx=1, int l=1, int r=n);
void djk();

signed main() {
  qIO; int q, a; cin >> n >> q >> s;
  tredx.reserve(N<<1);
  build();
  for (int i=0; i<q; ++i) {
    cin >> a;
    if (a == 1) {
      cin >> v >> ql >> w;
      if (v == ql) continue;
      st[tredx[v]].pb({w, tredx[ql]+(N<<2)});
    } else {
      rtos = a == 3;
      cin >> v >> ql >> qr >> w;
      if (ql != qr) upd();
      else if (v != ql) {
        if (rtos) st[tredx[ql]].pb({w, tredx[v]+(N<<2)});
        else st[tredx[v]].pb({w, tredx[ql]+(N<<2)});
      }
    }
  }
  djk();

  return 0;
}
 
void build(int idx, int l, int r) {
  if (l == r) { 
    tredx.pb(idx); 
    st[idx+(N<<2)].pb({0, idx});
    //st[idx].pb({0, idx+(N<<2)});
    return; 
  }
  int m = (l+r)>>1, ln = idx<<1, rn = idx<<1|1;
  st[ln].pb({0, idx});
  st[rn].pb({0, idx});
  st[idx+(N<<2)].pb({0, ln+(N<<2)});
  st[idx+(N<<2)].pb({0, rn+(N<<2)});
  build(ln, l, m);
  build(rn, m+1, r);
}
 
void upd(int idx, int l, int r) {
  if (ql <= l && qr >= r) {
    if (!rtos) st[tredx[v]].pb({w, idx+(N<<2)});
    else st[idx].pb({w, tredx[v]+(N<<2)});
  }
  else {
    int m = (l+r)>>1, ln = idx<<1, rn = idx<<1|1;
    if (ql <= m) upd(ln, l, m);
    if (qr > m) upd(rn, m+1, r);
  }
}
 
 
void djk() {
  fill(dis, dis+(N<<3), 9e18);
  dis[tredx[s]] = dis[tredx[s]+(N<<2)] = 0;
  bool T[N<<3] = {};
 
  pq.push({0, tredx[s]});
  while (pq.size()) {
    ll D = pq.top().ft, idx = pq.top().sd; 
    pq.pop(); 
 
    if (T[idx]) continue;
    T[idx] = 1;
    for (auto near : st[idx]) {
      if (T[near.sd]) continue;
      if (dis[near.sd] > near.ft + D) {
        dis[near.sd] = near.ft + D;
        pq.push({dis[near.sd], near.sd});
      }
    }
  }
  for (int i=1; i<=n; ++i) 
    cout << (dis[tredx[i]+(N<<2)] == 9e18? -1 : dis[tredx[i]+(N<<2)]) << ' ';
}
/*
3 5 1
2 3 2 3 17
2 3 2 2 16
2 2 2 3 3
3 3 1 1 12
1 3 3 17

0 28 12 
*/
//1 -> 3[12]
//3 -> 2[16]
//2 -> 3[3]