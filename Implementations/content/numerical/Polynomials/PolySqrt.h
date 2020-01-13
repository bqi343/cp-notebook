/**
 * Description: for $p$ a power of 2, computes $ans$ such that $ans^2 \equiv v \pmod{x^p}$
 * Time: O(N\log N)
 */

#include "PolyInv.h"

template<class T> vector<T> sqrt(vector<T> v, int p) { 
	assert(v[0] == 1); if (p == 1) return {1};
	v.rsz(p); auto S = sqrt(v,p/2);
	auto ans = S+mult(v,inv(S,p)); 
	ans.rsz(p); ans *= T(1)/T(2);
	return ans;
}
