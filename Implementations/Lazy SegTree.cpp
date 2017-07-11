#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
const int SZ = 1<<21;
 
ll mina[SZ], suma[SZ], lazy[SZ]; 
 
void push(int ind, int low, int high) {
	mina[ind] += lazy[ind];
    suma[ind] += (high-low+1)*lazy[ind];
    if (low != high) lazy[2*ind] += lazy[ind], lazy[2*ind+1] += lazy[ind];
    lazy[ind] = 0;
}
 
void pull(int ind) {
    suma[ind] = suma[2*ind]+suma[2*ind+1];
    mina[ind] = min(mina[2*ind],mina[2*ind+1]);
}
 
ll qmin(int ind, int low, int high, int L, int R) {
	push(ind,low,high);
    if (low > R || high < L) return 1000000007;
    if (L <= low && high <= R) return mina[ind];
    return min(qmin(2*ind,low,(low+high)/2,L,R),qmin(2*ind+1,(low+high)/2+1,high,L,R));
}
 
ll qsum(int ind, int low, int high, int L, int R) {
	push(ind,low,high);
    if (low > R || L > high) return 0;
    if (L <= low && high <= R) return suma[ind];
    return qsum(2*ind,low,(low+high)/2,L,R)+qsum(2*ind+1,(low+high)/2+1,high,L,R);
}
 
void update(int ind, int low, int high, int L, int R, int inc) { // take account for minimum as well
    push(ind,low,high);
    if (high < L || R < low) return;
    if (L <= low && high <= R) {
        suma[ind] += (high-low+1)*inc, mina[ind] += inc;
        if (low != high) lazy[2*ind] += inc, lazy[2*ind+1] += inc;
        return;
    }
    update(2*ind,low,(low+high)/2,L,R,inc);
    update(2*ind+1,(low+high)/2+1,high,L,R,inc);
    pull(ind);
}
 
int main() {
 
}
