/**
 * Description: Recovers $k$ increasing disjoint subsequences that 
 	* cover the maximum possible number of elements from $A$, 
 	* which must be a permutation of $[0,N)$. 
 * Source: Mark Gordon, based on the method described in section 4 of Greene's 
 	* "An Extension of Schensted's Theorem".
 * Time: O(MN), $M$ equals sum of sizes of subseqs
 * Verification: ?
 */

vector<vi> RSKrecover(vi A, int k) {
	int N = sz(A); vector<vi> h(k); // current tableau
	vector<tuple<int,int,int>> swaps; // Run RSK algo
	F0R(i,N) { 
		int x = A[i];
		F0R(j,k) { // type 3 swaps: (y,z,x) -> (y,x,z) where x<y<z
			if (!sz(h[j]) || h[j].bk < x) { h[j].pb(x); break; } 
			for (int y = sz(h[j])-1; ; --y) {
				if (y==0 || h[j][y-1]<x) { swap(x,h[j][y]); break; }
				swaps.eb(x,h[j][y-1],h[j][y]); 
			} // also type 2 swaps, but undoing them doesn't change 
		} // anything so no use storing
	}
	while (!sz(h[k-1])) k --;
	vi nxt(N+1,-1), prv(N+1,-1); // Linked list with k increasing 
	// subseqs, initially the canonical representation of A
	F0R(i,k) { // just take first k rows
		prv[h[i][0]] = N;
		FOR(j,1,sz(h[i])) {
			int a = h[i][j-1], b = h[i][j];
			prv[b] = a, nxt[a] = b;
		}
		nxt[h[i].bk] = N;
	} // Replay the swaps backwards and adjust subseqs
	R0F(i,sz(swaps)) { // type 1 swaps: x<y<z, yxz -> yzx
		int x,y,z; tie(x,y,z) = swaps[i]; 
		if (nxt[x] != z) continue; // x and y not in same subseq
		if (nxt[y] == -1) { // swap x,y
			prv[y] = prv[x]; nxt[prv[y]] = y;
			nxt[y] = z; prv[z] = y;
			prv[x] = nxt[x] = -1;
		} else { // Splice lists; a->y->b and c->x->z->d 
			nxt[x] = nxt[y]; prv[nxt[x]] = x;
			nxt[y] = z; prv[z] = y;
		} // becomes a->y->z->d and c->x->b.
	} // Reconstruct actual subseqs from linked list
	int cnt = 0; vi seq(N,-1); vector<vi> res(k);
	F0R(i,N) if (prv[i] != -1) {
		seq[i] = prv[i] == N ? cnt++ : seq[prv[i]]; 
		res[seq[i]].pb(i); // start new or continue old seq
	}
	return res;
}

/**
int main() {
	int N = 10, k = 5; // re(N,k);
	vi A(N); // re(A);
	F0R(i,N) A[i] = i;
	random_shuffle(all(A));
	ps(A);
	vector<vi> B = RSKrecover(A, k);
	F0R(i,sz(B)) {
		F0R(j,sz(B[i])) {
			if (j) cout << ' ';
			cout << B[i][j];
		}
		cout << endl;
	}
}
*/