/**
 * Description: Lazy SegTree supports modifications of the form 
 	* \texttt{ckmin(a\_i,t)} for all $l\le i\le r$, range max and sum queries. 
 	* \texttt{SZ} is power of 2.
 * Time: O(\log N)
 * Source: http://codeforces.com/blog/entry/57319
 * Verification: http://acm.hdu.edu.cn/showproblem.php?pid=5306
 */

template<int SZ> struct SegTreeBeats { // declare globally
	int N, mx[2*SZ][2], maxCnt[2*SZ];
	ll sum[2*SZ];
	void pull(int ind) {
		F0R(i,2) mx[ind][i] = max(mx[2*ind][i],mx[2*ind+1][i]);
		maxCnt[ind] = 0;
		F0R(i,2) {
			if (mx[2*ind+i][0] == mx[ind][0]) 
				maxCnt[ind] += maxCnt[2*ind+i];
			else ckmax(mx[ind][1],mx[2*ind+i][0]);
		}
		sum[ind] = sum[2*ind]+sum[2*ind+1];
	}
	void build(vi& a, int ind = 1, int L = 0, int R = -1) {
		if (R == -1) { R = (N = sz(a))-1; }
		if (L == R) {
			mx[ind][0] = sum[ind] = a[L];
			maxCnt[ind] = 1; mx[ind][1] = -1;
			return;
		} 
		int M = (L+R)/2;
		build(a,2*ind,L,M); build(a,2*ind+1,M+1,R); pull(ind);
	}
	void push(int ind, int L, int R) {
		if (L == R) return;
		F0R(i,2) if (mx[2*ind^i][0] > mx[ind][0]) {
			sum[2*ind^i] -= (ll)maxCnt[2*ind^i]*
							(mx[2*ind^i][0]-mx[ind][0]);
			mx[2*ind^i][0] = mx[ind][0];
		}
	}
	void upd(int x, int y, int t, int ind=1, int L=0, int R=-1) { 
		if (R == -1) R += N;
		if (R < x || y < L || mx[ind][0] <= t) return;
		push(ind,L,R);
		if (x <= L && R <= y && mx[ind][1] < t) {
			sum[ind] -= (ll)maxCnt[ind]*(mx[ind][0]-t);
			mx[ind][0] = t;
			return;
		}
		if (L == R) return;
		int M = (L+R)/2;
		upd(x,y,t,2*ind,L,M); upd(x,y,t,2*ind+1,M+1,R); pull(ind);
	}
	ll qsum(int x, int y, int ind = 1, int L = 0, int R = -1) {
		if (R == -1) R += N;
		if (R < x || y < L) return 0;
		push(ind,L,R);
		if (x <= L && R <= y) return sum[ind];
		int M = (L+R)/2;
		return qsum(x,y,2*ind,L,M)+qsum(x,y,2*ind+1,M+1,R);
	}
	int qmax(int x, int y, int ind = 1, int L = 0, int R = -1) {
		if (R == -1) R += N;
		if (R < x || y < L) return -1;
		push(ind,L,R);
		if (x <= L && R <= y) return mx[ind][0];
		int M = (L+R)/2;
		return max(qmax(x,y,2*ind,L,M),qmax(x,y,2*ind+1,M+1,R));
	}
};