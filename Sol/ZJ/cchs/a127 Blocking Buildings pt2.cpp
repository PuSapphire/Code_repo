#include <iostream>
#include <algorithm>
using namespace std;

template<typename T> using p = pair<T, T>;
using ll = long long;
using ld = long double;
#define ft  first
#define sd  second
#define pb  push_back
#define QIO ios_base::sync_with_stdio(false); cin.tie(0)

/*  ########  *\
演算法: greedy && 區間和 (離線)
時間複雜度: O(n log n)

資結的單一個節點都只存0或1，其在資結內的位置代表原位置
由高度小做到大，當更新值仍不大於下個查詢高度k就繼續更新
更新時一次將高度=x的所有位置+1
如此在查詢時，=1的所有位置即所有高度比k小的建築位置
再查詢區間的和，就剛好是區間內不大於k的數量

如果遇到題目的高度範圍很大(如到1e9)，可以先進行離散化
\*  ########  */

#include <vector>
const int N = 2e5+5;
struct Query {
    int l, r, k;
    int idx; //原本是第幾個查詢
} a[N];
bool cmp(Query q1, Query q2) {
    return q1.k < q2.k;
}
int n, q, x=0, bit[N], ans[N];
vector<int> pos[N]; //pos[i]代表高度=i的建築的所有位置
void upd(int i) {
    for(; i<N; i += i&-i) ++bit[i];
}
int qry(int i) {
    int sum = 0;
    for(; i>0; i -= i&-i) sum += bit[i];
    return sum;
}

signed main() {
    QIO;
    cin >> n >> q;
    for (int v, i=1; i<=n; ++i) {
        cin >> v;
        pos[v].pb(i);
    }
    for (int i=0; i<q; ++i) {
        cin >> a[i].l >> a[i].r >> a[i].k;
        a[i].idx = i;
    }

    sort(a, a+q, cmp);
    for (int i=0; i<q; ++i) {
        while (a[i].k >= x) {
            for (auto idx : pos[x]) 
                upd(idx); 
            ++x;
        }
        ans[a[i].idx] = qry(a[i].r) - qry(a[i].l-1);
    }
    for (int i=0; i<q; ++i) cout << ans[i] << '\n';
}