/**
 * Description: Used infrequently. Palindromic tree computes 
	* number of occurrences of each palindrome within string.
	* \texttt{ans[i][0]} stores min even $x$ such that 
	* the prefix $s[1..i]$ can be split into exactly $x$
	* palindromes, \texttt{ans[i][1]} does the same for odd $x.$
 * Time: $O(N\sum)$ for addChar, $O(N\log N)$ for updAns
 * Source: 
	* http://codeforces.com/blog/entry/13959
	* https://codeforces.com/blog/entry/19193
 * Verification: 
	* https://oj.uz/problem/view/APIO14_palindrome
	* http://acm.timus.ru/problem.aspx?space=1&num=2058
 */

template<int SZ> struct PalTree {
	static const int sigma = 26;
	int s[SZ], len[SZ], link[SZ], to[SZ][sigma], oc[SZ];
	int slink[SZ], diff[SZ];
	array<int,2> ans[SZ], seriesAns[SZ];
	int n = 0, last = 0, sz;
	PalTree() { 
		s[n++] = -1; link[0] = 1; len[1] = -1; sz = 2; 
		ans[0] = {0,MOD};
	}
	int getLink(int v) {
		while (s[n-len[v]-2] != s[n-1]) v = link[v];
		return v;
	}
	void updAns() { // serial path has O(log n) vertices
		ans[n-1] = {MOD,MOD};
		for (int v = last; len[v] > 0; v = slink[v]) {
			seriesAns[v] = ans[n-1-(len[slink[v]]+diff[v])];
			if (diff[v] == diff[link[v]]) 
				F0R(i,2) ckmin(seriesAns[v][i],seriesAns[link[v]][i]);
			// previous oc of link[v] = start of last oc of v
			F0R(i,2) ckmin(ans[n-1][i],seriesAns[v][i^1]+1);
		}
	}
	void addChar(int c) {
		s[n++] = c;
		last = getLink(last);
		if (!to[last][c]) {
			len[sz] = len[last]+2;
			link[sz] = to[getLink(link[last])][c];
			diff[sz] = len[sz]-len[link[sz]];
			if (diff[sz] == diff[link[sz]]) 
				slink[sz] = slink[link[sz]];
			else slink[sz] = link[sz]; 
			// slink[v] = max suffix u of v such that diff[v]\neq diff[u]
			to[last][c] = sz++;
		}
		last = to[last][c]; oc[last] ++;
		updAns();
	}
	void numOc() { // # occurrences of each palindrome
		vpi v; FOR(i,2,sz) v.pb({len[i],i});
		sort(rall(v)); trav(a,v) oc[link[a.s]] += oc[a.s];
	}
};