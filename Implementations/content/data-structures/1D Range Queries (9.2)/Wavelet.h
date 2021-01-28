/**
* Description: SegTree on values instead of indices. Returns $k$-th 
	* largest number in 0-indexed interval \texttt{[lo,hi)}.
	* $SZ=2^p$ and all values in $a$ must lie in $[0,SZ)$.
* Memory: O(N\log N)
* Time: O(\log N) query
* Source: http://rachitiitr.blogspot.com/2017/06
	/wavelet-trees-wavelet-trees-editorial.html
* Verification: http://www.spoj.com/problems/MKTHNUM/
*/

template<int SZ> struct Wavelet { 
	vi nexl[SZ], nexr[SZ];
	void build(vi a, int ind = 1, int L = 0, int R = SZ-1) { 
		if (L == R) return;
		nexl[ind] = nexr[ind] = {0};
		vi A[2]; int M = (L+R)/2;
		each(t,a) {
			A[t>M].pb(t);
			nexl[ind].pb(sz(A[0])), nexr[ind].pb(sz(A[1]));
		}
		build(A[0],2*ind,L,M), build(A[1],2*ind+1,M+1,R);
	}
	int query(int lo,int hi,int k,int ind=1,int L=0,int R=SZ-1) { 
		if (L == R) return L;
		int M = (L+R)/2, t = nexl[ind][hi]-nexl[ind][lo];
		if (t >= k) return query(nexl[ind][lo],
						nexl[ind][hi],k,2*ind,L,M);
		return query(nexr[ind][lo],
			nexr[ind][hi],k-t,2*ind+1,M+1,R);
	}
};
