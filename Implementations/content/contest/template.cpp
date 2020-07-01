#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef long double ld;
typedef double db; //
typedef string str; //
//
typedef pair<int,int> pi;
typedef pair<ll,ll> pl; //
typedef pair<db,db> pd; //
//
typedef vector<int> vi; 
typedef vector<ll> vl; //
typedef vector<db> vd; //
typedef vector<str> vs; //
typedef vector<pi> vpi;
typedef vector<pl> vpl; //
typedef vector<pd> vpd; //

#define mp make_pair
#define f first
#define s second
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)
#define rall(x) (x).rbegin(), (x).rend() //
#define rsz resize
#define ins insert //
#define ft front() //
#define bk back()
#define pf push_front //
#define pb push_back
#define eb emplace_back //
#define lb lower_bound //
#define ub upper_bound //

#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define ROF(i,a,b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i,a) ROF(i,0,a)
#define trav(a,x) for (auto& a: x)

const int MOD = 1e9+7; // 998244353;
const int MX = 2e5+5; //
const ll INF = 1e18; //
const ld PI = acos((ld)-1);
const int xd[4] = {1,0,-1,0}, yd[4] = {0,1,0,-1}; //
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count()); //
//
template<class T> bool ckmin(T& a, const T& b) { 
	return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { //
	return a < b ? a = b, 1 : 0; } //
constexpr int pct(int x) { return __builtin_popcount(x); } //
constexpr int bits(int x) { return 31-__builtin_clz(x); } // floor(log2(x)) //
constexpr int cdiv(int a, int b) { return a/b+!(a<0||a%b == 0); } // division of a by b rounded up, assumes b > 0 //
// IGNORE
int fstTrue(function<bool(int)> f, int lo, int hi) {
	hi ++; assert(lo <= hi); // assuming f is increasing
	while (lo < hi) { // find first index such that f is true 
		int mid = (lo+hi)/2; 
		f(mid) ? hi = mid : lo = mid+1; 
	} 
	return lo;
}
template<class T> void remDup(vector<T>& v) { 
	sort(all(v)); v.erase(unique(all(v)),end(v)); }
// IGNORE
//
int main() { ios_base::sync_with_stdio(0); cin.tie(0); }