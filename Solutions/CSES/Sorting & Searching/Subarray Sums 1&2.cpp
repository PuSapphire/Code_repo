#include <iostream>
#include <map>

using namespace std;
#define qIO ios_base::sync_with_stdio(false); cin.tie(0)

int main() {
  qIO;
  int n, x;
  cin >> n >> x;
  long long s = 0, cs = 0;
  map<long long, int> omap = {{0, 1}};
  for (int i=0, t; i<n; i++) {
    cin >> t;
    s += omap[(cs += t) - x];
    omap[cs]++;
  }
  cout << s;
  return 0;
}
