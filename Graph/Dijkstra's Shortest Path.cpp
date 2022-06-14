#include <queue>
#include <vector>
using namespace std;

template<typename T> using pr = pair<T, T>;

const int N = 2e5+5;
vector<int> dis(N, 2e9);
vector<bool> vis(N, 0);
vector<vector<pr<int>>> adj(N);
void djk(int s) {
    dis[s] = 0; vis[s] = 1;
    priority_queue<pr<int>, vector<pr<int>>, greater<pr<int>>> pq;
    pq.push({0, s});
    while (pq.size()) {
        int d = pq.top().first;
        int v = pq.top().second;
        if (vis[v]) continue;
        vis[v] = 1;
        for (pr<int> const &near : adj[v]) {
            if (vis[near.first] != 0) continue;
            if (dis[v] + d < dis[near.first]) {
                dis[near.first] = dis[v] + d;
                pq.push({dis[near.first], near.second});
            }
        }
    }
}