#include <iostream>
#include <set>
#include <map>

using namespace std;

#define qIO ios_base::sync_with_stdio(false); cin.tie(0);

signed main() {
  qIO;
  int n, x;
  cin >> n >> x;
  multiset<int> st;
  map<int, int> omap;
  for (int i=1, t; i<=n; i++) {
    cin >> t;
    st.insert(t);
    omap.emplace(t, i);
  }
  auto bound = st.upper_bound(x);
  for (auto it = st.begin(); it != bound; it++) {
    auto pos = st.find(x - *it);
    if (pos != st.end()) {
      cout << omap[*it] << ' ' << omap[*pos];
      return 0;
    }
  }
  cout << "IMPOSSIBLE";
  return 0;
}
