/**
 * Description: doesn't seem to be faster than other prime sieve
 * Time: O(SZ)
 */

template<int SZ> struct Sieve { 
	int sp[SZ];
	vi pr;

	Sieve() {
		memset(sp,0,sizeof sp);
		FOR(i,2,SZ) { 
			if (sp[i] == 0) { sp[i] = i; pr.pb(i); }
			trav(p,pr) {
				if (p > sp[i] || i*p >= SZ) break;
				sp[i*p] = p;
			}
		}
	} 
};
