/**
* Description: Segment tree on values instead of indices
* Source: http://rachitiitr.blogspot.com/2017/06
	/wavelet-trees-wavelet-trees-editorial.html
* Verification: http://www.spoj.com/problems/MKTHNUM/
*/

template<int SZ> struct Wavelet {
	vi mapl[2*SZ], mapr[2*SZ], val[2*SZ];
	void build(int ind = 1, int L = 0, int R = SZ-1) { // build a wavelet tree
		if (ind == 1) { F0R(i,N) val[ind].pb(i); }
		if (L == R) return;
		int M = (L+R)/2;
		trav(i,val[ind]) {
			val[2*ind+(A[i] > M)].pb(i);
			mapl[ind].pb(sz(val[2*ind])-1);
			mapr[ind].pb(sz(val[2*ind+1])-1);
		}
		build(2*ind,L,M);
		build(2*ind+1,M+1,R);
	}

	int getl(int ind, int x) { return x < 0 ? -1 : mapl[ind][x]; }
	int getr(int ind, int x) { return x < 0 ? -1 : mapr[ind][x]; }
	int query(int lind, int rind, int k, int ind = 1, int L = 0, int R = SZ-1) { // get k-th largest number in interval
		if (L == R) return L;

		int M = (L+R)/2;
		int t = getl(ind,rind)-getl(ind,lind-1);
		if (t >= k) return query(getl(ind,lind-1)+1,
								getl(ind,rind),k,2*ind,L,M);
		return query(getr(ind,lind-1)+1,
					getr(ind,rind),k-t,2*ind+1,M+1,R);
	}
};
