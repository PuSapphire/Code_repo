#include <iostream>

using namespace std;

#define qIO ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
const int MAXN = 2e5;
const int K = 25; //arr size ~ 1e7
int st[MAXN][K+1]; //st[i][j] = ans([i, i+2^j−1]) of len 2^j
int log[MAXN+1]; //RMQ
void iniRMQ(int n);
int getRMQ(int l, int r);

signed main() {
  qIO;
  int n, q;
  cin >> n >> q;
  for (int i=0; i<n; i++) cin >> st[i][0];
  iniRMQ(n);
  int l, r;
  while (q--) {
    cin >> l >> r;
    cout << getRMQ(l-1, r-1) << '\n';
  }
  return 0;
}

void getlog() {
  log[1] = 0;
  for (int i = 2; i <= MAXN; i++) log[i] = log[i>>1] + 1;
}

void iniRMQ(int n) {
  getlog();
  for (int j=1; j<=K; j++) {
    for (int i=0; i+(1<<j)<=n; i++) {
      st[i][j] = min(st[i][j-1], st[i + (1<<(j - 1))][j - 1]);
    }
  }
}

int getRMQ(int l, int r) {
  int j = log[r - l + 1];
  int qry = min(st[l][j], st[r - (1 << j) + 1][j]);
  return qry;
}

