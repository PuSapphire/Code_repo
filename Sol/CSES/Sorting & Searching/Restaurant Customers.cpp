#include <iostream>
#include <algorithm>

using namespace std;

#define qIO ios_base::sync_with_stdio(false); cin.tie(0);

signed main() {
  qIO;
  int n;
  cin >> n;
  int e[n], l[n];
  long long ans = 0, now = 0, j = 0;
  for (int i=0; i<n; i++) cin >> e[i] >> l[i];
  sort(e, e+n); sort(l, l+n);
  for (const int &t : e) {
    now++;
    while (l[j] <= t) { now--; j++; }
    ans = max(ans, now);
  }
  cout << ans;
  return 0;
}
