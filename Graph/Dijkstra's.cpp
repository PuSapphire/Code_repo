#include <iostream>
#include <queue>
#include <vector>
using namespace std;

const int SZ = 1e5;
vector<int> dis(SZ, 2e9);
vector<vector<pair<int, int>>> adj(SZ);
dis[s] = 0;

void dijkstra() {
  //pair<vtx id, dist>
  priority_queue<int, vector<int>, greater<int>> pq;
  pq.push({0, s});
  while (pq.size()) {
    int now = pq.top().ft;
    int d = pq.top().sd;
    pq.pop();
    if (t[now]) continue;
    t[now] = 1;

    for (pair<int, int> &vtx : adj[now]) {
      if (t[vtx.ft]) continue;
      if (d+vtx.sd < dis[vtx.ft]) {
        dis[vtx.ft] = d+vtx.sd;
        pq.push({dis[vtx.ft], vtx.ft});
      }
    }
  }
}
