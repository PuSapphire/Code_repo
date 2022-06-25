#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

typedef long long ll;
#define qIO ios_base::sync_with_stdio(false); cin.tie(0)
#define ft first
#define sd second
#define pb push_back

int main() {
  qIO;
  int tst, n;
  cin >> tst;
  while (tst--) {
    cin >> n;
    int ans = 1;
    float cap = sqrt(n);
    vector<int> v = {0, 0};
    while (!(n & 1)) { ++v[0]; n>>=1; }
    while (!(n % 3)) { ++v[1]; n/=3;  }

    for (int k=1;;++k) {
      int f = 6*k-1;
      if (f > cap) break;
      if (!(n % f)) {
        v.pb(1);
        while (!(n % f)) { ++v.back(); n/=f; }
      }
      f += 2;
      if (f > cap) break;
      if (!(n % f)) {
        v.pb(1);
        while (!(n % f)) { ++v.back(); n/=f; }
      }
    }
    for (auto s : v) ans *= (s+1);
    if (v.size()==2 && !v[0] && !v[1]) cout << 2 << '\n';
    else cout << ans << '\n';
  }
  return 0;
}
