#include <iostream>
#include <algorithm>
using namespace std;

template <typename T> using pr = pair<T, T>;
using ll = long long;
using ld = long double;
#define ft  first
#define sd  second
#define pb  push_back
#define QIO ios_base::sync_with_stdio(false); cin.tie(0)

const int N = 2e5+5, S = 20;
int n, q, bin_lift[S][N];

signed main() {
    QIO;
    cin >> n >> q;
    for (int i=2; i<=n; ++i) {
        int p; cin >> p;
        bin_lift[0][i] = p;
    }
    for (int i=1; i<S; ++i) {
        for (int j=1; j<=n; ++j) {
            bin_lift[i][j] = bin_lift[i-1][bin_lift[i-1][j]];
        }
    }
    for (int i=0; i<q; ++i) {
        int x, k; cin >> x >> k;
        for (int j=0; j<S; ++j) {
            if ((k >> j) & 1) x = bin_lift[j][x];
        }
        cout << (x ?: -1) << '\n';
    }
}