/**
* Verification: https://open.kattis.com/problems/primesieve
*/

template<int SZ> struct Sieve { 
    bitset<SZ+1> comp;
	vi pr;

    Sieve() {
        for (int i = 2; i*i <= SZ; ++i) if (!comp[i]) 
            for (int j = i*i; j <= SZ; j += i) comp[j] = 1;
        FOR(i,2,SZ+1) if (!comp[i]) pr.pb(i);
    }
};
