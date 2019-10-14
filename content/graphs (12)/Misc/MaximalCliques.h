/**
 * Description: Finds all maximal cliques
 * Time: O(3^{n/3})
 * Source: KACTL
 * Verification: BOSPRE 2016 gaudy
 */

typedef bitset<128> B;
int N;
B adj[128];

void cliques(B P = ~B(), B X={}, B R={}) { // possibly in clique, not in clique, in clique
	if (!P.any()) { 
		if (!X.any()) { 
			// do smth with maximal clique
		}
		return; 
	}
	auto q = (P|X)._Find_first();
	auto cands = P&~eds[q]; // clique must contain q or non-neighbor of q
	F0R(i,N) if (cands[i]) {
		R[i] = 1;
		cliques(eds, f, P & eds[i], X & eds[i], R);
		R[i] = P[i] = 0; X[i] = 1;
	}
}