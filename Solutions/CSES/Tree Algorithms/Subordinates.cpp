#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

typedef long long ll;
#define ft  first
#define sd  second
#define pb  push_back
#define qIO ios_base::sync_with_stdio(false); cin.tie(0)

vector<vector<int>> v;
int n, x, sum[int(2e5+5)];
int build(int i);

signed main() {
  qIO;
  cin >> n;
  v.resize(n+1, vector<int>{});
  for (int i=2; i<=n; ++i) {
    cin >> x;
    v[x].push_back(i);
  }
  build(1);
  for (int i=1; i<=n; ++i) cout << sum[i] << ' ';
  return 0;
}

int build(int i) {
  if (sum[i]) return sum[i];
  if (!v[i].size()) return 0;
  for (auto &p:v[i]) sum[i] += build(p);
  return sum[i] += v[i].size();
}
