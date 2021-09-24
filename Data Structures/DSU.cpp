#include <iostream>
#include <vector>
using namespace std;

class dsu {
  vector<int> root, sz;

  public:
  //function
  int find(int i) { 
    return (i == root[i])? i : root[i]=find(root[i]); 
  }
  void tie(int i, int j) {
    i = find(i); j = find(j);
    if (i == j) return;
    if (sz[i] > sz[j]) swap(i, j);
    root[i] = j; sz[j] += sz[i];
  }
  //constructor
  dsu(int n) { 
    root.resize(n); 
    sz.resize(n, 1); 
    for (int i=0; i<n; ++i) root[i] = i;
  }
};
