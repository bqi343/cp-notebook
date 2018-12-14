/**
 * Description: Suffix Automaton
 * Source: https://cp-algorithms.com/string/suffix-automaton.html
 * Verification: https://www.spoj.com/problems/SUBLEX/
 */
 
template<int SZ> struct sa {
    struct state {
        int len, link;
        map<char, int> next;
    };
    
    state st[SZ * 2]; 
    int sz, last;
    ll ans[SZ * 2]; // number of distinct substrings from current pos
    
    void extend(char c) {
        int cur = sz++;
        st[cur].len = st[last].len + 1;
        int p = last;
        while (p != -1 && !st[p].next.count(c)) {
            st[p].next[c] = cur;
            p = st[p].link;
        }
        if (p == -1) {
            st[cur].link = 0;
        } else {
            int q = st[p].next[c];
            if (st[p].len + 1 == st[q].len) {
                st[cur].link = q;
            } else {
                int clone = sz++;
                st[clone] = st[q]; st[clone].len = st[p].len + 1;
                while (p != -1 && st[p].next[c] == q) {
                    st[p].next[c] = clone;
                    p = st[p].link;
                }
                st[q].link = st[cur].link = clone;
            }
        }
        last = cur;
    }
    
    void init(string s) { 
        st[0].len = 0, st[0].link = -1; sz ++; last = 0; 
        trav(x,s) extend(x); 
    }
    
    ll gen(int x) {
        if (ans[x]) return ans[x];
        ans[x] = 1; trav(y,st[x].next) ans[x] += gen(y.s);
        return ans[x];
    }
};