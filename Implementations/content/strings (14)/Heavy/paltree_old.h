// simpler version, solves APIO palindrome

template<int SZ> struct palTree {
    static const int sigma = 26;
    int s[SZ], len[SZ], link[SZ], to[SZ][sigma], oc[SZ];
    int n, last, sz;
    palTree() {
        s[n++] = -1;
        link[0] = 1;
        len[1] = -1;
        sz = 2;
    }
    int get_link(int v) {
        while(s[n-len[v]-2] != s[n-1]) v = link[v];
        return v;
    }
    void add_letter(int c) {
        s[n++] = c;
        last = get_link(last);
        if (!to[last][c]) {
            len[sz] = len[last]+2;
            link[sz] = to[get_link(link[last])][c];
            to[last][c] = sz++;
        }
        last = to[last][c];
        oc[last] ++;
    }
    void prop() {
        vpi v;
        FOR(i,2,sz) v.pb({len[i],i});
        sort(all(v)); reverse(all(v));
        for (auto a: v) oc[link[a.s]] += oc[a.s]; 
    }
};