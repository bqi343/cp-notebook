/**
 * Description: Used only twice. For strs $a,b$ calculates 
 	* longest common subsequence of $a$ with all rotations of $b$
 * Time: O(N^2)
 * Source: gs14004, oj.uz
 * Verification: https://oj.uz/problem/view/IZhO13_rowords
 	* also see B from https://codeforces.com/gym/101657/standings
 */

pi dp[2001][4001];
str A,B; // both of len <= 2000
void init() { // naive LCS, store where values came from
	FOR(i,1,sz(A)+1) FOR(j,1,sz(B)+1) { 
		pi& bes = dp[i][j]; bes = {-1,-1};
		ckmax(bes,{dp[i-1][j].f,0});
		ckmax(bes,{dp[i-1][j-1].f+(A[i-1] == B[j-1]),-1});
		ckmax(bes,{dp[i][j-1].f,-2});
		bes.s *= -1;
	}
}
void adjust(int col) { // remove col'th character of b, fix DP
	int x = 1; while (x <= sz(A) && dp[x][col].s == 0) x ++;
	if (x > sz(A)) return; // no adjustments to dp
	pi cur = {x,col}; dp[cur.f][cur.s].s = 0;
	while (cur.f <= sz(A) && cur.s <= sz(B)) { 
		// every dp[cur.f][y >= cur.s].f decreased by 1
		if (cur.s < sz(B) && dp[cur.f][cur.s+1].s == 2) {
			dp[cur.f][++cur.s].s = 0;
		} else if (cur.f < sz(A) && cur.s < sz(B) 
			&& dp[cur.f+1][cur.s+1].s == 1) {
			dp[++cur.f][++cur.s].s = 0;
		} else cur.f ++;
	}
}
int getAns(pi x) {
	int lo = x.s-sz(B)/2, ret = 0;
	while (x.f && x.s > lo) {
		if (dp[x.f][x.s].s == 0) x.f --;
		else if (dp[x.f][x.s].s == 1) ret ++, x.f --, x.s --;
		else x.s --;
	}
	return ret;
}
int circLCS(str a, str b) {
	A = a, B = b+b; init();
	int ans = 0;
	F0R(i,sz(b)) {
		ckmax(ans,getAns({sz(a),i+sz(b)}));
		adjust(i+1);
	}
	return ans;
}