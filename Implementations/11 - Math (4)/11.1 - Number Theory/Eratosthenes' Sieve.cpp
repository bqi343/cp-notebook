/**
* Source: KACTL
* https://open.kattis.com/problems/primesieve
*/

template<int SZ> struct Sieve {
    bitset<SZ+1> comp;
    Sieve() {
        for (int i = 2; i*i <= SZ; ++i) if (!comp[i]) 
            for (int j = i*i; j <= SZ; j += i) comp[j] = 1;
    }
    bool isprime(int x) {
        if (x == 1) return 0;
        return !comp[x];
    }
};
