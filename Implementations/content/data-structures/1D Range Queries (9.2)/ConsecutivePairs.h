/**
 * Description: maintains info about every pair of consecutive elements in a set.
 	* In code below, \texttt{difs} is a multiset of all consecutive differences.
 * Time: O(\log N)
 * Source: own
 * Verification: https://cses.fi/problemset/task/1188/
 */

 template<class T> struct ConsecutivePairs {
	set<T> S;
	multiset<int> difs;
	void ins_pair(T l, T r) {
		difs.ins(r-l); 
	}
	void erase_pair(T l, T r) {
		auto it = difs.find(r-l); assert(it != end(difs));
		difs.erase(it);
	}
	void ins(T t) {
		auto [it,inserted] = S.ins(t); assert(inserted);
		bool is_bg = it == bg(S), is_en = next(it) == end(S);
		if (!is_bg && !is_en) erase_pair(*prev(it),*next(it));
		if (!is_bg) ins_pair(*prev(it),*it);
		if (!is_en) ins_pair(*it,*next(it));
	}
	void erase(T t) {
		auto it = S.find(t); assert(it != end(S));
		bool is_bg = it == bg(S), is_en = next(it) == end(S);
		if (!is_bg) erase_pair(*prev(it),*it);
		if (!is_en) erase_pair(*it,*next(it));
		if (!is_bg && !is_en) ins_pair(*prev(it),*next(it));
		S.erase(it);
	}
	void toggle(T t) {
		if (S.count(t)) erase(t);
		else ins(t);
	}
};