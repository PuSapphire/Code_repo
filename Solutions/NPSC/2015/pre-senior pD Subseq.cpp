#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

template <typename T> using pr = pair<T, T>;
using ll = long long;
using ld = long double;
#define ft  first
#define sd  second
#define pb  push_back
#define QIO ios_base::sync_with_stdio(false); cin.tie(0)

/*  #########  *\
dp[i]   := 前i個編號組成的字串數量
last[i] := 數字i上次出現的位置

dp[i] =  2*dp[i-1]+1 接或是不接，以及自己當開頭
dp[i] -= dp[last[i]] 扣掉結尾相同

結尾相同可能來自於字串連接，如"1011"可能來自[..., "10", "11"]
因此除了更新last[arr[i]]本身，還要更新last[arr[i-1]+arr[i]]...
由於arr[i]最多九位，因此更新到九位即可
\*  #########  */

const int MOD = 1e9+7;
signed main() {
    QIO;
    int tst; cin >> tst; while(tst--) {
        int n; cin >> n;
        ll dp[n+2];
        string arr[n+2]; 
        map<string, int> last;

        for (int i=2; i<=n+1; ++i) cin >> arr[i];
        dp[0] = 0; dp[1] = 1; //[0]->空值  [1]->空字串

        for (int i=2; i<=n+1; ++i) {
            dp[i] = ((2*dp[i-1] - dp[last[arr[i]]]) % MOD + MOD) % MOD;
            string concat = arr[i];
            for (int j=0; concat.size()<=9 && i-j>1; ++j) {
                last[concat] = i-j-1;
                concat += arr[i-j];
            }
        }
        //for (int i=2; i<=n+1; ++i) cout << dp[i] << ' '; cout << '\n';
        cout << dp[n+1]-1 << '\n';
    }
}
