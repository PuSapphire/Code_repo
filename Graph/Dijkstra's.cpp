#include <iostream>
#include <queue>
#include <vector>
using namespace std;

const int SZ = 1e5;
vector<ll> dis(SZ, 9e18);
vector<vector<pll>> adj(SZ);
dis[s] = 0;

void dijkstra() {
  //pair<vtx id, dist>
  priority_queue<pll, vector<pll>, greater<pll>> pq;
  pq.push({0, s});
  while (pq.size()) {
    ll now = pq.top().ft;
    ll d = pq.top().sd;
    pq.pop();
    if (t[now]) continue;
    t[now] = 1;

    for (pll &vtx : adj[now]) {
      if (t[vtx.ft]) continue;
      if (d+vtx.sd < dis[vtx.ft]) {
        dis[vtx.ft] = d+vtx.sd;
        pq.push({dis[vtx.ft], vtx.ft});
      }
    }
  }
}
