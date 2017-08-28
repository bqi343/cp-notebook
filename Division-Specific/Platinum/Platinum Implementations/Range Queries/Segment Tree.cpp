// http://codeforces.com/blog/entry/18051
#include <bits/extc++.h>

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

template<int SZ>
class Seg {
	public:
		typedef int T;
		T seg[2*SZ], MN = 0;

		Seg() {
			memset(seg,0,sizeof seg);	
		}

		T comb(T a, T b) { return a+b; }

		void upd(int p, T value) {  // set value at position p
			for (seg[p += SZ] = value; p > 1; p >>= 1) seg[p>>1] = comb(seg[p],seg[p^1]);
		}
		
		void build() {
			for (int i = SZ-1; i > 0; --i) seg[i] = comb(seg[2*i],seg[2*i+1]);	
		}

		T query(int l, int r) {  // nterval [l, r)
			T res = MN;
			for (l += SZ, r += SZ; l < r; l >>= 1, r >>= 1) {
				if (l&1) res = comb(res,seg[l++]);
				if (r&1) res = comb(res,seg[--r]);
			}
			return res;
		}
};


int main() {
	Seg<1<<17> a;
	a.upd(0,10);
	a.upd(2,5);
	cout << a.query(0,3); // 15
}

// read!
// ll vs. int!