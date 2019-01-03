/**
* Description: Disjoint Set Union
* Source: CSAcademy
* Verification: USACO superbull
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

// computes the minimum spanning tree in O(ElogE) time

template<class T> T kruskal(vector<pair<T,pi>> edge) { 
    DSU<MX> D; 
    sort(all(edge)); 
    T ans = 0;
    for (auto a: edge) if (D.unite(a.s.f,a.s.s)) ans += a.f; // edge is in MST   
    return ans;
}