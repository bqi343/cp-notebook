/**
* Description: For each pair of points, calculates the first time when they are connected
* Verification: https://oj.uz/problem/view/COCI18_pictionary
*/

int n,m,q; // vertices, edges, # queries
pi p[MX]; // connectivity queries 
int l[MX],r[MX];
vi tri[MX];
vpi ed; // edges

bool left() {
    F0R(i,sz(ed)) tri[i].clear();
    bool ok = 0;
    F0R(i,q) if (l[i] != r[i]) {
        tri[(l[i]+r[i])/2].pb(i);
        ok = 1;
    }
    return ok;
}

void test() {
    DSU<MX> D = DSU<MX>();
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