#include <iostream>

using namespace std;
#define qIO ios_base::sync_with_stdio(false); cin.tie(0)

int main() {
  qIO;
  int n, w;
  cin >> n >> w;
  int dp[w+1], arr[n][2];
  fill(dp, dp+w+1, 0);
  for (int i=0; i<n; i++) cin >> arr[i][0];
  for (int i=0; i<n; i++) cin >> arr[i][1];
  for (int i=0, x; i<n; i++) {
    x = arr[i][0];
    for (int j=w; j>=arr[i][0]; j--) {
      dp[j] = max(dp[j], dp[j-x]+arr[i][1]);
    }
  }
  cout << dp[w];
  return 0;
}
