#include <iostream>

using namespace std;

#define qIO ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

signed main() {
  qIO;
  long long n, s=0;
  cin >> n;
  for (int i=5; i<=n;) {
    s += n/i;
    i *= 5;
  }
  cout << s;
  return 0;
}
