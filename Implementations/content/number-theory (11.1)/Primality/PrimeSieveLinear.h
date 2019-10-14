/**
 * Description: Linear Time Prime Sieve 
 */

template<int SZ> struct Sieve { 
	int sp[SZ];
	vi pr;

	Sieve() {
		memset(sp,0,sizeof sp);
		FOR(i,2,SZ) { // O(N) sieve
			if (sp[i] == 0) { sp[i] = i; pr.pb(i); }
			trav(p,pr) {
				if (p > sp[i] || i*p >= SZ) break;
				sp[i*p] = p;
			}
		}
	} 
};
