#include <iostream>

using namespace std;

#define qIO ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)
const int mod = 1e9+7;

long long binExp(long long b, long long p, long long m) {
  long long res = 1;
  while (p) {
    if (p & 1) {
      res = res*b % m;
      p--;
    }
    b = b*b % m;
    p >>= 1;
  }
  return res % m;
}

signed main() {
  qIO;
  int n;
  while (cin >> n && n) {
    long long a, b, c;
    while (n--) {
      cin >> a >> b >> c;
      cout << binExp(a, binExp(b, c, mod-1), mod) << '\n';
    }
  }
  return 0;
}
