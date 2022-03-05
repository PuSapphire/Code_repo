#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
 
template <typename T> using pr = pair<T, T>;
typedef long long ll;
typedef long double ld;
#define ft  first
#define sd  second
#define pb  push_back
#define qIO ios_base::sync_with_stdio(false); cin.tie(0)
 
//Ex. CSES - Path Queries II
int n, q, ptr;
vector<vector<int>> adj;
//"jumping" to another chain:
//move to top, then to par, thus par[top[i]]
class HLD {
  //hvy[i] = heavy subtree[i];
  //top[i] = top of chain i belongs to
  //ti = depth-first index = tree index
  vector<int> par, dep, hvy, top, ti, st;
  vector<int> val; //values of nodes
 
//segtree functions
  void tu(int p, int v, int idx=1, int l=1, int r=n) {
    if (l == r) return void(st[idx] = v);
    int m=(l+r)>>1, ln=idx<<1, rn=idx<<1|1;
    (p <= m)? tu(p,v,ln,l,m) : tu(p,v,rn,m+1,r);
    st[idx] = max(st[ln], st[rn]);
  }
  int tq(int ql, int qr, int idx=1, int l=1, int r=n) {
    if (ql > r || qr < l) return -1;
    if (ql <= l && qr >= r) return st[idx];
    int m=(l+r)>>1, ln=idx<<1, rn=idx<<1|1;
    if (qr <= m) return tq(ql,qr,ln,l,m);
    if (ql > m) return tq(ql,qr,rn,m+1,r);
    return max(tq(ql,qr,ln,l,m), tq(ql,qr,rn,m+1,r));
  }
//segtree functions end
 
//decomposition
  int dfs(int v) { //decide par, hvy, dep
    int sz=1, max_subsz=0;
    for (int const& sub : adj[v]) {
      if (sub == par[v]) continue;
      par[sub] = v;
      dep[sub] = dep[v] + 1;
      int subsz = dfs(sub);
      sz += subsz;
      if (subsz > max_subsz) max_subsz = subsz, hvy[v] = sub;
    }
    return sz;
  }
  void decomp(int v, int t) { //decide top and st mapping
    top[v] = t; ti[v] = ++ptr;
    tu(ti[v], val[v]);
    if (hvy[v] == -1) return;
//decomp this first to ensure indices are continuous
    decomp(hvy[v], t);
    for (int const& sub : adj[v]) {
      if (sub == par[v] || sub == hvy[v]) continue;
      decomp(sub, sub);
    }
  }
 
public:
  HLD(int n, int rt) {
    ptr = 0;
    adj.resize(n+5);
    par = dep = top = ti = val = vector<int>(adj.size());
    for (int i=1; i<=n; ++i) cin >> val[i];
    for (int a,b,i=1; i<n; ++i) {
      cin >> a >> b;
      adj[a].pb(b); adj[b].pb(a);
    }
    st.resize(adj.size()<<3, 0);
    hvy.assign(adj.size(), -1);
    dfs(rt); decomp(rt, rt);
  }
  void upd(int p, int v) { tu(ti[p], v); }
  int qry(int a, int b) {
    int res = 0;
    for(; top[a] != top[b]; b = par[top[b]]) {
      if (dep[top[a]] > dep[top[b]]) swap(a, b);
      res = max(res, tq(ti[top[b]], ti[b]));
    }
    if (dep[a] > dep[b]) swap(a, b);
    return max(res, tq(ti[a], ti[b]));
  }
};
 
signed main() {
  qIO;
  cin >> n >> q;
  HLD hld(n, 1);
  for (int a,b,c,i=0; i<q; ++i) {
    cin >> a >> b >> c;
    if (a == 1) hld.upd(b, c);
    else cout << hld.qry(b, c) << ' ';
  }
  return 0;
}
