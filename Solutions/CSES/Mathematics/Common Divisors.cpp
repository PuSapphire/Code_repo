#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
using namespace std;

template <typename T> using pr = pair<T, T>;
using ll = long long;
using ld = long double;
#define ft  first
#define sd  second
#define pb  push_back
#define QIO ios_base::sync_with_stdio(false); cin.tie(0)


unordered_map<int, vector<int>> ht;
int count_of_factors[int(1e6+5)];
void count_factors(int x) {
    if (ht[x].empty()) {
        int i = 1;
        for (; i*i<x; ++i) if (!(x % i)) {
            ht[x].pb(i);
            ht[x].pb(x/i);
        }
        if (i*i == x) ht[x].pb(i);
    }
    for (int f : ht[x]) ++count_of_factors[f];
}

signed main() {
    QIO;
    int n; cin >> n;
    for (int i=0; i<n; ++i) {
        int x; cin >> x;
        count_factors(x);
    }
    for (int i=1e6; i>=1; --i) {
        if (count_of_factors[i] >= 2) {
            cout << i;
            break;
        }
    }
}