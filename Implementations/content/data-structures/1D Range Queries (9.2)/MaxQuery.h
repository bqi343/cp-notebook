/**
 * Description: insert pair $(a,b)$ and query max value 
 	* of $b$ over all pairs satisfying $a\ge x$.
 * Source: Own
 * Verification: https://codeforces.com/gym/102059/problem/K
 	* http://www.usaco.org/index.php?page=viewproblem2&cpid=995
 * Time: O(\log N)
 */

struct MaxQuery {
	map<int,ll> m;
	void ins(int a, ll b) {
		auto it = m.lb(a); if (it != end(m) && it->s >= b) return;
		it = m.insert(it,{a,b}); it->s = b;
		while (it != begin(m) && prev(it)->s <= b) m.erase(prev(it));
	}
	ll query(int x) { auto it = m.lb(x); 
		return it == end(m) ? 0 : it->s; }
};