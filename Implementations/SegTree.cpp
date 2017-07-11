#include <bits/stdc++.h>

using namespace std;

const int SZ = 100000;

int N,Q, segsum[2*SZ], segmax[2*SZ];

void modifysum(int p, int value) {  // set value at position p
  for (segsum[p += SZ] = value; p > 1; p >>= 1) segsum[p>>1] = segsum[p] + segsum[p^1];
}

void modifymax(int p, int value) {  // set value at position p
  for (segmax[p += SZ] = value; p > 1; p >>= 1) segmax[p>>1] = max(segmax[p],segmax[p^1]);
}

int qsum(int l, int r) {  // sum on interval [l, r)
  int res = 0;
  for (l += SZ, r += SZ; l < r; l >>= 1, r >>= 1) {
    if (l&1) res += segsum[l++];
    if (r&1) res += segsum[--r];
  }
  return res;
}

int qmax(int l, int r) {  
  int res = 0;
  for (l += SZ, r += SZ; l < r; l >>= 1, r >>= 1) {
    if (l&1) res = max(res,segmax[l++]);
    if (r&1) res = max(res,segmax[--r]);
  }
  return res;
}

int main() {
	
}
