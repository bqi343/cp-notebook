/**
 * Description: minimum cyclic shift
 * Time: O(N)
 * Source: KACTL
 * Verification: https://cses.fi/problemset/task/1110/
 */
 
int minRotation(str s) {
	int a = 0, N = sz(s); s += s;
	F0R(b,N) F0R(i,N) { 
		// a is current best rotation found up to b-1
		if (a+i==b || s[a+i]<s[b+i]) { b += max(0,i-1); break; } 
		// b to b+i-1 can't be better than a to a+i-1
		if (s[a+i] > s[b+i]) { a = b; break; } // new best found
	}
	return a;
}
