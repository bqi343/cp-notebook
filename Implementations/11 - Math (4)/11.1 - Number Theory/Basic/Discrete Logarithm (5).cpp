/**
 * Description: find k such that root^k%mod=x
 	* mod is prime, root is primitive
 	* meet in the middle: O(sqrt(mod))
 * Source: Own
 * Verification: ?
 */

// dependency: Modular Int

struct DiscreteLog {
	int mod, root, block;
	vmi invy;
	unordered_map<int,int> u;

	int query(int x) {
		F0R(i,block) {
			int X = invy[i]*x;
			if (u.count(X)) return i*block+u[X];
		}
		return -1;
	}

	void init(int m, int r) : mod(m), root(r) {
		u.clear(); block = sqrt(mod)+1;

		mi cur(1,mod); F0R(i,block) u[cur] = i, cur *= root;
		cur = inv(cur,mod);

		invy.resz(block); invy[0] = 1; FOR(i,1,block) invy[i] = cur*invy[i-1];
	} 
};
