/**
* Description: \texttt{sa} contains indices of suffixes in sorted order
* Time: O(N\log N)
* Source: SuprDewd, KACTL, majk, ekzhang
* Verification: 
	* http://usaco.org/index.php?page=viewproblem2&cpid=768
		* https://pastebin.com/y2Z9FYr6
	* https://open.kattis.com/problems/suffixsorting
	* https://codeforces.com/contest/1090/problem/J
*/

template<int SZ> struct SuffixArray {
	string S; int N;
	void init(const string& _S) {
		S = _S; N = sz(S);
		genSa(); genLcp();
		// R.init(lcp);
	}
	
	vi sa, isa;
	void genSa() { // http://ekzlib.herokuapp.com
		sa.rsz(N); vi classes(N);
		F0R(i,N) sa[i] = N-1-i, classes[i] = S[i];
		stable_sort(all(sa), [this](int i, int j) { return S[i] < S[j]; });
		for (int len = 1; len < N; len *= 2) { 
			vi c(classes);
			F0R(i,N) { // compare first len characters of each suffix
				bool same = i && sa[i-1] + len < N
							  && c[sa[i]] == c[sa[i-1]]
							  && c[sa[i]+len/2] == c[sa[i-1]+len/2];
				classes[sa[i]] = same ? classes[sa[i-1]] : i;
			}
			vi nex(N), s(sa); iota(all(nex),0); // suffixes with <= len chars will not change pos 
			F0R(i,N) {
				int s1 = s[i]-len;
				if (s1 >= 0) sa[nex[classes[s1]]++] = s1; // order pairs w/ same first len chars by next len chars 
			}
		}
		isa.rsz(N); F0R(i,N) isa[sa[i]] = i;
	}
	
	vi lcp;
	void genLcp() { // KACTL
		lcp = vi(N-1);
		int h = 0;
		F0R(i,N) if (isa[i]) {
			int pre = sa[isa[i]-1];
			while (max(i,pre)+h < N && S[i+h] == S[pre+h]) h++;
			lcp[isa[i]-1] = h; // lcp of suffixes starting at pre and i
			if (h) h--; // if we cut off first chars of two strings with lcp h, then remaining portions still have lcp h-1 
		}
	}
	/*RMQ<int> R; 
	int getLCP(int a, int b) {
		if (max(a,b) >= N) return 0;
		if (a == b) return N-a;
		int t0 = isa[a], t1 = isa[b];
		if (t0 > t1) swap(t0,t1);
		return R.query(t0,t1-1);
	}*/
};