/**
* Source: own
* Description: computes the minimum spanning tree in O(ElogE) time
*/

template<int SZ> struct DSU {
    int par[SZ], sz[SZ];
    DSU() {
        F0R(i,SZ) par[i] = i, sz[i] = 1;
    }
    
    int get(int x) { // path compression
    	if (par[x] != x) par[x] = get(par[x]);
    	return par[x];
    }
    
    bool unite(int x, int y) { // union-by-rank
    	x = get(x), y = get(y);
    	if (x == y) return 0;
    	if (sz[x] < sz[y]) swap(x,y);
    	sz[x] += sz[y], par[y] = x;
    	return 1;
    }
};

int ans = 0; // total weight of MST
vector<pair<int,pii>> edge;

DSU<100> D;

void kruskal() {
	sort(all(edge));
	for (auto a: edge) if (D.unite(a.s.f,a.s.s)) ans += a.f; // edge is in MST	
}