#include <iostream>
#include <algorithm>

using namespace std;

#define qIO ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

signed main() {
  qIO;
  int n;
  cin >> n;
  int dp[n+1];
  fill(dp+1, dp+1+n, 1e9);
  dp[0] = 0;
  for (int i=0; i<=n; i++) {
    for (const char &a : to_string(i)) {
      dp[i] = min(dp[i], dp[i-(a-'0')]+1);
    }
  }
  cout << dp[n];
  return 0;
}
