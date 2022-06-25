#include <iostream>
#include <algorithm>

using namespace std;

#define qIO ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)

signed main() {
  qIO;
  long long s = 0;
  int n;
  cin >> n;
  if (n == 1) {
    cout << 0;
    return 0;
  }
  int arr[n];
  for (int i=0; i<n; i++) {
    cin >> arr[i];
  }
  for (int i=1; i<n; i++) {
    if (arr[i] < arr[i-1]) {
      s += (arr[i-1] - arr[i]);
      arr[i] = arr[i-1];
    }
  }
  cout << s;
  return 0;
}
