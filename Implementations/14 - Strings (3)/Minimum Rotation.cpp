/**
* Description: Calculates min rotation of string in O(N)
* Source: KACTL
* Verification: ?
*/

int minRotation(string s) {
	int a = 0, N = sz(s); s += s;
	F0R(b,N) F0R(i,N) {
		if (a+i == b || s[a+i] < s[b+i]) {b += max(0, i-1); break;}
		if (s[a+i] > s[b+i]) { a = b; break; }
	}
	return a;
}