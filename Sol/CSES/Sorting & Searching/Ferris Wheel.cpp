#include <iostream>
#include <algorithm>

using namespace std;

#define qIO ios_base::sync_with_stdio(false); cin.tie(0);

signed main() {
  qIO;
  int n, x;
  cin >> n >> x;
  long long arr[n], s = 0;
  for (int i=0; i<n; i++) cin >> arr[i];
  sort(arr, arr+n);
  for (int i=0, j=n-1; i <= j; s++, j--) {
    if (i == j) { s++; break; }
    if (arr[i] + arr[j] <= x) i++;
  }
  cout << s;
  return 0;
}
