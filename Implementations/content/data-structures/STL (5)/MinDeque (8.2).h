/**
 * Description: maintains minimum of deque while adding 
	elements to back or deleting elements from front
 * Source: own
 * Verification: USACO Jan 18 Lifeguards
 */

template<class T> struct MinDeque { 
	int lo = 0, hi = -1;
	deque<pair<T,int>> d;
	int size() { return hi-lo+1; }
	void push(T x) { // add to back
		while (sz(d) && d.back().f >= x) d.pop_back();
		d.pb({x,++hi});
	}
	void pop() { // delete from front
		assert(size());
		if (d.front().s == lo++) d.pop_front();
	}
	T mn() { return size() ? d.front().f : MOD; }
	// change MOD based on T
};