#include <iostream>
#include <algorithm>

using namespace std;
const int mod = 1e9+7;

signed main() {
  int tst, mxm;
  cin >> tst >> mxm;
  long long s = 0;
  long long arr[tst][mxm], t;
  for (int i=0; i<tst; i++) fill(arr[i], arr[i]+mxm, 0);
  cin >> t;
  if (t!=0) arr[0][t-1]=1;
  else for(int i=0; i<mxm; i++) arr[0][i] = 1;

  for (int i=1; i<tst; i++) {
    cin >> t;
    if (--t != -1) {
      arr[i][t] = arr[i-1][t];
      if (t != mxm) (arr[i][t] += arr[i-1][t+1]) %= mod;
      if (t != 0) (arr[i][t] += arr[i-1][t-1]) %= mod;
    } else {
      arr[i][0] = (arr[i-1][0] + arr[i-1][1]) % mod;
      arr[i][mxm-1] = (arr[i-1][mxm-1] + arr[i-1][mxm-2]) % mod;
      for (int j=1; j<mxm-1; j++) {
        arr[i][j] = arr[i-1][j+1] + arr[i-1][j] + arr[i-1][j-1];
        arr[i][j] %= mod;
      }
    }
  }
  /*cout << '\n';
  for (int i=mxm-1; i>=0; i--) {
    for (int j=0; j<tst; j++) {
      cout << arr[j][i] << ' ';
    }
    cout << '\n';
  }*/
  for (const int &e : arr[tst-1]) (s += e) %= mod;
  cout << s;
  return 0;
}
