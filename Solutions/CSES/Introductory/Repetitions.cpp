#include <iostream>
#include <algorithm>

using namespace std;

#define qIO ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)

signed main() {
  qIO;
  string s;
  cin >> s;
  int len = 1, tmp = 1;
  for (int i=1; i<s.size(); i++) {
    if (s[i] == s[i-1]) tmp++;
    else {
      len = max(len, tmp);
      tmp = 1;
    }
  }
  cout << max(len, tmp);
  return 0;
}
