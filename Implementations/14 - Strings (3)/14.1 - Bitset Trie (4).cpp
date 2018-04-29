/**
* Source: Algorithms Gym
* Verification: January Easy 2018 - Shubham and Subarray Xor
*/

template<int MX> struct tri {
    const int MXBIT = 60;
    int trie[MX][2], nex = 0; // easily changed to character
    int sz[MX][2];
    ll ans = 0;
    
    tri() {
        memset(trie,0,sizeof trie);
    }
    
    void ins(ll x, int a = 1) { // insert or delete
        int cur = 0; sz[cur] += a;
        F0Rd(i,MXBIT) {
            int t = (x&(1LL<<i))>>i;
            if (!trie[cur][t]) trie[cur][t] = ++nex;
            cur = trie[cur][t];
            sz[cur] += a;
        }
    }
    
    void test(ll x) {
        int cur = 0;
        F0Rd(i,MXBIT) {
            int t = ((x&(1LL<<i))>>i) ^ 1;
            if (!trie[cur][t] || !sz[trie[cur][t]]) t ^= 1;
            cur = trie[cur][t];
            if (t) x ^= (1LL<<i);
        }
        ans = max(ans,x);
    }
};
