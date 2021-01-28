/**
 * Description: Unordered map with keys in [0,SZ). (In case you're dumb like me and you need to replace a map rlly quickly ...)
 * Source: Own
 * Usage: HT<int,1<<20> dp;
 */

template<class T, int SZ> struct HT {
	vi keys; bitset<SZ> inside; T dat[SZ];
	void clear() { 
		each(t,keys) inside[t] = 0;
		keys.clear(); 
	}
	T& operator[](int k) { 
		if (!inside[k]) {
			inside[k] = 1, keys.pb(k); 
			dat[k] = 0;
		}
		return dat[k]; 
	}
};
