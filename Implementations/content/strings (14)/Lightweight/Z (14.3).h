/**
 * Source: http://codeforces.com/blog/entry/3107
 * Time: O(N)
 * Description: for each index $i$, computes the the maximum $len$ such that
 	* \texttt{s.substr(0,len) == s.substr(i,len)}
 * Verification: POI 12 Template, https://codeforces.com/contest/1137/problem/B
 */

vi z(string s) {
	int N = sz(s); s += '#';
	vi ans(N); ans[0] = N; 
	int L = 1, R = 0;
	FOR(i,1,N) {
		if (i <= R) ans[i] = min(R-i+1,ans[i-L]);
		while (s[i+ans[i]] == s[ans[i]]) ans[i] ++;
		if (i+ans[i]-1 > R) L = i, R = i+ans[i]-1;
	}
	return ans;
}

vi getPrefix(string a, string b) { // find prefixes of a in b
	vi t = z(a+b), T(sz(b));
	F0R(i,sz(T)) T[i] = min(t[i+sz(a)],sz(a));
	return T;
}

// pr(z("abcababcabcaba"),getPrefix("abcab","uwetrabcerabcab"));
