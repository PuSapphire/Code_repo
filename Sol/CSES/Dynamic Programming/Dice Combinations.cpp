#include <iostream>
#include <algorithm>

using namespace std;

#define qIO ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)
const int mod = 1e9+7;

signed main() {
  qIO;
  int n;
  cin >> n;
  long long dp[n+1];
  fill(dp, dp+n+1, 0);
  dp[0] = 1;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= 6 && i-j >= 0; j++) {
      (dp[i] += dp[i-j]) %= mod;
    }
  }
  cout << dp[n];
  return 0;
}
