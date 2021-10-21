#include <iostream>

using namespace std;

const int SZ = 100;
int bit[SZ+1]

void update (int i, int v) {
  for (; i <= SZ; i += i&-i)
    bit[i] += v;
};

int query (int i) {
  int s = 0;
  for (; i > 0; i -= i&-i)
    s += bit[i];
  return s;
};
