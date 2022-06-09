#include <iostream>
#include <algorithm>

using namespace std;

#define qIO ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)

signed main() {
  qIO;
  int n, s;
  cin >> n >> s;
  int arr[n];
  long long dp[s+1];
  fill(dp, dp+s+1, 1e9);
  dp[0] = 0;
  for (int i=0; i<n; i++) cin >> arr[i];
  for (int i=0; i<=s; i++) {
    for (int j=0; j<n; j++) {
      int dif = i-arr[j];
      if (dif >= 0) dp[i] = min(dp[i], dp[dif]+1);
    }
  }
  cout << ((dp[s] == 1e9)? -1 : dp[s]);
  return 0;
}
