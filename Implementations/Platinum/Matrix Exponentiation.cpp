#include <bits/stdc++.h>
  
using namespace std;
//using namespace __gnu_pbds;
  
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
//typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;
  
#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
  
#define mp make_pair
#define pb push_back
#define f first
#define s second
#define lb lower_bound
#define ub upper_bound
  
vector<vi> make(int sz) {
    vector<vi> ans;
    F0R(i,sz) {
        vi x;
        F0R(j,sz) x.pb(0);
        ans.pb(x);
    }
    return ans;
}
  
vector<vi> mult(vector<vi> x, vector<vi> y) {
    vector<vi> z = make(x.size());
    F0R(i,x.size()) F0R(j,x.size()) F0R(k,x.size()) 
        if (x[i][k] & y[k][j]) z[i][j] = 1;
    return z;
}
  
vector<vi> po(vector<vi> x, int p) {
    vector<vi> z = make(x.size());
    F0R(i,z.size()) z[i][i] = 1;
    while (p) {
        if (p & 1) z = mult(z,x);
        x = mult(x,x);
        p /= 2;
    }
    return z;
}
  
int main() {
    //can be sped up with bitset
}
