/**
 * Description: Euler Tour Tree using treap, each edge is
 	* represented by two nodes. Supports reroot, insert edge, 
 	* delete edge, get connected component. Can support
 	* aggregate over vertices in connected component by 
 	* introducing self-loops.
 * Time: O(\log N)
 * Source:
 	* https://codeforces.com/blog/entry/53265 (Rerooting dynamic Euler tour trees)
 	* https://codeforces.com/blog/entry/18369 (On Euler tour trees)
 * Verification:
 	* https://www.spoj.com/problems/DYNACON1/
 */

// TREAP OPERATIONS
int cnt, pri[MX], par[MX]; // ETT node for each edge
AR<int,2> c[MX];

int getRoot(int x) { // get top node in ETT
	while (par[x]) x = par[x];
	return x;
}
void link(int x, int d, int y) { // set d-th child of x to y
	assert(x); assert(d == 0 || d == 1);
	assert(!c[x][d]), c[x][d] = y; 
	if (y) assert(!par[y]), par[y] = x;
}
int dis(int x, int d) { // disconnected d-th child of x
	assert(x); assert(d == 0 || d == 1);
	int y = c[x][d]; c[x][d] = 0;
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

// int getFirst(int x) {
// 	if (!x) return 0;
// 	while (c[x][0]) x = c[x][0];
// 	return x;
// }
int makeFirst(int x) { // rotate ETT of x such that x is first
	assert(x); pi p = split(x);
	return merge(p.s,p.f);
}
void remFirst(int x) { // remove first node of ETT rooted at x
	assert(x && !par[x]);
	while (c[x][0]) x = c[x][0];
	int y = dis(x,1), p = par[x];
	if (p) dis(p,0), link(p,0,y);
}

// ETT OPERATIONS
map<int,int> adj[MX];
int makeEdge(int a, int b) {
	adj[a][b] = ++cnt; pri[cnt] = rng();
	return cnt;
}
int reroot(int x) { // make edge beginning with x
	if (!sz(adj[x])) return 0;
	return makeFirst(begin(adj[x])->s);
}
bool con(int a, int b) {
	if (!sz(adj[a]) || !sz(adj[b])) return 0;
	a = begin(adj[a])->s, b = begin(adj[b])->s;
	return getRoot(a) == getRoot(b);
}
void add(int a, int b) { // connect A and B with edge
	int ta = reroot(a), tb = reroot(b); if (ta||tb) assert(ta != tb);
	int x = makeEdge(a,b), y = makeEdge(b,a); // make two nodes for new edge
	merge(merge(ta,x),merge(tb,y));
}
void rem(int a, int b) {
	int x = adj[a][b], y = adj[b][a]; makeFirst(x);
	pi p = split(y); // assert(getFirst(p.f) == x && getFirst(p.s) == y);
	remFirst(p.f), remFirst(p.s);
	adj[a].erase(b), adj[b].erase(a);
}

int main() {
	int N,M; re(N,M);
	F0R(i,M) {
		str s; int A,B; re(s,A,B);
		if (s == "add") {
			add(A,B);
		} else if (s == "rem") {
			rem(A,B);
		} else {
			if (con(A,B)) ps("YES");
			else ps("NO");
		}
	}
}