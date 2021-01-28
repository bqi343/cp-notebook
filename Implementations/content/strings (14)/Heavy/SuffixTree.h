/**
 * Description: Used infrequently. Ukkonen's algorithm for suffix tree. Longest
   * non-unique suffix of \texttt{s} has length \texttt{len[p]+lef} after each
   * call to \texttt{add} terminates. Each iteration of loop within \texttt{add}
   * decreases this quantity by one.
 * Time: O(N\log \sum)
 * Source: *
 * Verification: *
 */

struct SuffixTree {
	str s; int N = 0;
	vi pos, len, lnk; vector<map<char,int>> to;
	int make(int POS, int LEN) { // lnk[x] is meaningful when x!=0 and len[x] != MOD
		pos.pb(POS); len.pb(LEN); lnk.pb(-1); to.eb(); return N++; }
	void add(int& p, int& lef, char c) { // our longest non-unique suffix is at node p with lef extra chars
		s += c; lef ++; int lst = 0;
		for (;lef;p?p=lnk[p]:lef--) { // if p is not root then lnk[p] must be defined
			while (lef>1 && lef>len[to[p][s[sz(s)-lef]]]) // traverse edges of suffix tree while you can
				p = to[p][s[sz(s)-lef]], lef -= len[p]; 
			char e = s[sz(s)-lef]; int& q = to[p][e]; // next edge of suffix tree
			if (!q) q = make(sz(s)-lef,MOD), lnk[lst] = p, lst = 0; // make new edge
			else {
				char t = s[pos[q]+lef-1]; 
				if (t == c) { lnk[lst] = p; return; } // suffix is not unique, done
				int u = make(pos[q],lef-1); // new node for the current suffix - 1, define its link
				to[u][c] = make(sz(s)-1,MOD); to[u][t] = q; // new node, old node
				pos[q] += lef-1; if (len[q] != MOD) len[q] -= lef-1;
				q = u, lnk[lst] = u, lst = u;
			}
		}
	}
	void init(str _s) {
		make(-1,0); int p = 0, lef = 0;
		each(c,_s) add(p,lef,c);
		add(p,lef,'$'); s.pop_back(); // terminal char
	}
	int maxPre(str x) { // max prefix of x which is substring
		for (int p = 0, ind = 0;;) {
			if (ind == sz(x) || !to[p].count(x[ind])) return ind;
			p = to[p][x[ind]];
			F0R(i,len[p]) {
				if (ind == sz(x) || x[ind] != s[pos[p]+i]) return ind;
				ind ++;
			}
		}
	}
	vi sa; // generate suffix array
	void genSa(int x = 0, int Len = 0) {
		if (!sz(to[x])) sa.pb(pos[x]-Len); // found terminal node
		else each(t,to[x]) genSa(t.s,Len+len[x]);
	}
};
