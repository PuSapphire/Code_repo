#include <iostream>

using namespace std;

#define qIO ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)

signed main() {
  qIO;
  long long n;
  cin >> n;
  while (n != 1) {
    cout << n << ' ';
    if (n & 1) n = 3*n + 1;
    else n >>= 1;
  }
  cout << 1;
  return 0;
}
