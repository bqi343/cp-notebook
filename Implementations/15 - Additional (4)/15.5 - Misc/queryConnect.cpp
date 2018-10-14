/**
* Description: For each pair of points, calculates the first time when they are connected
* Source: Own
* Verification: https://oj.uz/problem/view/COCI18_pictionary
*/

// struct DSU 

template<int SZ> struct queryConnect {
    int n,q; // vertices, edges, # queries
    vpi ed; // edges
 
    pi p[SZ]; // connectivity queries 
    int l[SZ],r[SZ]; // left and right bounds for answer
    vi tri[SZ];
 
    bool left() {
        F0R(i,sz(ed)+1) tri[i].clear();
        bool ok = 0;
        F0R(i,q) if (l[i] != r[i]) {
            tri[(l[i]+r[i])/2].pb(i);
            ok = 1;
        }
        return ok;
    }
 
    void test() {
        DSU<SZ> D = DSU<SZ>();
        F0R(i,sz(ed)+1) {
            if (i) D.unite(ed[i-1].f,ed[i-1].s);
            for (int x: tri[i]) {
                if (D.get(p[x].f) == D.get(p[x].s)) r[x] = i;
                else l[x] = i+1;
            }
        }
    }
     
    void solve() {
        F0R(i,q) l[i] = 0, r[i] = sz(ed)+1;
        while (left()) test();
    }
};