
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;
typedef pair<ll, ll>  pll;
typedef pair<int,int> pii;
#define ft  first
#define sd  second
#define pb  push_back
#define qIO ios_base::sync_with_stdio(false); cin.tie(0)

const int MAXN = 1e6+5, MAXQ = 1e5+5;
int A[MAXN], X[MAXQ], Y[MAXQ], k, m, N, Q;
bool C[MAXQ];
void gen_dat(), ini();

int st1[MAXN<<2], st2[MAXN<<2]; //{max, min}
void build(int idx=1, int l=1, int r=N);
pii qry(int ql, int qr, int idx=1, int l=1, int r=N);
void upd(int p, int v, int idx=1, int l=1, int r=N);

signed main() {
  qIO; ini();
  for (int i=1; i<=Q; ++i) {
    if (!C[i]) upd(X[i], Y[i]);
    else {
      pii p = qry(X[i], Y[i]);
      cout << abs(p.ft - p.sd) << '\n';
    }
  }
  return 0;
}

void build(int idx, int l, int r) {
  if (l == r) st1[idx] = st2[idx] = A[l];
  else {
    int m = (l + r) >> 1;
    build(idx<<1, l, m); build(idx<<1|1, m+1, r);
    st1[idx] = max(st1[idx<<1], st1[idx<<1|1]);
    st2[idx] = min(st2[idx<<1], st2[idx<<1|1]);
  }
}
pii qry(int ql, int qr, int idx, int l, int r) {
  if (ql > r || qr < l) return {-1, 2e9};
  if (ql <= l && qr >= r) return {st1[idx], st2[idx]};
  int m = (l + r) >> 1;
  if (qr <= m) return qry(ql, qr, idx<<1, l, m);
  if (ql > m)  return qry(ql, qr, idx<<1|1, m+1, r);
  pii p1 = qry(ql, qr, idx<<1, l, m);
  pii p2 = qry(ql, qr, idx<<1|1, m+1, r);
  return { max(p1.ft, p2.ft), min(p1.sd, p2.sd) };
}
void upd(int p, int v, int idx, int l, int r) {
  if (l == r) A[p] = v, st1[idx] = st2[idx] = v;
  else {
    int m = (l + r) >> 1;
    if (p <= m) upd(p, v, idx<<1, l, m);
    else upd(p, v, idx<<1|1, m+1, r);
    st1[idx] = max(st1[idx<<1], st1[idx<<1|1]);
    st2[idx] = min(st2[idx<<1], st2[idx<<1|1]);
  }
}



void gen_dat() {
  int i,j;
  for(i=k+1;i<=max(Q,N);++i) A[i]=(A[i-2]*97+A[i-1]*3)%m+1;
  for(i=1,j=max(Q,N);i<=Q; ++i,--j) {
    C[i] = A[i]&1;
    X[i] = (A[i]+A[j])%N+1;
    if(C[i]) Y[i]=X[i]+((A[i]<<3)+(A[j]<<5)+m)%(N-X[i]+1);
    else Y[i]=((A[i]<<3)+(A[j]<<5))%m+1;
  }
}
void ini() {
  cin >> k >> m;
  for (int i=1; i<=k; ++i) cin >> A[i];
  cin >> N >> Q;
  gen_dat();
  build();
}