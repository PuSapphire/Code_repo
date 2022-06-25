
/*  ########  *\
莫隊演算法Mo's Algorithm
時間複雜度: n√n
資節用途: 離線區間查詢

對於一些難以合併，而線段樹不管用的區間查詢常常有奇效
\*  ########  */
#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;

const int N = 8e4, Q = 8e4;
const int S = sqrt(N);
struct Query {
    int l, r, lb, idx;
    bool operator< (Query const &rhs) {
        if (lb == rhs.lb) //奇偶優化 (parity sort)
            return lb&1? r<rhs.r : r>rhs.r; 
        return lb < rhs.lb;
    }
};

int singleAns(int i) {
    return i * 5;
}
void inc(int &v, int i) {
    v += singleAns(i);
}
void dec(int &v, int i) {
    v -= singleAns(i);
}
int sol(int v) {
    return v;
}

vector<int> process(vector<pair<int, int>> &qry) {
    vector<Query> Mo;
    for (int i=0; i<qry.size(); ++i) {
        int l = qry[i].first;
        int r = qry[i].second;
        Mo.push_back({l, r, l/S, i});
    }

    vector<int> ans(qry.size());
    sort(Mo.begin(), Mo.end());
    int cl=1, cr=0, cur=0;
    for (Query const &q : Mo) {
        while (cl > q.l) inc(cur, --cl);
        while (cl < q.l) dec(cur, cl++);
        while (cr > q.r) dec(cur, cr--);
        while (cr < q.r) inc(cur, ++cr);
        ans[q.idx] = sol(cur);
    }
    return ans;
}