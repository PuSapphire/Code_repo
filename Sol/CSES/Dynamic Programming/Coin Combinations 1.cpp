#include <iostream>
#include <algorithm>

using namespace std;

#define qIO ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)
const int mod = 1e9+7;

signed main() {
  qIO;
  int n, s;
  cin >> n >> s;
  int arr[n];
  long long dp[s+1];
  fill(dp, dp+s+1, 0);
  for (int i=0; i<n; i++) {
    cin >> arr[i];
    if (arr[i] > s) continue;
    dp[arr[i]] = 1;
  }
  for (int i=1; i<=s; i++) {
    for (int j=0; j<n; j++) {
      int dif = max(0, i-arr[j]);
      dp[i] = (dp[i] + dp[dif]) % mod;
    }
  }
  cout << dp[s] % mod;
  return 0;
}
