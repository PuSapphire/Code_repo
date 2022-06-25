#include <iostream>
#include <algorithm>

using namespace std;
#define qIO ios_base::sync_with_stdio(false); cin.tie(0)
int az[26] = {};
unsigned long long fact[9] = {1};
int getfact(int n);

int main() {
  qIO;
  string s;
  cin >> s;
  sort(s.begin(), s.end());
  for (char a : s) az[a - 'a']++;
  cout << getfact(s.size()) << '\n';
  do cout << s << '\n'; while (next_permutation(s.begin(), s.end()));
  return 0;
}

int getfact(int n) {
  for (int i=1; i<9; i++) fact[i] = i*fact[i-1];
  unsigned long long f = fact[n];
  for (int e : az) f /= fact[e];
  return f;
}
