#include <iostream>

using namespace std;

#define qIO ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
const int mod = 1e9+7;

void binExp(long long b, long long p) {
  long long res = 1;
  while (p) {
    if (p & 1) {
      res = (res*b) % mod;
      p--;
    }
    b = (b*b) % mod;
    p >>= 1;
  }
  cout << res;
}

signed main() {
  qIO;
  long long n;
  cin >> n;
  binExp(2, n);
  return 0;
}
