/**
 * Source: http://codeforces.com/blog/entry/12143
 * Time: O(N)
 * Description: length of largest palindrome centered at each character of string
 	* and between every consecutive pair
 * Verification: http://www.spoj.com/problems/MSUBSTR/
 */

vi manacher(str _S) {
	str S = "@"; each(c,_S) S += c, S += "#";
	S.bk = '&';
	vi ans(sz(S)-1); int lo = 0, hi = 0;
	FOR(i,1,sz(S)-1) {
		if (i != 1) ans[i] = min(hi-i,ans[hi-i+lo]);
		while (S[i-ans[i]-1] == S[i+ans[i]+1]) ++ans[i];
		if (i+ans[i] > hi) lo = i-ans[i], hi = i+ans[i];
	}
	ans.erase(begin(ans));
	F0R(i,sz(ans)) if (i%2 == ans[i]%2) ++ans[i]; 
	return ans;
} 
/// Usage: ps(manacher("abacaba"))
