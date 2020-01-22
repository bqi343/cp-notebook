#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef vector<int> vi; 
 
#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define ROF(i,a,b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i,a) ROF(i,0,a)
#define trav(a,x) for (auto& a: x)
 
#define pb push_back
#define ub upper_bound
#define s second
 
void setIO(string name) {
	ios_base::sync_with_stdio(0); cin.tie(0);
	freopen((name+".in").c_str(),"r",stdin);
	freopen((name+".out").c_str(),"w",stdout);
}
 
const int MX = 100005;
 
template<class T, int SZ> struct BIT {
	T bit[SZ+1];
	void upd(int pos, T x) {
		for (; pos <= SZ; pos += (pos&-pos)) 
		bit[pos] += x;
	}
	T sum(int r) {
		T res = 0; for (; r; r -= (r&-r)) 
			res += bit[r];
		return res;
	}
	T query(int l, int r) { 
		return sum(r)-sum(l-1); 
	}	
};
 
BIT<ll,MX> A,B;
map<int,int> col[MX];
int st[MX], en[MX],sub[MX];
int N,Q;
vi adj[MX];
int co;
 
void dfs(int x, int y) {
	st[x] = ++co;
	trav(t,adj[x]) if (t != y) dfs(t,x);
	en[x] = co;
	sub[x] = en[x]-st[x]+1;
}
 
void upd(int x, int y) {
	A.upd(st[x],y); A.upd(en[x]+1,-y);
	B.upd(st[x],y*sub[x]);
}
 
int main() {
	setIO("snowcow");
	cin >> N >> Q;
	F0R(i,N-1) {
		int a,b; cin >> a >> b;
		adj[a].pb(b), adj[b].pb(a);
	}
	dfs(1,0);
	F0R(i,Q) {
		int t; cin >> t;
		if (t == 1) {
			int x,c; cin >> x >> c;
			auto it = col[c].ub(st[x]);
			if (it != begin(col[c]) && en[prev(it)->s] >= en[x]) continue;
			while (it != end(col[c]) && en[it->s] <= en[x]) {
				upd(it->s,-1);
				col[c].erase(it++);
			}
			col[c][st[x]] = x; upd(x,1);
		} else {
			int x; cin >> x;
			cout << sub[x]*A.sum(st[x])+B.query(st[x]+1,en[x]) << "\n";
		}
	}
}