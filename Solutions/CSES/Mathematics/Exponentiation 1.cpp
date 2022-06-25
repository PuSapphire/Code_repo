#include <iostream>

using namespace std;

#define qIO ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)
const int mod = 1e9+7;

long long binExp(long long b, long long p) {
  long long res = 1;
  while (p) {
    if (p & 1) {
      res = res*b % mod;
      p--;
    }
    b = b*b % mod;
    p >>= 1;
  }
  return res % mod;
}

signed main() {
  qIO;
  int n;
  while (cin >> n) {
    long long b, p;
    while (n--) {
      cin >> b >> p;
      cout << binExp(b, p) << '\n';
    }
  }
  return 0;
}
