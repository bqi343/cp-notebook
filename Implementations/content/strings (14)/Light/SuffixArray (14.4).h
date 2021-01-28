/**
 * Description: Sort suffixes. First element of \texttt{sa} is \texttt{sz(S)},
 	* \texttt{isa} is the inverse of \texttt{sa}, and \texttt{lcp} stores
 	* the longest common prefix between every two consecutive elements of \texttt{sa}.
 * Time: O(N\log N)
 * Source: SuprDewd, KACTL, majk, ekzhang (http://ekzlib.herokuapp.com)
 * Verification: 
	* https://open.kattis.com/problems/suffixsorting
	* https://judge.yosupo.jp/problem/suffixarray
 */

#include "RMQ.h"

struct SuffixArray {
	str S; int N; vi sa, isa, lcp;
	void init(str _S) { N = sz(S = _S)+1; genSa(); genLcp(); }
	void genSa() {
		sa = isa = vi(N); sa[0] = N-1; iota(1+all(sa),0);
		sort(1+all(sa),[&](int a, int b) { return S[a] < S[b]; });
		FOR(i,1,N) { int a = sa[i-1], b = sa[i];
			isa[b] = i > 1 && S[a] == S[b] ? isa[a] : i; }
		for (int len = 1; len < N; len *= 2) { // currently sorted by first len chars
			vi s(sa), is(isa), pos(N); iota(all(pos),0); 
			each(t,s) { int T = t-len; if (T >= 0) sa[pos[isa[T]]++] = T; }
			FOR(i,1,N) { int a = sa[i-1], b = sa[i];
				isa[b] = is[a] == is[b] && is[a+len] == is[b+len] ? isa[a] : i; }
		}
	}
	void genLcp() { // Kasai's Algo
		lcp = vi(N-1); int h = 0;
		F0R(b,N-1) { int a = sa[isa[b]-1];
			while (a+h < sz(S) && S[a+h] == S[b+h]) h ++;
			lcp[isa[b]-1] = h; if (h) h--; }
		R.init(lcp); /// if we cut off first chars of two strings
		/// with lcp h then remaining portions still have lcp h-1 
	}
	RMQ<int> R; 
	int getLCP(int a, int b) { // lcp of suffixes starting at a,b
		if (a == b) return sz(S)-a;
		int l = isa[a], r = isa[b]; if (l > r) swap(l,r);
		return R.query(l,r-1);
	}
};
