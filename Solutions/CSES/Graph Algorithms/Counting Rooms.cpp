#include <iostream>

using namespace std;

#define qIO ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)
bool mark[1000][1000] = {{}};
string m[1000];
bool dfs(int x, int y);
int kai[5] = {1, 0, -1, 0, 1};
int r, c;

signed main() {
  qIO;
  int s=0;
  cin >> r >> c;
  for (int i=0; i<r; i++) cin >> m[i];
  for (int i=0; i<c; i++) {
    for (int j=0; j<r; j++) {
      s += dfs(i, j);
    }
  }
  cout << s;
  return 0;
}

bool dfs(int x, int y) {
  if (mark[x][y] || m[y][x] == '#') return 0;
  mark[x][y] = 1;
  for (int i=0; i<4; i++) {
    int nx = x+kai[i], ny = y+kai[i+1];
    if (nx < 0 || nx >= c || ny < 0 || ny >= r) continue;
    dfs(nx, ny);
  }
  return 1;
}
