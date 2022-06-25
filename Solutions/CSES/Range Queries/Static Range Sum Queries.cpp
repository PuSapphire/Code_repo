#include <iostream>

using namespace std;

#define qIO ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

signed main() {
  qIO;
  int n, q;
  cin >> n >> q;
  long long arr[n+1];
  arr[0] = 0;
  cin >> arr[1];
  for (int i=2, s; i<=n; i++) {
    cin >> s;
    arr[i] = s + arr[i-1];
  }
  int l, r;
  for (int i=0; i<q; i++) {
    cin >> l >> r;
    cout << arr[r] - arr[l-1] << '\n';
  }
  return 0;
}
