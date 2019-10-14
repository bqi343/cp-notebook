/**
 * Description: find least integer p such that r^p=x(mod m)
	* meet in the middle: O(sqrt(mod)) per query
 * Source: Own
 * Verification: https://www.hackerrank.com/contests/infinitum11/challenges/discrete-logarithm/problem
 * Dependency: Modular Int
 */

struct DiscreteLog {
	int mod, root, block;
	unordered_map<int,int> u;
	mi cur;

	int query(mi x) { 
		F0R(i,block) {
			if (u.count((int)x)) return i*block+u[(int)x];
			x *= cur;
		}
		return -1;
	}

	void init(int m, int r) { // gcd(m,r) = 1
		mod = m; root = r; block = sqrt(mod)+1;
		u.clear(); 
		cur = mi(1,mod);
		F0R(i,block) {
			if (!u.count((int)cur)) u[(int)cur] = i;
			cur *= root;
		}
		cur = 1/cur;
	} 
};