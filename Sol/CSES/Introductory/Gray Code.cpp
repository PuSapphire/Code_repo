#include <iostream>
#include <bitset>
#include <cmath>

using namespace std;

#define qIO ios_base::sync_with_stdio(false); cin.tie(0);
bitset<16> b;

signed main() {
  qIO;
  int n;
  cin >> n;
  for (int i=0; i<(1<<n); ++i) {
    cout << (b ^= (i&-i)).to_string().substr(16-n) << '\n';
  }
  return 0;
}
