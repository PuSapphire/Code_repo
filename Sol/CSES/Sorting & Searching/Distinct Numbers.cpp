#include <iostream>
#include <set>

using namespace std;

#define qIO ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)

signed main() {
  qIO;
  int tst, t;
  cin >> tst;
  set<int> st;
  while (tst--) {
    cin >> t;
    st.insert(t);
  }
  cout << st.size();
  return 0;
}
