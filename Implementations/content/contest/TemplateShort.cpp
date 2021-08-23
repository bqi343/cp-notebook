#include <bits/stdc++.h>
using namespace std;
 
using ll = long long;
using db = long double; // or double if tight TL
using pi = pair<int,int>;
using vi = vector<int>;
#define tcT template<class T
tcT> using V = vector<T>; 

#define mp make_pair
#define f first
#define s second

#define sz(x) int((x).size())
#define all(x) begin(x), end(x)
#define rsz resize
#define bk back()
#define pb push_back

#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define ROF(i,a,b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i,a) ROF(i,0,a)
#define each(a,x) for (auto& a: x)

const int MOD = 1e9+7; // 998244353;
const db PI = acos((db)-1);
mt19937 rng(0); // or mt19937_64

tcT> bool ckmin(T& a, const T& b) {
	return b < a ? a = b, 1 : 0; } // set a = min(a,b)
tcT> bool ckmax(T& a, const T& b) {
	return a < b ? a = b, 1 : 0; }

int main() { cin.tie(0)->sync_with_stdio(0); }