#include <iostream>

using namespace std;

#define qIO ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
const int mod = 1e9+7;

signed main() {
  qIO;
  int n;
  cin >> n;
  long long dp[n][n];
  string s[n];
  for (int i=0; i<n; i++) cin >> s[i];
  for (int i=0; i<n; i++) {
    if (s[0][i] == '*') {
      for (int j=i; j<n; j++, i++) {
        dp[0][j] = 0;
      }
    } else dp[0][i] = 1;
  }

  for (int i=0; i<n; i++) {
    if (s[i][0] == '*') {
      for (int j=i; j<n; j++, i++) {
        dp[j][0] = 0;
      }
    } else dp[i][0] = 1;
  }

  for (int i=1; i<n; i++) {
    for (int j=1; j<n; j++) {
      if (s[i][j] == '*') dp[i][j] = 0;
      else dp[i][j] = (dp[i-1][j] + dp[i][j-1]) % mod;
    }
  }
  cout << dp[n-1][n-1] % mod;
  return 0;
}
