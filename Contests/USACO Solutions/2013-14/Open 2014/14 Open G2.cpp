/*#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp>*/
#include <bits/stdc++.h>

using namespace std;
//using namespace __gnu_pbds;
 
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pi;
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

const int MOD = 1000000007;
double PI = 4*atan(1);

int N,Bx,By,cx,cy;
map<int,int> xval, yval;
vector<pair<pi,char>> pairs;
set<pair<int,char>> v[1<<17], h[1<<17];
ll ans = 0;

template<int SZ>
class LazySegTree { 
	public:
		ll sum[2*SZ], lazy[2*SZ]; 
		
		LazySegTree() {
			memset (sum,0,sizeof sum);
			memset (lazy,0,sizeof lazy);
		}
		
		void push(int ind, int L, int R) {
			sum[ind] += (R-L+1)*lazy[ind];
			if (L != R) lazy[2*ind] += lazy[ind], lazy[2*ind+1] += lazy[ind];
			lazy[ind] = 0;
		}
		
		void build() {
			for (int i = SZ-1; i > 0; --i) sum[i] = sum[2*i]+sum[2*i+1];
		}
		
		void pull(int ind) {
			sum[ind] = sum[2*ind]+sum[2*ind+1];
		}
		 
		ll qsum(int lo, int hi, int ind = 1, int L = 0, int R = SZ-1) {
			push(ind,L,R);
			if (lo > R || L > hi) return 0;
			if (lo <= L && R <= hi) return sum[ind];
			
			int M = (L+R)/2;
			return qsum(lo,hi,2*ind,L,M)+qsum(lo,hi,2*ind+1,M+1,R);
		}
		 
		void upd(int lo, int hi, int inc, int ind = 1, int L = 0, int R = SZ-1) { // take account for minimum as well
			push(ind,L,R);
			if (hi < L || R < lo) return;
			if (lo <= L && R <= hi) {
				lazy[ind] = inc;
				push(ind,L,R);
				return;
			}
			
			int M = (L+R)/2;
			upd(lo,hi,inc,2*ind,L,M); upd(lo,hi,inc,2*ind+1,M+1,R);
			pull(ind);
		}
};

ll numintersection(vector<pair<int,pi>> ver, vector<pair<int,pi>> hor) {
	LazySegTree<1<<17> x;
	ll ans = 0;
	vector<pair<int,pi>> query; // y, factor, x
	for (auto a: ver) {
		query.pb({a.s.f,{-1,a.f}});
		query.pb({a.s.s-1,{1,a.f}});
	}
	sort(query.begin(),query.end());
	sort(hor.begin(),hor.end());
	
	int i1 = 0, i2 = 0;
	F0R(i,1<<17) {
		while (i2 < hor.size() && hor[i2].f == i) {
			x.upd(hor[i2].s.f+1,hor[i2].s.s-1,1);
			i2++;
		}
		while (i1 < query.size() && query[i1].f == i) {
			ans += query[i1].s.f*x.qsum(query[i1].s.s,query[i1].s.s);
			i1++;
		}
	}
	return ans;
}
// intersection of lines with lazy segment tree

pair<vector<pair<int,pi>>,vector<pair<int,pi>>> gen(vector<pi> x) {
	pair<vector<pair<int,pi>>,vector<pair<int,pi>>> y;
	F0R(i,x.size()-1) {
		if (x[i].f == x[i+1].f) y.f.pb({x[i].f,{min(x[i].s,x[i+1].s),max(x[i].s,x[i+1].s)}});
		else y.s.pb({x[i].s,{min(x[i].f,x[i+1].f),max(x[i].f,x[i+1].f)}});
	}
	return y;
}

void init() {
	freopen("optics.in","r",stdin);
	freopen("optics.out","w",stdout);
	cin >> N >> Bx >> By;
	F0R(i,N) {
		int x,y; char c; cin >> x >> y; cin >> c;
		pairs.pb({{x,y},c});
		xval[x] = 1, yval[y] = 1;
	}
	xval[0] = yval[0] = 1;
	xval[Bx] = yval[By] = 1;
	for (auto a: xval) xval[a.f] = ++cx;
	for (auto a: yval) yval[a.f] = ++cy;
	F0R(i,pairs.size()) {
		pairs[i].f.f = xval[pairs[i].f.f];
		pairs[i].f.s = yval[pairs[i].f.s];
		v[pairs[i].f.f].insert({pairs[i].f.s,pairs[i].s});
		h[pairs[i].f.s].insert({pairs[i].f.f,pairs[i].s});
	}
	Bx = xval[Bx], By = yval[By];
}

vector<pi> point;
bool done[4];

bool on (pi a, pi b, pi x) {
	if (a > b) swap(a,b);
	if (x.f == a.f && x.f == b.f && a.s < x.s && x.s < b.s) return 1;
	if (x.s == a.s && x.s == b.s && a.f < x.f && x.f < b.f) return 1;
	return 0;
}

void get(int x, int y, char dir) {
	point.pb({x,y});
	if (dir == 'N') {
		auto it = v[x].ub({y,']'});
		
		pair<int,char> des;
		bool bad = 0;
		if (it == v[x].end()) des = {(1<<17)-1,'.'}, bad = 1;
		else des = *it;
		if (on({x,y},{x,des.f},{xval[0],yval[0]})) des.f = yval[0], bad = 1;
		if (on({x,y},{x,des.f},{Bx,By})) {
			done[3] = 1;
			des.f = By, bad = 1;
		}
		
		if (bad) {
			point.pb({x,des.f});
			return;
		}
		if (des.s == '/') get(x,des.f,'E');
		else get(x,des.f,'W');
	} else if (dir == 'S') {
		auto it = v[x].lb({y,'/'});
		
		pair<int,char> des;
		bool bad = 0;
		if (it == v[x].begin()) des = {0,'.'}, bad = 1;
		else des = *prev(it);
		
		if (on({x,y},{x,des.f},{xval[0],yval[0]})) des.f = yval[0], bad = 1;
		if (on({x,y},{x,des.f},{Bx,By})) {
			done[1] = 1;
			des.f = By, bad = 1;
		}
		//cout << "S " << x << " " << y << " " << des.f << " " << des.s << " " << point.size() << "\n";
		
		if (bad) {
			point.pb({x,des.f});
			return;
		}
		if (des.s == '/') get(x,des.f,'W');
		else get(x,des.f,'E');
	} else if (dir == 'E') {
		auto it = h[y].ub({x,']'});
		
		pair<int,char> des;
		bool bad = 0;
		if (it == h[y].end()) des = {(1<<17)-1,'.'}, bad = 1;
		else des = *it;
		if (on({x,y},{des.f,y},{xval[0],yval[0]})) des.f = xval[0], bad = 1;
		if (on({x,y},{des.f,y},{Bx,By})) {
			des.f = Bx, bad = 1;
			done[2] = 1;
		}
		
		if (bad) {		
			point.pb({des.f,y});
			return;
		}
		if (des.s == '/') get(des.f,y,'N');
		else get(des.f,y,'S');
	} else if (dir == 'W') {
		auto it = h[y].lb({x,'/'});
		
		pair<int,char> des;
		bool bad = 0;
		if (it == h[y].begin()) des = {0,'.'}, bad = 1;
		else des = *prev(it);
		if (on({x,y},{des.f,y},{xval[0],yval[0]})) des.f = xval[0], bad = 1;
		if (on({x,y},{des.f,y},{Bx,By})) {
			des.f = Bx, bad = 1;
			done[0] = 1;
		}
		
		if (bad) {
			point.pb({des.f,y});
			return;
		}
		if (des.s == '/') get(des.f,y,'S');
		else get(des.f,y,'N');
	}
}

void solve() {
	point.clear();
	get(xval[0],yval[0],'N');
	vector<pi> z = point;
	pair<vector<pair<int,pi>>,vector<pair<int,pi>>> z1 = gen(z);
	
	char dir[4] = {'E','N','W','S'};
	F0R(i,4) if (!done[i]) {
		point.clear();
		get(Bx,By,dir[i]);
		vector<pi> a = point;
		pair<vector<pair<int,pi>>,vector<pair<int,pi>>> a1 = gen(a);
		ans += numintersection(z1.f,a1.s);
		ans += numintersection(z1.s,a1.f);
	}
}

int main() {
	init();
	solve();
	cout << ans;
}
