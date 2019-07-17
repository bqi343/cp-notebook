/**
 * Description: ?
 * Source: https://ideone.com/0cMjZJ
 * Verification: Kattis stringmultimatching
 */

template<int SZ> struct AhoCorasick {
    int sz = 1, num = 0; // sz = # of nodes, num = # strings added
    int link[SZ]; // longest suffix
    map<char,int> to[SZ];
    queue<int> q;
    
    int word[SZ]; // longest suffix which is a word
    vpi words[SZ]; // store word(s) at trie position
    vi oc[SZ]; // store occurrences of each word

    AhoCorasick() {
        memset(link,0,sizeof link);
        memset(word,0,sizeof word);
    }

    void add(string s) { // add word
        int v = 0;
        trav(c,s) {
            if (!to[v].count(c)) to[v][c] = sz++;
            v = to[v][c];
        }
        word[v] = v; words[v].pb({++num,sz(s)});
    }

    void init() { // generate links
        link[0] = -1; q.push(0);
        while (sz(q)) {
            int v = q.front(); q.pop();
            trav(it,to[v]) {
                char c = it.f; int u = it.s, j = link[v];
                while (j != -1 && !to[j].count(c)) j = link[j];
                if (j != -1) {
                    link[u] = to[j][c];
                    if (!word[u]) word[u] = word[link[u]];
                }
                q.push(u);
            }
        }
    }

    void process(int pos, int cur) { // process matches
        cur = word[cur];
        while (cur) {
            trav(a,words[cur]) oc[a.f].pb(pos-a.s+1);
            cur = word[link[cur]];
        }
    }

    int nex(int pos, int cur, char c) {
        // get position after adding character
        // if alphabet size is limited, speed up with memoization 
        while (cur != -1 && !to[cur].count(c)) cur = link[cur];
        if (cur == -1) cur = 0;
        else cur = to[cur][c];
        process(pos, cur);
        return cur;
    }
};