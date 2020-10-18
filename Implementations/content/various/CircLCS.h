/**
 * Description: Used only twice. For strs $a,b$ calculates 
 	* longest common subsequence of $a$ with all rotations of $b$
 * Time: O(|A|\cdot |B|)
 * Source: gs14004, oj.uz
 * Verification: https://oj.uz/problem/view/IZhO13_rowords
 	* also see B from https://codeforces.com/gym/101657/standings
 */

str A,B; V<vi> dp, dir; // DP values for normal LCS, which direction values came from
void init() {
	dp = dir = V<vi>(sz(A)+1,vi(sz(B)+1));
	FOR(i,1,sz(A)+1) FOR(j,1,sz(B)+1) {
		dp[i][j] = dp[i-1][j];
		if (A[i-1] == B[j-1] && ckmax(dp[i][j],dp[i-1][j-1]+1)) dir[i][j] = 1;
		if (ckmax(dp[i][j],dp[i][j-1])) dir[i][j] = 2;
	}
}
int get_ans(pi p) { // get current LCS
	int ans = 0;
	while (p.f) {
		if (dir[p.f][p.s] == 2) p.s --;
		else if (dir[p.f][p.s] == 1) p.f --, p.s --, ans ++;
		else p.f --;
	}
	return ans;
}
void remove_char(int ind) { // remove column of DP table, fix dirs
	for (pi cur{0,ind}; cur.s < sz(B);) { // decrease some suffix of each column
		if (dir[cur.f][cur.s+1] == 2) dir[cur.f][++cur.s] = 0; // move to next column
		else {
			if (cur.f == sz(A)) break;
			if (dir[++cur.f][cur.s+1] == 1) dir[cur.f][++cur.s] = 0; // move to next column, increase by one
		}
	}
}
int circ_lcs(str a, str b) {
	A = a, B = b+b; init();
	int ans = 0;
	F0R(i,sz(b)) {
		ckmax(ans,get_ans({sz(a),i+sz(b)}));
		remove_char(i);
	}
	return ans;
}