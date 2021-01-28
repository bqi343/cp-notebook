/**
 * Description: Factors integers.
 * Time: O(\sqrt N)
 * Source: Own
 * Verification: https://csacademy.com/contest/ceoi-2018-day-2/task/toys-big/
 */

namespace factorBasic {
	template<class T> vector<pair<T,int>> factor(T x) { 
		vector<pair<T,int>> pri;
		for (T i = 2; i*i <= x; ++i) if (x % i == 0) {
			int t = 0;
			while (x % i == 0) x /= i, t ++;
			pri.pb({i,t});
		}
		if (x > 1) pri.pb({x,1});
		return pri;
	}
	/* Note:
	 * number of operations needed s.t.
	 *				  phi(phi(...phi(n)...))=1
	 * is O(log n).
	 * Euler's theorem: a^{\phi(p)}\equiv 1 (mod p), gcd(a,p)=1
	 */
	ll phi(ll x) {
		each(a,factor(x)) x -= x/a.f;
		return x;
	}
	template<class T> void tour(vector<pair<T,int>>& v, 
		vector<T>& V, int ind, T cur) {
			if (ind == sz(v)) V.pb(cur);
			else {
				T mul = 1;
				F0R(i,v[ind].s+1) {
					tour(v,V,ind+1,cur*mul);
					mul *= v[ind].f;
				}
			}
		}
	template<class T> vector<T> getDivi(T x) {
		auto v = factor(x);
		vector<T> V; tour(v,V,0,(T)1); sort(all(V));
		return V;
	}
}

using namespace factorBasic;
