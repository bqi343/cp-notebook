/**
 * Description: Used only twice. For strs $A,B$ calculates 
 	* longest common subsequence of $A$ with all rotations of $B$
 * Time: O(|A|\cdot |B|)
 * Source: gs14004, oj.uz
 * Verification: https://oj.uz/problem/view/IZhO13_rowords
 	* also see B from https://codeforces.com/gym/101657/standings
 */

int circular_lcs(str A, str B) {
	B += B;
	int max_lcs = 0;
	V<vb> dif_left(sz(A)+1,vb(sz(B)+1)), dif_up(sz(A)+1,vb(sz(B)+1)); 
	auto recalc = [&](int x, int y) { assert(x && y);
		int res = (A.at(x-1) == B.at(y-1)) | 
			dif_up[x][y-1] | dif_left[x-1][y];
		dif_left[x][y] = res-dif_up[x][y-1];
		dif_up[x][y]   = res-dif_left[x-1][y];
	};
	FOR(i,1,sz(A)+1) FOR(j,1,sz(B)+1) recalc(i,j);
	F0R(j,sz(B)/2) {
		// 1. zero out dp[.][j], update dif_left and dif_right
		if (j) for (int x = 1, y = j; x <= sz(A) && y <= sz(B); ) {
			int pre_up = dif_up[x][y];
			if (y == j) dif_up[x][y] = 0;
			else recalc(x,y);
			(pre_up == dif_up[x][y]) ? ++x : ++y;
		}
		// 2. calculate LCS(A[0:sz(A)),B[j:j+sz(B)/2))
		int cur_lcs = 0;
		FOR(x,1,sz(A)+1) cur_lcs += dif_up[x][j+sz(B)/2];
		ckmax(max_lcs,cur_lcs);
	}
	return max_lcs;
}