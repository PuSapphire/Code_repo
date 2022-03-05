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
 
const int N = 2e5+5;
 
//Ex. QTREE - SPOJ
 
//"jumping" to an upper chain from u:
//move u to chain top(top[u]), then move to parent of that node
//thus: par[top[u]] 
 
//node stores weight to parent
int ptr;
struct EDGE { int w, to, ord; };
vector<vector<EDGE>> adj;
class HLD {
//ti, oi -> depth-first idx && oi[ti[v]] = v
//hvy[i] -> heavy sub of i
//top[i] -> top of chain i belongs to
//cst[i] -> cost(i->par[i])
//eton[i] -> point to node storing weight of ith edge
  vector<int> par, cst, eton, dep, hvy, top, ti, oi;
  vector<int> st;
 
//decomposition core
  int dfs(int v) { //decide par, hvy, top
    int sz=1, max_subsz=0;
    for (EDGE const &E : adj[v]) {
      int w = E.w, sub = E.to, ord = E.ord;
      if (sub == par[v]) continue;
      par[sub] = v; 
      cst[sub] = w; 
      eton[ord] = sub;
      dep[sub] = dep[v]+1;
      int subsz = dfs(sub);
      sz += subsz;
      if (subsz > max_subsz) max_subsz = subsz, hvy[v] = sub;
    }
    return sz;
  }
  void decomp(int v, int h) { //deciding tops and mapping to st
    top[v] = h; ti[v] = ++ptr; oi[ti[v]] = v;
  //decomp hvysub first for continuous indexing in same chain
    if (hvy[v] != -1) decomp(hvy[v], h);
    for (EDGE const &E : adj[v]) {
      int sub = E.to;
      if (sub == par[v] || sub == hvy[v]) continue;
      decomp(sub, sub); //create new chains
    }
  }
//decomp core end
 
//segtree stuff begin
  void tb(int idx=1, int l=1, int r=ptr) {
    if (l == r) return void(st[idx] = cst[oi[l]]);
    int m=(l+r)>>1, ln=idx<<1, rn=idx<<1|1;
    tb(ln, l, m); tb(rn, m+1, r);
    st[idx] = max(st[ln], st[rn]);
  }
  void tu(int p, int v, int idx=1, int l=1, int r=ptr) {
    if (l == r) return void(st[idx] = v);
    int m=(l+r)>>1, ln=idx<<1, rn=idx<<1|1;
    (p <= m)? tu(p,v,ln,l,m) : tu(p,v,rn,m+1,r);
    st[idx] = max(st[ln], st[rn]);
  }
  int tq(int ql, int qr, int idx=1, int l=1, int r=ptr) {
    if (ql > r || qr < l) return -2e9;
    if (ql <= l && qr >= r) return st[idx];
    int m=(l+r)>>1, ln=idx<<1, rn=idx<<1|1;
    if (qr <= m) return tq(ql,qr,ln,l,m);
    if (ql > m) return tq(ql,qr,rn,m+1,r);
    return max(tq(ql,qr,ln,l,m), tq(ql,qr,rn,m+1,r));
  }
//segtree stuff end
 
public:
  HLD(int rt) {
    ptr = 0;
    par = cst = eton = dep =
      top = ti = oi = vector<int>(adj.size());
    hvy.assign(adj.size(), -1);
    dfs(rt); decomp(rt, rt);
    st.resize((ptr+5)<<2); tb();
  }
  void upd(int p, int v) { tu(ti[eton[p]], v); }
  //combine queries as we jump for lca
  int qry(int a, int b) { //can be split into (a, lca) && (b, lca)
    int res = 0;
    for (; top[a] != top[b]; a = par[top[a]]) { //a always deeper
      if (dep[top[a]] < dep[top[b]]) swap(a, b);
      res = max(res, tq(ti[top[a]], ti[a]));
    } //after for, top[a] == top[b]
    if (dep[a] < dep[b]) swap(a, b);
    return max(res, tq(ti[b]+1, ti[a]));
  }
};
 
signed main() {
  qIO;
  string s;
  int a, b, w, n, tst; cin >> tst; while(tst--) {
    cin >> n;
    adj = vector<vector<EDGE>>(n+5, vector<EDGE>());
    for (int i=1; i<n; ++i) {
      cin >> a >> b >> w;
      adj[a].pb({w, b, i});
      adj[b].pb({w, a, i});
    }
    HLD hld(1);
    while (cin >> s && s[0] != 'D' && cin >> a >> b) {
      if (s[0] == 'C') hld.upd(a, b);
      else cout << hld.qry(a, b) << '\n';
    }
  }
  return 0;
}
