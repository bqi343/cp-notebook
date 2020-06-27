/**
 * Description: Linear Time Knapsack w/ Bounded Weights
 * Time: O(N\cdot (\text{max weight}))
 * Source: 
 	* https://chaoxuprime.com/posts/2018-12-18-subset-sum-through-balancing.html
 	* https://stackoverflow.com/questions/18821453/bounded-knapsack-special-case-small-individual-item-weight-is-small-compared-t
 * Verification: GP of Bytedance 2020 F
 */

const int BIG = 20000;
array<int,2*BIG+1> dp, tmp;

int solve(vi a) {
	int n = sz(a), ind = 0, sum = 0;
	while (ind < n && sum+a[ind] <= c) sum += a[ind++];
	if (ind == n) return sum;
	F0R(i,2*BIG+1) dp[i] = ind+1, tmp[i] = ind;
	dp[BIG+sum-c] = 0;
	FOR(i,ind,n) {
		R0F(j,BIG+1) ckmin(dp[j+a[i]],dp[j]);
		ROF(j,BIG,2*BIG+1) while (tmp[j] > dp[j]) 
			tmp[j] --, ckmin(dp[j-a[tmp[j]]],tmp[j]+1);
	}
	R0F(i,BIG+1) if (dp[i] != ind+1) return c+i-BIG; // must return
}