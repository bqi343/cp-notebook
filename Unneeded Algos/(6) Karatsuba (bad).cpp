#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;
 
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pi;
template <class T> using Tree = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;

#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)

#define sz(x) (int)(x).size()
#define mp make_pair
#define pb push_back
#define f first
#define s second
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()

const int MOD = 1000000007;

void prin(vi& x) {
    F0Rd(i,sz(x)) cout << x[i];
    cout << "\n";
}

void normalize (vi& x) {
    F0R(i,sz(x)) {
        if (x[i] > 9) {
            if (i+1 == sz(x)) x.pb(0);
            x[i+1] += x[i]/10, x[i] %= 10;
        } else if (x[i] < 0) {
            int t = (-x[i]+9)/10;
            x[i] += 10*t, x[i+1] -= t;
        }
    }
    while (sz(x) && !x.back()) x.pop_back();
}

vi operator+(vi a, vi b) {
    if (sz(a) < sz(b)) swap(a,b);
    F0R(i,sz(b)) a[i] += b[i];
    normalize(a); return a;
}

vi operator-(vi a, vi b) {
    F0R(i,sz(b)) a[i] -= b[i];
    normalize(a); return a;
}

vi shift(vi x, int sz) {
    x.insert(x.begin(),sz,0);
    return x;
}

vi mult(vi a, vi b) {
    if (sz(a) < sz(b)) swap(a,b);
    if (sz(b) == 0) return {};
    
    if (sz(a) == 1) {
        vi c = {a[0]*b[0]}; normalize(c);
        return c;
    }
    int sz = (sz(a)+1)/2; b.resize(max(sz(b),sz));
    
    vi a2(a.begin()+sz,a.end()); a.resize(sz);
    vi b2;
    if (sz(b2)<sz) {
        
    }
    
    vi z0 = mult(a1,b1);
    vi z1 = mult(a1+a2,b1+b2);
    vi z2 = mult(a2,b2);
    
    return shift(z2,2*sz)+shift(z1-z2-z0,sz)+z0;
}

vi brute(vi a, vi b) {
    vi c(sz(a)+sz(b)-1);
    F0R(i,sz(a)) F0R(j,sz(b)) c[i+j] += a[i]*b[j];
    normalize(c);
    return c;
}

int main() {
	ios_base::sync_with_stdio(0);cin.tie(0);
	vi a, b;
	F0R(i,10000) a.pb(rand()%10), b.pb(rand()%10);
	vi x = mult(a,b);
	prin(a);
	prin(b);
	prin(x);
}

// read!read!read!read!read!read!read!read!read!read!read!read!read!read!read!read!
// ll vs. int!
