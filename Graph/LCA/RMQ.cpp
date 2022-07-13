
#include <iostream>
#include <vector>
using namespace std;

const int N = 2e5+5;
int n, q, st[N], first[N], height[N], root=0;
vector<int> euler;
vector<vector<int>> TREE_GRAPH;

void upd(int i, int v) {
    for (st[i+=n]=v; i>1; i>>=1) 
        st[i>>1] = min(st[i], st[i^1]);
}
int qry(int ql, int qr) {
    int r = 2e9;
    for (ql+=n, qr+=n; ql < qr; ql>>=1, qr>>=1) {
        if (ql & 1) r = min(r, st[ql++]);
        if (qr & 1) r = min(r, st[--qr]);
    } return r;
}
void dfs(int v=root, int pv=-1, int h=0) {
    height[v] = h;
    first[v] = euler.size();
    euler.push_back(v);
    for (auto near: TREE_GRAPH[v]) {
        if (near == pv) continue;
        dfs(near, v, h+1);
        euler.push_back(v);
    }
}
void init() {
    dfs();
    for (int v=0; v<n; ++v) upd(v, height[v]);
}
int find_lca(int u, int v) {
    u = first[u]; v = first[v];
    if (u > v) swap(u, v);
    return qry(u, v);
}