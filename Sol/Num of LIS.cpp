#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

typedef long long ll;
#define ft  first
#define sd  second
#define pb  push_back
#define qIO ios_base::sync_with_stdio(false); cin.tie(0)

const int mod = 1e9+7;
inline int fR();

int main() {
  int n = fR();
  vector<vector<ll>> num(n, vector<ll>{}), cs;
  for (int i=0; i<min(10, n); ++i) 
    num[i].reserve(n >> i);
  vector<ll> lis;
  lis.reserve(n);
  ll i, s;
  for (int _=0; _<n; ++_) {
    int ele = fR();
    i = lower_bound(lis.begin(), lis.end(), ele) - lis.begin();
    s = 1;
    if (i > 0) {
      ll j = upper_bound(num[i-1].begin(), num[i-1].end(), -ele) - num[i-1].begin(); 
      s = (cs[i-1].back() - cs[i-1][j]) % mod;    
    }
    num[i].pb(-ele);
    if (i == lis.size()) {
      lis.pb(ele);
      cs.pb({0, s});
    } else {
      lis[i] = ele;
      cs[i].pb(s + cs[i].back());
    }
  }
  cout << cs.back().back() % mod;
  return 0;
}

inline int fR() {
  int x = 0, c = getchar_unlocked();
  for (; '0'<=c && c<='9'; c=getchar_unlocked())
    x = (x<<1) + (x<<3) + (c^'0');
  return x;
}
