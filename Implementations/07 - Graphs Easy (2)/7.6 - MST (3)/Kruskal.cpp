/**
* Description: computes the minimum spanning tree in O(ElogE) time
* Source: Own
* Verification: USACO superbull
*/

template<class T> T kruskal(vector<pair<T,pi>> edge) {
    DSU<MX> D; 
    sort(all(edge)); 
    T ans = 0;
    for (auto a: edge) if (D.unite(a.s.f,a.s.s)) ans += a.f; // edge is in MST   
    return ans;
}