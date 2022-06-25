#include <iostream>
#include <algorithm>
#include <bitset>
using namespace std;

typedef long long ll;
#define qIO ios_base::sync_with_stdio(false); cin.tie(0)
#define ft first
#define sd second
bitset<30> b[(int)2e4+5];

int main() {
  qIO;
  int n, l, ans=2e9;
  cin >> n >> l;
  for (int i=0; i<n; ++i) cin >> b[i];
  for (int i=0; i<n; ++i) for (int j=i+1; j<n; ++j) {
    ans = min(ans, (int)(b[i] ^ b[j]).count());
  }
  cout << ans;
  return 0;
}
