// #include<iostream>
#include<vector>
#include<algorithm>
#include<fstream>
  
using namespace std;
//using namespace __gnu_pbds;
  
typedef long long ll;
typedef vector<int> vi;
typedef pair<ll,ll> pii;
//typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;
  
#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
  
#define mp make_pair
#define pb push_back
#define f first
#define s second
  
ll cross(pii O, pii A, pii B) {
    return (A.f - O.f) * (B.s - O.s) - (A.s - O.s) * (B.f - O.f);
}
  
vector<pii> convex_hull(vector<pii> P) { 
    int n = P.size(), k = 0;
    vector<pii> H(2*n);
    //lower
    F0R(i,n) {
        while (k >= 2 && cross(H[k-2], H[k-1], P[i]) <= 0) k--;
        H[k++] = P[i];
    }
    // upper
    for (int i = n-2, t = k+1; i >= 0; i--) {
        while (k >= t && cross(H[k-2], H[k-1], P[i]) <= 0) k--;
        H[k++] = P[i];
    }
    H.resize(k-1);
    return H;
}
  
int main() {
  
}
