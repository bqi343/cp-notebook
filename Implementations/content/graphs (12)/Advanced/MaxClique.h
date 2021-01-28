/**
 * Description: Quickly finds a maximum clique of a graph (given as symmetric bitset
	* matrix; self-edges not allowed). To find maximum independent set consider complement.
 * Source: KACTL (added by chilli)
 	* https://github.com/kth-competitive-programming/kactl/blob/master/content/graph/MaximumClique.h
 	* https://en.wikipedia.org/wiki/MaxCliqueDyn_maximum_clique_algorithm
 * Time: Runs in about 1s for $n=155$ and worst case random graphs ($p=.90$). 
	* Faster for sparse graphs.
 */

struct MaxClique {
	db limit = 0.025, pk = 0; // # of steps
	struct Vertex { int i, d=0; Vertex(int _i):i(_i){} };
	typedef vector<Vertex> vv; vv V;
	vector<bitset<200>> e; vector<vi> C; // colors
	vi qmax,q,S,old; // max/current clique, sum # steps up to lev
	void init(vv& r) { // v.d -> degree
		each(v,r) { v.d = 0; each(j,r) v.d += e[v.i][j.i]; } 
		sort(all(r),[](Vertex a,Vertex b) { return a.d > b.d; });
		int mxD = r[0].d; F0R(i,sz(r)) r[i].d = min(i,mxD)+1;
	}
	void expand(vv& R, int lev = 1) {
		S[lev] += S[lev-1]-old[lev]; old[lev] = S[lev-1]; 
		while (sz(R)) {
			if (sz(q)+R.bk.d <= sz(qmax)) return; // no larger clique
			q.pb(R.bk.i); // insert node with max col into clique
			vv T; each(v,R) if (e[R.bk.i][v.i]) T.pb({v.i});
			if (sz(T)) {
				if (S[lev]++/++pk < limit) init(T); // recalc degs
				int j = 0, mxk = 1, mnk = max(sz(qmax)-sz(q)+1,1);
				C[1].clear(), C[2].clear();
				each(v,T) {
					int k = 1; auto f = [&](int i) { return e[v.i][i]; };
					while (any_of(all(C[k]),f)) k ++; /// while common edge ++
					if (k > mxk) mxk = k, C[mxk+1].clear(); // new set
					if (k < mnk) T[j++].i = v.i;
					C[k].pb(v.i);
				}
				if (j > 0) T[j-1].d = 0; // >=1 vert >=j part of clique
				FOR(k,mnk,mxk+1) each(i,C[k]) T[j].i = i, T[j++].d = k;
				expand(T,lev+1);
			} else if (sz(q) > sz(qmax)) qmax = q;
			q.pop_back(), R.pop_back(); // R.bk not in set
		}
	}
	vi solve(vector<bitset<200>> conn) { 
		e = conn; C.rsz(sz(e)+1), S.rsz(sz(C)), old = S;
		F0R(i,sz(e)) V.pb({i}); 
		init(V), expand(V); return qmax; 
	}
};
