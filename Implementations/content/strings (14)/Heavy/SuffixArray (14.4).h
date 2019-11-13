/**
 * Description: \texttt{sa} contains indices of suffixes in sorted order
 * Time: O(N\log N)
 * Source: SuprDewd, KACTL, majk, ekzhang (http://ekzlib.herokuapp.com)
 * Verification: 
	* http://usaco.org/index.php?page=viewproblem2&cpid=768
		* https://pastebin.com/y2Z9FYr6
	* https://open.kattis.com/problems/suffixsorting
	* https://codeforces.com/contest/1090/problem/J
 */

struct SuffixArray {
	string S; int N;
	void init(const string& _S) {
		S = _S; N = sz(S);
		genSa(); genLcp(); // R.init(lcp);
	}
	vi sa, isa;
	void genSa() {
		sa.rsz(N); isa.rsz(N);
		F0R(i,N) sa[i] = N-1-i, isa[i] = S[i];
		stable_sort(all(sa), [this](int i, int j) { 
			return S[i] < S[j]; });
		// can speed up on random test data by breaking 
		// when elements of isa are all distinct
		for (int len = 1; len < N; len *= 2) { 
			vi is(isa), s(sa), nex(N); iota(all(nex),0); 
			F0R(i,N) { // compare first len characters of each suf
				bool same = i && sa[i-1]+len < N
							  && is[sa[i]] == is[sa[i-1]]
							  && is[sa[i]+len/2] == is[sa[i-1]+len/2];
				isa[sa[i]] = same ? isa[sa[i-1]] : i;
			} 
			F0R(i,N) { // rearrange sufs with >len chars
				int s1 = s[i]-len; 
				if (s1 >= 0) sa[nex[isa[s1]]++] = s1; 
			} 
		}
	}
	vi lcp;
	void genLcp() { // Kasai's Algo
		lcp = vi(N-1); int h = 0;
		F0R(i,N) if (isa[i]) {
			int pre = sa[isa[i]-1];
			while (max(i,pre)+h < N && S[i+h] == S[pre+h]) h++;
			lcp[isa[i]-1] = h; // lcp of sufs starting at pre and i
			if (h) h--; // if we cut off first chars of two strings 
			// with lcp h then remaining portions still have lcp h-1 
		}
	}
	/*RMQ<int> R; 
	int getLCP(int a, int b) { // lcp of suffixes starting at a,b
		if (max(a,b) >= N) return 0;
		if (a == b) return N-a;
		int t0 = isa[a], t1 = isa[b];
		if (t0 > t1) swap(t0,t1);
		return R.query(t0,t1-1);
	}*/
};