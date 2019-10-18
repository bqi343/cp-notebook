/**
 * Source: http://codeforces.com/blog/entry/12143
 * Time: O(N)
 * Description: Calculates length of largest palindrome centered at each character of string
 * Verification: http://www.spoj.com/problems/MSUBSTR/
 */

vi manacher(string s) {
	string s1 = "@";
	trav(c,s) s1 += c, s1 += "#";
	s1[sz(s1)-1] = '&';

	vi ans(sz(s1)-1);
	int lo = 0, hi = 0;
	FOR(i,1,sz(s1)-1) {
		if (i != 1) ans[i] = min(hi-i,ans[hi-i+lo]);
		while (s1[i-ans[i]-1] == s1[i+ans[i]+1]) ans[i] ++;
		if (i+ans[i] > hi) lo = i-ans[i], hi = i+ans[i];
	}

	ans.erase(begin(ans));
	F0R(i,sz(ans)) if ((i&1) == (ans[i]&1)) ans[i] ++; // adjust lengths
	return ans;
} 
// ps(manacher("abacaba"))