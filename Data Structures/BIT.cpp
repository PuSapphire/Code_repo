#include <iostream>
using namespace std;

const int N = 1e5+5;
int bit[N];

void upd(int i, int v) {
  for (; i<N; i+=i&-i) bit[i] += v;
}
int qry(int i) {
  int s = 0;
  for(; i>0; i-=i&-i) s += bit[i];
  return s;
}
