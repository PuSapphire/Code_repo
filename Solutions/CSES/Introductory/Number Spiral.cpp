#include <iostream>
#include <algorithm>

using namespace std;

#define qIO ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

signed main() {
  qIO;
  int n;
  cin >> n;
  while (n--) {
    long long x, y;
    cin >> y >> x;
    long long sqbt = max(x, y);
    sqbt = sqbt*(sqbt-1) + 1;
    if (x == y) cout << sqbt;
    else if (x > y) cout << ((x & 1)? sqbt + x-y : sqbt + y-x);
    else cout << ((y & 1)? sqbt + x-y : sqbt + y-x);
    cout << '\n';
  }
  return 0;
}
