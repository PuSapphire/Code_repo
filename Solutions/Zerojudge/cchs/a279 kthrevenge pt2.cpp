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
演算法: 平衡二搜樹(pb_ds tree)
時間複雜度: O(n log n)

不會寫BST也沒關係，因為g++ compiler幫你寫好了
跟普通的set/map都一樣，不過多了兩個函式:
1. .find_by_order(int n) -> 回傳第n個元素的指標(0開始)(Ex. less<int>, n=2就是第3小)
2. .order_of_key(int k)  -> 回傳嚴格比k小的元素數量

如果compiler不是g++(gcc、gnu)的話就不能用

將XXX_equal<>塞進去即可變成multi
但因為這是未定義行為，有一些事情要注意
1. .find()永遠找不到(永遠return .end())
2. .erase()不能用值，只能放指標進去
3. .lowerbound(), .upperbound()功能互換
4. .find_by_order(), .order_of_key() 功能完好沒有奇怪的改變

需要更正常一點的multi的話可以改塞pair當作key
如(10, 1), (10, 2), (10, 3)...即第一個key=10的、第二個...
\*  ########  */

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

tree<int, null_type, less_equal<int>, rb_tree_tag, tree_order_statistics_node_update> st;

signed main() {
    QIO;
    int q, k; cin >> q >> k;
    for (int a, b; q--; ) {
        cin >> a;
        if (a == 1) cin >> b, st.insert(b);
        else {
            auto it = st.find_by_order(k-1); //find_by_order從0開始
            if (it == st.end()) cout << -1 << '\n';
            else cout << *it << '\n', st.erase(it);
        }
    }
}