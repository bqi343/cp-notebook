// https://github.com/kth-competitive-programming/kactl/blob/master/content/data-structures/Matrix.h

#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;
 
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
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

const int MOD = 1000000007;

template<int SZ> struct mat {
    array<array<ll,SZ>,SZ> d;
    
    mat() {
        F0R(i,SZ) F0R(j,SZ) d[i][j] = 0;
    }
    
    mat operator+(const mat& m) {
        mat<SZ> a;
        F0R(i,SZ) F0R(j,SZ) a.d[i][j] = (d[i][j]+m.d[i][j]) % MOD;
        return a;
    }
    
    mat operator*(const mat& m) {
        mat<SZ> a;
        F0R(i,SZ) F0R(j,SZ) F0R(k,SZ) 
            a.d[i][k] = (a.d[i][k]+d[i][j]*m.d[j][k]) % MOD;
        return a;
    }
    
    mat operator^(ll p) {
        mat<SZ> a, b(*this); 
        F0R(i,SZ) a.d[i][i] = 1;
        
        while (p) {
            if (p&1) a = a*b;
            b = b*b;
            p /= 2;
        }
        
        return a;
    }
    
    void print() {
        F0R(i,SZ) {
            F0R(j,SZ) cout << d[i][j] << " ";
            cout << "\n";
        }
        cout << "------------\n";
    }
};

int main() {
	ios_base::sync_with_stdio(0);cin.tie(0);
	mat<2> x; 
	x.d[0][0] = 1, x.d[1][0] = 2, x.d[1][1] = 1, x.d[0][1] = 3;
	x.print();
	
	mat<2> y = x*x;
	y.print();
	
	mat<2> z = x^5;
	z.print();
}

// read!
// ll vs. int!