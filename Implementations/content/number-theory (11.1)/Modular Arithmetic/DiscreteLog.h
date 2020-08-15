/**
 * Description: find least integer p such that r^p=x(mod MOD)
	* meet in the middle: O(sqrt(mod)) per query
 * Source: Own
 * Verification: https://www.hackerrank.com/contests/infinitum11/challenges/discrete-logarithm/problem
 */

#include "ModInt.h"

struct DiscreteLog {
	int root, block;
	unordered_map<int,int> u;
	mi cur;
	int query(mi x) { 
		F0R(i,block) {
			if (u.count((int)x)) return i*block+u[(int)x];
			x *= cur;
		}
		return -1;
	}
	void init(int r) { // gcd(m,r) = 1
		root = r; block = sqrt(MOD)+1;
		u.clear(); cur = mi(1);
		F0R(i,block) {
			if (!u.count((int)cur)) u[(int)cur] = i;
			cur *= root;
		}
		cur = 1/cur;
	} 
};