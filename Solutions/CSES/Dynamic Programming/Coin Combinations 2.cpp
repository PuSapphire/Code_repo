#include <iostream>

using namespace std;

#define qIO ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
const int mod = 1e9+7;

signed main() {
  qIO;
  int n, x;
  cin >> n >> x;
  int arr[n];
  int dp[n][x+1];
  for (int i=0; i<n; i++) cin >> arr[i];
  for (int i=0; i<n; i++) fill(dp[i], dp[i]+x+1, 0);
  dp[0][0] = 1;
  for (int i=0; arr[0]*i<=x; i++) dp[0][arr[0]*i] = 1;

  for (int i=1; i<n; i++) {
    for (int j=0; j<=x; j++) {
      dp[i][j] = dp[i-1][j];
      if (j >= arr[i]) (dp[i][j] += dp[i][j-arr[i]]) %= mod;
    }
  }

  cout << dp[n-1][x] % mod;
  return 0;
}
