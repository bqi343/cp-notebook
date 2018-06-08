/** 
 * Source: https://ideone.com/0cMjZJ
 * Usage: Kattis stringmultimatching
*/

template<int SZ> struct Aho {
    int link[SZ], dict[SZ], sz = 1, num = 0;
    vpi ind[SZ];
    map<char,int> to[SZ];
    vi oc[SZ];
    queue<int> q;
    
    Aho() {
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
 
    void push_links() {
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
    
    int nex(int pos, int cur, char c) { // get position after adding character
        while (cur != -1 && !to[cur].count(c)) cur = link[cur];
        if (cur == -1) cur = 0;
        else cur = to[cur][c];
        process(pos, cur);
        return cur;
    }
};

Aho<100001> A;

int n;

void solve() {
    A = Aho<100001>();
    cin >> n;
    F0R(i,n) {
        string pat; getline(cin,pat); if (!i) getline(cin,pat);
        A.add(pat);
    }
    A.push_links();
    
    string t; getline(cin,t);
    int cur = 0;
    F0R(i,sz(t)) cur = A.nex(i,cur,t[i]);
    FOR(i,1,n+1) {
        for (int j: A.oc[i]) cout << j << " ";
        cout << "\n";
    }
}
