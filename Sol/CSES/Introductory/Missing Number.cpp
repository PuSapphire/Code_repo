#include <iostream>
#include <bitset>

using namespace std;

#define qIO ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)
bitset<200005> b(0);

signed main() {
  qIO;
  long long n;
  cin >> n;
  for (int i=1, t; i<n; i++) {
    cin >> t;
    b[t] = 1;
  }
  for (int i=1; i<=n; i++) {
    if (!b[i]) {
      cout << i;
      break;
    }
  }
  return 0;
}
