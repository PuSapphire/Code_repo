#include <iostream>

using namespace std;

#define qIO ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
const int MAXN = 2e5;
int n, q;
unsigned long long BIT[MAXN+1];
void upd(int idx, int v);
long long qry(int idx);

signed main() {
  qIO;
  cin >> n >> q;
  long long arr[n+1];
  fill(BIT+1, BIT+n+1, 0);
  for (int i=1; i<=n; i++) {
    cin >> arr[i];
    upd(i, arr[i]);
  }
  long long a, l, r;
  while (q--) {
    cin >> a >> l >> r;
    if (a == 1) {
      upd(l, r-arr[l]);
      arr[l] = r;
    }
    else cout << qry(r) - qry(l-1) << '\n';
  }
  return 0;
}

void upd(int idx, int v) {
  for (; idx<=n; idx += idx&-idx) BIT[idx] += v;
}

long long qry(int idx) {
  long long s = 0;
  for (; idx > 0; idx -= idx&-idx) s += BIT[idx];
  return s;
}
