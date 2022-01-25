#include <iostream>
#include <vector>
using namespace std;

class dsu {
  vector<int> rt, sz;

  public:
  //function
  int find(int i) { 
    if (i == rt[i]) return i;
    return i = find(rt[i]);
  }
  void tie(int i, int j) {
    i = find(i); j = find(j);
    if (i == j) return;
    if (sz[i] < sz[j]) swap(i, j);
    rt[j] = i; sz[i] += sz[j];
  }
  //constructor
  dsu(int n) { 
    rt.resize(n); 
    sz.assign(n, 1); 
    for (int i=0; i<n; ++i) root[i] = i;
  }
};
