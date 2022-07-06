
#include <iostream>
#include <algorithm>
using namespace std;

template <typename T>
using pr = pair<T, T>;
typedef long long ll;
#define ft  first
#define sd  second
#define pb  push_back
#define qIO ios_base::sync_with_stdio(false); cin.tie(0)

const int MAXN = 1e6+5, MAXQ = 1e5+5;
const int sz = MAXN<<2;
int A[MAXN], X[MAXQ], Y[MAXQ], Z[MAXQ], k, m, N, Q;
bool C[MAXQ];
void gen_dat(), ini();

int st1[sz], st2[sz]; ll st3[sz]; //{max, min, sum}
int lz[sz];
void push(int i, int l, int r);
void build(int idx=1, int l=1, int r=N);
pair<pr<int>, int> qry(int ql, int qr, int idx=1, int l=1, int r=N);
void rupd(int ql, int qr, int v, int idx=1, int l=1, int r=N);

signed main() {
  qIO; ini();
  for (int i=1; i<=Q; ++i) {
    if (!C[i]) rupd(X[i], Y[i], Z[i]);
    else {
      auto p = qry(X[i], Y[i]);
      cout << p.sd%m << ' ' << p.ft.ft - p.ft.sd << '\n';
    }
  }
  return 0;
}

void push(int i, int ql, int qr) {
  if (lz[i] != -1) {
    int m = (ql + qr) >> 1;
    int l = i<<1, r = i<<1|1;
    st1[l] = st1[r] = 
    st2[l] = st2[r] = lz[i];
    st3[l] = (m-ql+1) * lz[i];
    st3[r] = (qr-m) * lz[i];

    lz[l] = lz[r] = lz[i]; lz[i] = -1;
  }
}
void build(int idx, int l, int r) {
  if (l == r) st1[idx] = st2[idx] = st3[idx] = A[l];
  else {
    int m = (l + r) >> 1;
    build(idx<<1, l, m); build(idx<<1|1, m+1, r);
    st1[idx] = max(st1[idx<<1], st1[idx<<1|1]);
    st2[idx] = min(st2[idx<<1], st2[idx<<1|1]);
    st3[idx] = (st3[idx<<1] + st3[idx<<1|1]);
  }
}
pair<pr<int>, int> qry(int ql, int qr, int idx, int l, int r) {
  if (l != r) push(idx, l, r);
  if (ql > r || qr < l) return {{-1, 2e9}, 0};
  if (ql <= l && qr >= r) return {{st1[idx], st2[idx]}, st3[idx]};
  int m = (l + r) >> 1;
  if (qr <= m) return qry(ql, qr, idx<<1, l, m);
  if (ql > m)  return qry(ql, qr, idx<<1|1, m+1, r);
  auto p1 = qry(ql, qr, idx<<1, l, m);
  auto p2 = qry(ql, qr, idx<<1|1, m+1, r);
  return {
    { max(p1.ft.ft, p2.ft.ft), min(p1.ft.sd, p2.ft.sd) },
    p1.sd + p2.sd
  };
}
void rupd(int ql, int qr, int v, int idx, int l, int r) {
  if (l != r) push(idx, l, r);
  if (ql <= l && qr >= r) {
    st1[idx] = st2[idx] = st3[idx] = lz[idx] = v;
    st3[idx] = (r-l+1) * v;
  }
  else {
    int m = (l + r) >> 1;
    if (ql <= m) rupd(ql, qr, v, idx<<1, l, m);
    if (qr > m) rupd(ql, qr, v, idx<<1|1, m+1, r);
    st1[idx] = max(st1[idx<<1], st1[idx<<1|1]);
    st2[idx] = min(st2[idx<<1], st2[idx<<1|1]);
    st3[idx] = st3[idx<<1] + st3[idx<<1|1];
  }
}


void gen_dat()
{
   int i,j;
   for( i=k+1; i<=max(Q,N); ++i )
      A[i] = ( A[i-2]*97 + A[i-1]*3 )%m+1;
   for(i=1,j=max(Q,N); i<=Q; ++i,--j)
   {
      C[i] = A[i]&1;
      X[i] = (A[i]+A[j])%N+1;
      Y[i] = X[i]+ ( (A[i]<<3)+(A[j]<<5)+m )%( N-X[i]+1 );
      if(!C[i]) Z[i] = ((A[i]<<3)+(A[j]<<5))%m+1;
   }
}

void ini() {
  cin >> k >> m;
  for (int i=1; i<=k; ++i) cin >> A[i];
  cin >> N >> Q;
  gen_dat();
  build();
  fill(lz, lz+sz, -1);
}