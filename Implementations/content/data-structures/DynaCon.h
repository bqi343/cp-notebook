/**
 * Description: Dynamic Connectivity with Euler Tour Trees
 * Time: O(\log^2 N)
 * Source:
 	* https://courses.csail.mit.edu/6.851/spring12/scribe/L20.pdf
 * Verification:
 	* https://www.spoj.com/problems/DYNACON1/ (data is very weak though)
 	* https://dmoj.ca/problem/wac4p7 (first two subtasks)
 */

// TREAP OPERATIONS

constexpr int MAX_N = 1e5+5, MAX_M = 1e5+5;

int N;

template<int SZ> struct Treap {
	int cnt, pri[SZ], par[SZ], sz[SZ]; // ETT node for each edge
	bitset<SZ> specialNode, existsSpecialNode;
	bitset<SZ> specialEdge, existsSpecialEdge;
	int edgeId[SZ];
	AR<int,2> c[SZ];
	int makeEdge(int label) {
		edgeId[++cnt] = label; pri[cnt] = rng(); sz[cnt] = 1;
		return cnt;
	}
	void calc(int x) {
		int a = c[x][0], b = c[x][1];
		sz[x] = 1+sz[a]+sz[b];
		existsSpecialNode[x]=specialNode[x]|existsSpecialNode[a]|existsSpecialNode[b];
		existsSpecialEdge[x]=specialEdge[x]|existsSpecialEdge[a]|existsSpecialEdge[b];
	}
	int extractSpecialEdge(int x) {
		int a = c[x][0], b = c[x][1], res;
		assert(existsSpecialEdge[x]);
		if (specialEdge[x]) {
			res = edgeId[x], specialEdge[x] = 0;
		} else if (existsSpecialEdge[a]) res = extractSpecialEdge(a);
		else res = extractSpecialEdge(b);
		assert(res >= 0); calc(x); return res;
	}
	int extractSpecialNode(int x) {
		assert(existsSpecialNode[x]);
		int a = c[x][0], b = c[x][1];
		if (specialNode[x]) return x;
		if (existsSpecialNode[a]) return extractSpecialNode(a);
		return extractSpecialNode(b);
	}
	int getRoot(int x) { // get top node in ETT
		while (par[x]) x = par[x];
		return x;
	}
	bool con(int a, int b) { return getRoot(a) == getRoot(b); }
	void link(int x, int d, int y) { // set d-th child of x to y
		assert(x); assert(d == 0 || d == 1);
		assert(!c[x][d]), c[x][d] = y; 
		if (y) assert(!par[y]), par[y] = x;
		calc(x);
	}
	int dis(int x, int d) { // disconnected d-th child of x
		assert(x); assert(d == 0 || d == 1);
		int y = c[x][d]; c[x][d] = 0; calc(x);
		if (y) assert(par[y] == x), par[y] = 0;
		return y;
	}
	pi split(int x) { // x and everything to right goes in p.s
		// everything else goes in p.f
		pi p = {dis(x,0),x};
		while (par[x]) {
			int y = par[x];
			if (c[y][0] == x) {
				dis(y,0), link(y,0,p.s),  p.s = y;
			} else {
				assert(c[y][1] == x);
				dis(y,1), link(y,1,p.f); p.f = y;
			}
			x = y;
		}
		assert(!par[p.f] && !par[p.s]); return p;
	}
	int merge(int x, int y) {
		assert(!par[x] && !par[y]);
		if (!x || !y) return max(x,y);
		if (pri[x] > pri[y]) {
			int X = dis(x,1);
			link(x,1,merge(X,y));
			return x;
		} else {
			int Y = dis(y,0);
			link(y,0,merge(x,Y));
			return y;
		}
	}
	int getFirst(int x) {
		if (!x) return 0;
		while (c[x][0]) x = c[x][0];
		return x;
	}
	int makeFirst(int x) { // rotate ETT of x such that x is first
		assert(x); pi p = split(x); return merge(p.s,p.f); }
	void remFirst(int x) { // remove first node of ETT rooted at x
		assert(x && !par[x]);
		while (c[x][0]) x = c[x][0];
		int y = dis(x,1), p = par[x];
		if (p) dis(p,0), link(p,0,y);
		while (p) {
			calc(p);
			p = par[p];
		}
	}
	int reroot(int x) { 
		assert(1 <= x && x <= N); return makeFirst(x); }
	void markSpecialNode(int x, int val) {
		if (specialNode[x] == val) return;
		for(specialNode[x]=val;x;x=par[x]) 
			calc(x);
	}
};


vpi ed; vi edgeLevel; vb span; // vertices which edge connects, level of edge, whether edge is part of spanning tree
struct ETT {
	Treap<MAX_N+2*MAX_M> T;
	int level; // level of ETT, 0 to log(N)
	vpi nonSpan[MAX_N]; // list of non-spanning edges adjacent to each vertex
	pi edgeNodes[MAX_M]; // list of spanning edges
	int spanEdges;
	void init(int _level) {
		level = _level; 
		F0R(i,N) T.makeEdge(-1);
	}
	bool con(int a, int b) { return T.con(a,b); }
	bool add(int label) {
		assert(level <= edgeLevel[label]);
		int a = ed[label].f, b = ed[label].s;
		if (con(a,b)) {
			assert(!span[label]);
			nonSpan[a].pb({label,b}), nonSpan[b].pb({label,a});
			T.markSpecialNode(a,1), T.markSpecialNode(b,1); 
			return 0;
		} else {
			spanEdges ++;
			span[label] = 1;
			int ta = T.reroot(a), tb = T.reroot(b); 
			if (ta||tb) assert(ta != tb);
			int x = T.makeEdge(label), y = T.makeEdge(label);
			edgeNodes[label] = {x,y};
			if (level == edgeLevel[label]) {
				T.specialEdge[x] = T.existsSpecialEdge[x] = 1;
			}
			T.merge(T.merge(ta,x),T.merge(tb,y));
			return 1;
		}
	}
	void rem(int label) { // remove smth that's in the spanning tree
		int x,y; tie(x,y) = edgeNodes[label]; assert(x && y);
		T.makeFirst(x);
		pi p = T.split(y); assert(T.getFirst(p.f) == x && T.getFirst(p.s) == y);
		T.remFirst(p.f), T.remFirst(p.s); spanEdges --;
	}
	pair<vi,int> replace(int x, int y) {
		// dbg("FIND REPLACEMENT",level,x,y);
		x = T.getRoot(x), y = T.getRoot(y); // try to find replacement edge for (x,y)
		if (T.sz[x] > T.sz[y]) swap(x,y); // loop over smaller component
		pair<vi,int> res = {{},-1};
		while (T.existsSpecialEdge[x]) {
			// increase levels of all spanning tree edges
			int ind = T.extractSpecialEdge(x);
			assert(edgeLevel[ind] == level); 
			res.f.pb(ind); edgeLevel[ind] ++;
		}
		while (T.existsSpecialNode[x]) {
			int t = T.extractSpecialNode(x);
			while (sz(nonSpan[t])) {
				pi u = nonSpan[t].bk; nonSpan[t].pop_back();
				if (edgeLevel[u.f] > level || span[u.f]) continue; // outdated information
				assert(edgeLevel[u.f] == level);
				int r = T.getRoot(u.s); 
				assert(r == x || r == y);
				if (r == y) { res.s = u.f; return res; } // wow done!
				res.f.pb(u.f); edgeLevel[u.f] ++;
			}
			T.markSpecialNode(t,0);
		}
		return res;
	}
};

struct DynaCon {
	ETT E[17]; void init() { F0R(i,17) E[i].init(i); }
	bool con(int a, int b) { return E[0].con(a,b); }
	map<pi,vi> edges;
	void add(int a, int b) { // add an edge
		if (a > b) swap(a,b);
		// dbg("add",a,b);
		int label = sz(ed);
		ed.pb({a,b}); edgeLevel.pb(0); span.pb(0);
		edges[{a,b}].pb(label); 
		E[0].add(label);
	}
	void rem(int a, int b) { // remove an edge
		if (a > b) swap(a,b);
		vi& edgeLabels = edges[{a,b}]; assert(sz(edgeLabels));
		int label = edgeLabels.bk; edgeLabels.pop_back();
		REM(label);
	}
	void REM(int label) {
		int L = edgeLevel[label]; edgeLevel[label] = MOD;
		if (!span[label]) return;
		F0R(i,L+1) E[i].rem(label); // remove from spanning tree
		while (L >= 0) {
			pair<vi,int> p = E[L].replace(ed[label].f,ed[label].s);
			each(t,p.f) {
				assert(edgeLevel[t] == L+1);
				if (span[t]) assert(E[L+1].add(t));
				else {
					assert(!E[L+1].add(t));
				}
			}
			if (p.s != -1) { // found a replacement edge!
				assert(!span[p.s]);
				F0R(i,L+1) assert(E[i].add(p.s));
				assert(span[p.s]);
				return;
			}
			L --;
		}
	}
};

DynaCon D;
set<pi> lo, hi;
int a[MAX_M],b[MAX_M],d[MAX_M],t[MAX_M];
bool LO[MAX_M];

int main() {
	int M,Q; re(N,M,Q);
	D.init();
	F0R(i,M) {
		re(a[i],b[i],d[i],t[i]);
	}
	vi edgeInds(M); iota(all(edgeInds),0);
	sort(all(edgeInds),[&](int x, int y) { return d[x] < d[y]; });
	each(i,edgeInds) hi.insert({t[i],i});
	V<AR<int,3>> query;
	F0R(i,Q) {
		int x,y; re(x,y);
		query.pb({x,y,i});
	}
	sort(all(query));
	int ind = 0;
	vb ans(Q);
	each(_,query) {
		while (ind < sz(edgeInds) && d[edgeInds[ind]] < _[0]) {
			int x = edgeInds[ind++];
			if (LO[x]) lo.erase({t[x],x}), D.rem(a[x],b[x]);
			else hi.erase({t[x],x});
		}
		while (sz(hi) && D.E[0].spanEdges < N-1) {
			int x = hi.begin()->s; hi.erase(begin(hi));
			lo.insert({t[x],x}); D.add(a[x],b[x]); LO[x] = 1;
		}
		if (D.E[0].spanEdges == N-1 && lo.rbegin()->f <= _[1]) {
			ans[_[2]] = 1;
		}
	}
	for (bool a: ans) ps(a?"YES":"NO");
}
