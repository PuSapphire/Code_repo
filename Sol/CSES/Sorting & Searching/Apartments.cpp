#include <iostream>
#include <algorithm>

using namespace std;

#define qIO ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)

signed main() {
  qIO;
  int ppl, apt, dif;
  cin >> ppl >> apt >> dif;
  int p[ppl], a[apt];
  for (int i=0; i<ppl; i++) cin >> p[i];
  for (int i=0; i<apt; i++) cin >> a[i];
  sort(p, p+ppl);
  sort(a, a+apt);
  long long s = 0;
  for (int i=0, j=0; i<ppl && j<apt;) {
    if (a[j]-dif <= p[i] && a[j]+dif >= p[i]) { s++; i++; j++; }
    else if (a[j]-dif > p[i]) i++;
    else j++;
  }
  cout << s;
  return 0;
}
