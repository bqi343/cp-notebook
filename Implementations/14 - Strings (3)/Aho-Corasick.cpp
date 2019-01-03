/** 
 * Source: https://ideone.com/0cMjZJ
 * Verification: Kattis stringmultimatching
*/

template<int SZ> struct AhoCorasick {
    int link[SZ], dict[SZ], sz = 1, num = 0;
    vpi ind[SZ];
    map<char,int> to[SZ];
    vi oc[SZ];
    queue<int> q;
    
    AhoCorasick() {
        memset(link,0,sizeof link);
        memset(dict,0,sizeof dict);
    }

    void add(string s) {
        int v = 0;
        for(auto c: s) {
            if (!to[v].count(c)) to[v][c] = sz++;
            v = to[v][c];
        }
        dict[v] = v; ind[v].pb({++num,sz(s)});
    }
 
    void pushLinks() {
        link[0] = -1; q.push(0);
        while (sz(q)) {
            int v = q.front(); q.pop();
            for (auto it: to[v]) {
                char c = it.f; int u = it.s, j = link[v];
                while (j != -1 && !to[j].count(c)) j = link[j];
                if (j != -1) {
                    link[u] = to[j][c];
                    if (!dict[u]) dict[u] = dict[link[u]];
                }
                q.push(u);
            }
        }
    }
    
    void process(int pos, int cur) { // process matches
        cur = dict[cur];
        while (cur) {
            for (auto a: ind[cur]) oc[a.f].pb(pos-a.s+1);
            cur = dict[link[cur]];
        }
    }
    
    int nex(int pos, int cur, char c) { 
        // get position after adding character
        // speed up with memoization
        while (cur != -1 && !to[cur].count(c)) cur = link[cur];
        if (cur == -1) cur = 0;
        else cur = to[cur][c];
        process(pos, cur);
        return cur;
    }
};