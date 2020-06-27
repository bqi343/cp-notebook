/**
 * Description: Insert and delete elements from any position. \texttt{sz(v)-1=min(k,length of LIS)}.
 * Time: O(k(n+q)\log n)
 * Source: https://arxiv.org/abs/1309.7724
   * https://codeforces.com/blog/entry/75266?
 * Verification: GP of Wroclaw 2020 D
 */

int n,k;
vi c, lef;
vector<pt> v;
vector<bool> in;

struct tnode {
	int pri, x; pt c[2]; // essential
	tnode (int _x) {
		pri = rng(); x = _x;
		c[0] = c[1] = NULL;
	}
};
void tour(pt x, vi& v) { // print values of nodes, 
	if (!x) return; // inorder traversal
	tour(x->c[0],v); v.pb(x->x); tour(x->c[1],v);
}
pair<pt,pt> split(pt t, int v) { // split by x, >= v goes to the right
	if (!t) return {t,t};
	if (t->x >= v) {
		auto p = split(t->c[0], v); t->c[0] = p.s;
		return {p.f,t};
	} else {
		auto p = split(t->c[1], v); t->c[1] = p.f;
		return {t,p.s};
	}
}
pair<pt,pt> splitY(pt t, int v) { // <= v goes to right
	if (!t) return {t,t};
	if (c[t->x] <= v) {
		auto p = splitY(t->c[0], v); t->c[0] = p.s;
		return {p.f,t};
	} else {
		auto p = splitY(t->c[1], v); t->c[1] = p.f;
		return {t,p.s};
	}
}
pt merge(pt l, pt r) { // merge treaps, keys in left < keys in right
	if (!l || !r) return l?:r;
	pt t;
	if (l->pri > r->pri) l->c[1] = merge(l->c[1],r), t = l;
	else r->c[0] = merge(l,r->c[0]), t = r;
	return t;
}
int firstX(pt p) { // min x in treap
	if (!p) return MOD;
	while (p->c[0]) p = p->c[0];
	return p->x;
} 
int lastY(pt p) { // min c-value in treap
	if (!p) return MOD;
	while (p->c[1]) p = p->c[1];
	return c[p->x];
} 
int minY(pt& a, int x) { // min y across < x
	auto b = split(a,x); int res = lastY(b.f);
	a = merge(b.f,b.s); return res;
} 

vi vec(pt p) { vi u; tour(p,u); return u; } // for debugging
pair<pt,pt> getIns(pt a, pt b) {
	if (!b) return {a,NULL};
	auto x = split(a,firstX(b));
	auto y = splitY(x.s,lastY(b)); // > on left, <= on right
	return {merge(x.f,merge(b,y.s)),y.f}; // same, not same
}
pair<pair<pt,pt>,pi> getDel(pt a, int nexX, int nexY) {
	auto x = split(a,nexX), y = splitY(x.f,nexY);
	int NEXx = firstX(x.s), NEXy = lastY(y.f);
	return {{merge(y.f,x.s),y.s},{NEXx,NEXy}};
}
pt insMid(pt a, pt b) {
	if (!b) return a;
	auto x = split(a,b->x);
	return merge(merge(x.f,b),x.s);
}
void DEL(int ind, int nexX, int nexY) {
	if (ind >= sz(v)) return;
	pair<pt,pt> z; pi oops;
	tie(z,oops) = getDel(v[ind],nexX,nexY);
	v[ind-1] = insMid(v[ind-1],z.s); v[ind] = z.f;
	DEL(ind+1,oops.f,oops.s);
}

bool inside(pt& a, int b) {
	auto x = split(a,b), y = split(x.s,b+1);
	bool ok = (y.f != NULL); 
	a = merge(x.f,merge(y.f,y.s));
	return ok;
}

void del(int x) {
	assert(in[x]); in[x] = 0; lef.pb(x);
	int ind = 0; while (ind < sz(v) && !inside(v[ind],x)) ind ++;
	auto a = split(v[ind],x), b = split(a.s,x+1);
	int nexX = firstX(b.s), nexY = lastY(a.f);
	v[ind] = merge(a.f,b.s);
	DEL(ind+1,nexX,nexY);
	while (!v.bk) v.pop_back();
}

void INS(int ind, pt p) { // OK
	if (!p) return;
	if (ind >= sz(v)) v.pb(NULL);
	pair<pt,pt> z = getIns(v[ind],p);
	v[ind] = z.f; INS(ind+1,z.s);
}

void ins(int x) {
	assert(!in[x]); in[x] = 1;
	int ind = 0; 
	while (ind+1 < sz(v) && minY(v[ind+1],x) < c[x]) ind ++;
	INS(ind+1,new tnode(x));
}

void solve() {
	re(n,k); c.rsz(n+1); FOR(i,1,n+1) re(c[i]);
	lef.clear(); FOR(i,1,n+1) lef.pb(i);
	in = vector<bool>(n+1);
	v = {new tnode(0)};
	int q; re(q);
	F0R(i,q) {
		int p,val; re(p,val);
		if (in[p]) del(p);
		c[p] = val;
		while (sz(lef) && sz(v) <= k) {
			ins(lef.bk);
			lef.pop_back();
		}
		ps(sz(v)-1);
	}
}