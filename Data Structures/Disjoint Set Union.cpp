
/*  ########  *\
互斥集合組Disjoint Set Union(DSU, Union-Find)
時間複雜度: 
    合併 = O(n) → O(log n) → O(ɑ^-1(n))
    查詢 = O(n) → O(log n) → O(ɑ^-1(n))
資節用途: 分組、查組

有路徑壓縮(Path compression)、啟發式合併(Union by rank)兩種優化方式
都不使用O(n)，用了一種O(log n)，兩種一啟用O(ɑ^-1(n))
ɑ^-1(n) 為反阿克曼(ackermann)函式，幾乎可視為常數函數
\*  ########  */

#include <vector>
class DSU {
    std::vector<int> rt, sz;
    int find(int x) {
        if (x == rt[x]) return x;
        return rt[x] = find(x); //路徑壓縮
    }
    void unite(int i, int j) {
        i = find(i); j = find(j);
        if (i == j) return;
        if (sz[i] < sz[j]) std::swap(i, j); //啟發式合併
        sz[i] += sz[j]; rt[j] = i;
    }
    DSU(int n) {
        sz.assign(n+1, 1);
        for (int i=0; i<=n; ++i) rt.emplace_back(i);
    }
};