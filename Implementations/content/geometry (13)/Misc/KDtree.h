/**
 * Description: nearest neighbor to point and squared dist
 * Time: Assume points are distributed uniformly at random. 
 	* Insertion and find nearest neighbor are $O(\log N)$,
 	* rectangle queries are $O(N^{1-1/D})$ on average.
 * Source: KACTL, Stanford
 	* https://en.wikipedia.org/wiki/K-d_tree
 	* https://www.cise.ufl.edu/class/cot5520sp15/CG_RangeKDtrees.pdf
 	* https://arxiv.org/pdf/1903.04936.pdf
 * Verification: 
 	* https://open.kattis.com/problems/closestpair1
 	* https://dmoj.ca/problem/wac5p7
 */

static const int D = 2; using P = array<int,D>;
const array<pi,D> ID{pi{-1e7,1e7},pi{-1e7,1e7}};

struct KDTree {
	int root = -1; vector<P> pos; vector<array<int,2>> chi;
	ll sq(ll x) { return x*x; }
	ll dist(const P& a, const P& b) { 
		ll d = 0; F0R(i,D) d += sq(a[i]-b[i]);
		return d; }
	ll minDist(const array<pi,D>& b, const P& loc) { 
		ll d = 0; F0R(i,2) d += sq(loc[i]-max(min(loc[i],b[i].s),b[i].f));
		return d; }
	pair<ll,int> query(int cur, int side, const array<pi,D>& b, const P& loc, pair<ll,int> ans) {
		if (cur == -1 || minDist(b,loc) >= ans.f) return ans;
		if (ckmin(ans.f,dist(pos[cur],loc))) ans.s = cur;
		array<array<pi,D>,2> B = {b,b};
		B[0][side].s = pos[cur][side]; B[1][side].f = pos[cur][side];
		vl ret(2); F0R(i,2) ret[i] = minDist(B[i],loc);
		int ind = 0; if (ret[1] < ret[0]) ind = 1;
		ans = query(chi[cur][ind],side^1,B[ind],loc,ans);
		ind ^= 1; ans = query(chi[cur][ind],side^1,B[ind],loc,ans);
		return ans;
	}
	void ins(int& cur, int side, int nex) {
		if (cur == -1) cur = nex;
		else ins(chi[cur][pos[nex][side] > pos[cur][side]],side^1,nex);
	}
	pair<ll,int> query(P p) { return query(root,0,ID,p,{INF,-1}); }
	int add(P p) {
		pos.pb(p); chi.pb({-1,-1});
		int ind = sz(pos)-1; ins(root,0,ind); return ind;
	}
};