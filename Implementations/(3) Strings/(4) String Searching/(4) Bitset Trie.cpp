/**
* Source: Algorithms Gym
*/

template<int MX> struct tri {
    int nex = 0, ans = 0;
    int trie[MX][2]; // easily changed to character
    
    tri() {
        memset(trie,0,sizeof trie);
    }
    
    void ins(int x) {
        int cur = 0;
        F0Rd(i,30) {
            int t = (x&(1<<i))>>i;
            if (!trie[cur][t]) trie[cur][t] = ++nex;
            cur = trie[cur][t];
        }
    }
    
    void test(int x) {
        int cur = 0;
        F0Rd(i,30) {
            int t = ((x&(1<<i))>>i) ^ 1;
            if (!trie[cur][t]) t ^= 1;
            cur = trie[cur][t];
            if (t) x ^= (1<<i);
        }
        ans = max(ans,x);
    }
};
