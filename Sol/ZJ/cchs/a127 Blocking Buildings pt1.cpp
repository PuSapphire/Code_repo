//Source: NCTU PCCA
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

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
演算法: Merge Sort Tree
時間複雜度: O(n log^2 n)

線段樹的節點儲存一個區間[l, r]的陣列排序後的樣子
底達到一個完全包含於查詢區間[ql, qr]的區間[l, r]時，
即可利用二分搜快速搜出這個區間答案。
合併只需要相加即可

...但因為學校系統較慢，因此必須加入許多常數優化才給過
\*  ########  */

#include <vector>
const int N = 2e5+5;
int n, q;
vector<int> st[N<<1];

inline int R() {
    int x = 0, c = getchar();
    while(('0'>c||c>'9') && c!=EOF) c = getchar();
    for (; '0'<=c && c<='9'; c=getchar()) x = x*10 + (c^'0');
    return x;
}

void build() {
    for (int idx=n; idx<(n<<1); ++idx) st[idx] = {R()};
    for (int idx=n-1; idx>0; idx--) {
        int ln=idx<<1, rn=idx<<1|1;
        std::merge( //分治排序的merge
            st[ln].begin(), st[ln].end(),
            st[rn].begin(), st[rn].end(),
            std::back_inserter(st[idx]) 
        ); 
    }

    //忘記的話也可以手刻
    /* 
    st[idx].resize(r-l+1);
    int i=-1, j=-1, k=-1; 
    for (; i < st[ln].size(); ++i) {
        while (j < st[rn].size() && st[rn][j] < st[ln][i])
            st[idx][++k] = st[rn][++j];
        st[idx][++k] = st[ln][++i];
    }
    while (j < st[rn].size()) st[idx][++k] = st[rn][++j]; 
    */
}

int qry(int l, int r, int k) {
    int res = 0;
    for (l+=n, r+=n; l<r; l>>=1, r>>=1) {
        if (l & 1) {
            res += upper_bound(st[l].begin(), st[l].end(), k) - st[l].begin();
            ++l;
        }
        if (r & 1) {
            --r;
            res += upper_bound(st[r].begin(), st[r].end(), k) - st[r].begin();
        }
    }
    return res;
}

signed main() {
    QIO;
    n = R(); q = R();
    build();
    while (q--) {
        int l=R(), r=R(), k=R();
        cout << qry(l-1, r, k) << '\n';
    }
}
