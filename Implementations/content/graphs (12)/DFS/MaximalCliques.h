/**
 * Description: Used only once. Finds all maximal cliques.
 * Time: O(3^{N/3})
 * Source: KACTL
 * Verification: BOSPRE 2016 gaudy
 */

typedef bitset<128> B; B adj[128];
int N;
// possibly in clique, not in clique, in clique
void cliques(B P = ~B(), B X={}, B R={}) { 
	if (!P.any()) { 
		if (!X.any()) // do smth with R
		return; 
	}
	int q = (P|X)._Find_first();
	// clique must contain q or non-neighbor of q
	B cands = P&~adj[q]; 
	F0R(i,N) if (cands[i]) {
		R[i] = 1; cliques(P&adj[i],X&adj[i],R);
		R[i] = P[i] = 0; X[i] = 1;
	}
}
