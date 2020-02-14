/**
 * Description: Sort suffixes. 
 * Time: O(N\log N)
 * Source: SuprDewd, KACTL, majk, ekzhang (http://ekzlib.herokuapp.com)
 * Verification: 
	* http://usaco.org/index.php?page=viewproblem2&cpid=768
		* https://pastebin.com/y2Z9FYr6
	* https://open.kattis.com/problems/suffixsorting
	* https://codeforces.com/contest/1090/problem/J
 */

struct SuffixArray {
	str S; int N;
	void init(str _S) { S = _S, N = sz(S); genSa(), genLcp(); }
	vi sa, isa; // indices of suffixes in sorted order, inverses
	void genSa() {
		sa.rsz(N), isa.rsz(N); iota(all(sa),0);
		sort(all(sa),[&](int a, int b) { return S[a] < S[b]; });
		F0R(i,N) {
			bool same = i && S[sa[i]] == S[sa[i-1]];
			isa[sa[i]] = same ? isa[sa[i-1]] : i; 
		}
		for (int len = 1; len < N; len *= 2) { 
			// sufs currently sorted by first len chars
			vi is(isa), s(sa), nex(N); iota(all(nex),0); 
			FOR(i,-1,N) { // rearrange sufs by 2*len
				int s1 = (i == -1 ? N : s[i])-len; 
				if (s1 >= 0) sa[nex[isa[s1]]++] = s1; 
			} // to make faster, break when all ints in sa distinct
			F0R(i,N) { // update isa for 2*len
				bool same = i && sa[i-1]+len < N
							  && is[sa[i]] == is[sa[i-1]]
							  && is[sa[i]+len] == is[sa[i-1]+len]; 
				isa[sa[i]] = same ? isa[sa[i-1]] : i; 
			}
		}
	}
	vi lcp; // common prefix of every two indices in sa
	void genLcp() { // Kasai's Algo
		lcp = vi(N-1); int h = 0;
		F0R(i,N) if (isa[i]) {
			for (int j=sa[isa[i]-1]; j+h<N && S[i+h]==S[j+h]; h++);
			lcp[isa[i]-1] = h; if (h) h--; 
		}
		/// if we cut off first chars of two strs with lcp h 
		/// then remaining portions still have lcp h-1 
		/// R.init(lcp);
	}
	/**RMQ<int> R; 
	int getLCP(int a, int b) { // lcp of suffixes starting at a,b
		if (max(a,b) >= N) return 0;
		if (a == b) return N-a;
		int t0 = isa[a], t1 = isa[b];
		if (t0 > t1) swap(t0,t1);
		return R.query(t0,t1-1);
	}*/
};
