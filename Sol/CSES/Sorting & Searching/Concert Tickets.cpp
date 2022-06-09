#include <iostream>
#include <set>

using namespace std;

#define qIO ios_base::sync_with_stdio(false); cin.tie(0);

signed main() {
  qIO;
  int n, p;
  cin >> n >> p;
  multiset<long long> st;
  for (int i=0, t; i<n; i++) { cin >> t; st.insert(t); }
  for (int i=0, t; i<p; i++) {
    cin >> t;
    auto it = st.upper_bound(t);
		if (it == st.begin()) cout << -1 << "\n";
		else { cout << *(--it) << "\n"; st.erase(it); }
  }
  return 0;
}
