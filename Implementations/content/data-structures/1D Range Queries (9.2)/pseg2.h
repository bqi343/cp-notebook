/**
 * Description: Persistent min segtree with lazy incremental updates. 
 	* Unlike other lazy segtree, assumes that \texttt{d[cur].lazy} 
 	* is included in \texttt{d[cur].val} before propagating 
 	* \texttt{cur.} Less of a pain to use array of fixed size to 
 	* store data rather than vector. Maybe faster to have separate
 	* arrays for each of $\texttt{l,r,val,lazy}$.
 * Memory: O(N+Q\log N)
 * Time: O(\log N)
 * Source: CF, Franklyn Wang
 * Verification: 
 	* https://codeforces.com/contest/1090/problem/G
 	* https://codeforces.com/gym/102423/submission/70170291
 */ 

template<class T, int SZ> struct pseg {
	static const int LIM = 2e7;
	struct node { 
		int l,r; T val = 0,lazy = 0; 
		void inc(T x) { val += x, lazy += x; }
	};
	node d[LIM]; int nex = 0;
	//// HELPER
	int copy(int cur) { d[nex] = d[cur]; return nex++; }
	T comb(T a, T b) { return min(a,b); }
	void pull(int x){d[x].val=comb(d[d[x].l].val,d[d[x].r].val);} 
	void push(int cur, int L, int R) { 
		T& x = d[cur].lazy; if (!x) return;
		if (L != R) {
			d[d[cur].l = copy(d[cur].l)].inc(x);
			d[d[cur].r = copy(d[cur].r)].inc(x);
		}
		x = 0;
	}
	//// MAIN FUNCTIONS
	T query(int cur, int lo, int hi, int L, int R) {  
		if (lo <= L && R <= hi) return d[cur].val;
		if (R < lo || hi < L) return INF;
		int M = (L+R)/2;
		return d[cur].lazy+comb(query(d[cur].l,lo,hi,L,M),
							query(d[cur].r,lo,hi,M+1,R));
	}
	int upd(int cur, int lo, int hi, T v, int L, int R) {
		if (R < lo || hi < L) return cur;
		int x = copy(cur);
		if (lo <= L && R <= hi) { d[x].inc(v); return x; }
		push(x,L,R); int M = (L+R)/2;
		d[x].l = upd(d[x].l,lo,hi,v,L,M);
		d[x].r = upd(d[x].r,lo,hi,v,M+1,R);
		pull(x); return x;
	}
	int build(const vector<T>& arr, int L, int R) {
		int cur = nex++;
		if (L == R) {
			if (L < sz(arr)) d[cur].val = arr[L];
			return cur;
		}
		int M = (L+R)/2;
		d[cur].l = build(arr,L,M), d[cur].r = build(arr,M+1,R);
		pull(cur); return cur;
	}
	//// PUBLIC
	vi loc;
	void upd(int lo, int hi, T v) { 
		loc.pb(upd(loc.bk,lo,hi,v,0,SZ-1)); }
	T query(int ti, int lo, int hi) { 
		return query(loc[ti],lo,hi,0,SZ-1); }
	void build(const vector<T>&arr) {loc.pb(build(arr,0,SZ-1));}
};