/**
 * Description: Permutation Tree, represents all contiguous subsequences
	 * of permutation whose values are contiguous (good). Works for both 0-
	 * and 1-indexed permutations. \texttt{typ[i]=1} (increasing) and 
	 * \texttt{typ[i]=2} (decreasing) represent join nodes - every contiguous 
	 * subsequence of its children is good. \texttt{typ[i]=0} represents a leaf 
	 * node or a cut node; no contiguous subsequence of its children with length > 1 
	 * is good. Note that a cut node must have $\ge 4$ children. \texttt{loc[i]}
	 * stores the node corresponding to the \texttt{i}-th element of the permutation.
 * Source: https://codeforces.com/blog/entry/78898
 * Verification: CERC17 Intrinsic Interval
 * Usage: PermTree P; P.init({0,1,2,3,5,4});
 */

typedef pi T;
const int SZ = 1<<19;
struct LazySeg { 
	const T ID = {MOD,0}; 
	T comb(T l, T r) { return l.f != r.f ? min(l,r) : T{l.f,l.s+r.s}; }
	T seg[2*SZ]; int lazy[2*SZ]; 
	LazySeg() { 
		F0R(i,2*SZ) lazy[i] = 0; 
		F0R(i,SZ) seg[SZ+i] = {0,1};
		ROF(i,1,SZ) seg[i] = comb(seg[2*i],seg[2*i+1]);
	}
	void push(int ind, int L, int R) { /// modify values for current node
		if (L != R) F0R(i,2) lazy[2*ind+i] += lazy[ind]; /// prop to children
		seg[ind].f += lazy[ind]; lazy[ind] = 0; 
	} // recalc values for current node
	void pull(int ind) { seg[ind] = comb(seg[2*ind],seg[2*ind+1]); }
	void build() { ROF(i,1,SZ) pull(i); }
	void upd(int lo,int hi,int inc,int ind=1,int L=0, int R=SZ-1) {
		push(ind,L,R); if (hi < L || R < lo) return;
		if (lo <= L && R <= hi) { 
			lazy[ind] = inc; push(ind,L,R); return; }
		int M = (L+R)/2; upd(lo,hi,inc,2*ind,L,M); 
		upd(lo,hi,inc,2*ind+1,M+1,R); pull(ind);
	}
	pi query(int lo, int hi, int ind = 1, int L = 0, int R = SZ-1) {
		push(ind,L,R); if (hi < L || R < lo) return {MOD,0};
		if (lo <= L && R <= hi) return seg[ind];
		int M = (L+R)/2;
		return comb(query(lo,hi,2*ind,L,M),query(lo,hi,2*ind+1,M+1,R));
	}
};

struct PermTree {
	vi P; int n; // N = number of nodes in perm tree
	int N = 0, root; vector<vi> child;
	vpi inter, range; vi typ, loc; // inter = index range in perm
	void init(vi _P) {
		P = _P; n = sz(P); LazySeg L; 
		vi mn{-1}, mx{-1}, st;
		F0R(i,n) { // L stores max-min-len for each range
			if (i) L.upd(0,i-1,-1);
			{
				while (mn.bk != -1 && P[mn.bk] > P[i]) {
					int t = mn.bk; mn.pop_back();
					L.upd(mn.bk+1,t,P[t]);
				}
				L.upd(mn.bk+1,i,-P[i]); mn.pb(i); 
			}
			{
				while (mx.bk != -1 && P[mx.bk] < P[i]) {
					int t = mx.bk; mx.pop_back();
					L.upd(mx.bk+1,t,-P[t]);
				}
				L.upd(mx.bk+1,i,P[i]); mx.pb(i);
			}
			int cur = N++; loc.pb(cur);
			inter.pb({i,i}); range.pb({P[i],P[i]}); typ.pb(0); child.eb();
			auto add = [](pi a, pi b) -> pi { return {min(a.f,b.f),max(a.s,b.s)}; };
			auto adj = [&](int x, int y) { pi a = range[x], b = range[y]; 
				return a.s+1 == b.f || b.s+1 == a.f; };
			while (sz(st)) {
				if (adj(st.bk,cur)) {
					if (sz(child[st.bk]) && adj(child[st.bk].bk,cur)) {
						assert(typ[st.bk]); // join node
						inter[st.bk] = add(inter[st.bk],inter[cur]);
						range[st.bk] = add(range[st.bk],range[cur]);
						child[st.bk].pb(cur); cur = st.bk; st.pop_back();
					} else { // make new join node
						int CUR = N++;
						inter.pb(add(inter[cur],inter[st.bk]));
						range.pb(add(range[cur],range[st.bk]));
						typ.pb(range[st.bk] < range[cur] ? 1 : 2);
						child.pb({st.bk,cur}); cur = CUR; st.pop_back();
					}
					continue;
				}
				if (L.query(0,inter[cur].f-1).f != 0) break;
				int CUR = N++;
				inter.pb(inter[cur]); range.pb(range[cur]); typ.pb(0); child.pb({cur});
				auto len = [](pi p) { return p.s-p.f; };
				do {
					assert(sz(st));
					inter[CUR] = add(inter[CUR],inter[st.bk]);
					range[CUR] = add(range[CUR],range[st.bk]);
					child[CUR].pb(st.bk); st.pop_back();
				} while (len(inter.bk) != len(range.bk));
				rev(child[CUR]); cur = CUR;
			}
			st.pb(cur);
		}
		assert(sz(st) == 1); root = st.bk;
		F0R(i,N) if (typ[i]) {
			if (typ[i] == 1) {
				FOR(j,1,sz(child[i])) assert(range[child[i][j-1]].s+1 == range[child[i][j]].f);
			} else {
				FOR(j,1,sz(child[i])) assert(range[child[i][j-1]].f-1 == range[child[i][j]].s);
			}
		}
		dbg(root);
		F0R(i,N) dbg(i,typ[i],inter[i],range[i],child[i]);
	} // traverse tree by starting at root and DFSing through child
};