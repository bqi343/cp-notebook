/**
 * Source: KACTL
 * Time: O(N)
 * Description: \texttt{f[i]} is length of the longest proper suffix 
 	* of the $i$-th prefix of $s$ that is a prefix of $s$
 * Verification: https://open.kattis.com/problems/stringmatching
 */

vi kmp(str s) {
	int N = sz(s); vi f(N+1); f[0] = -1;
	FOR(i,1,N+1) {
		for (f[i]=f[i-1];f[i]!=-1&&s[f[i]]!=s[i-1])f[i]=f[f[i]];
		f[i] ++; }
	return f;
}
vi getOc(str a, str b) { // find occurrences of a in b
	vi f = kmp(a+"@"+b), ret;
	FOR(i,sz(a),sz(b)+1) if (f[i+sz(a)+1] == sz(a)) 
		ret.pb(i-sz(a));
	return ret;
}
