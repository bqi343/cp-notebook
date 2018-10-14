/**
* Description: computes the minimum spanning tree in O(ElogE) time
* Source: Own
* Verification: USACO superbull
*/

ll kruskal(vector<array<int,3>> edge) {
    DSU<MX> D; 
    sort(all(edge)); 
    ll ans = 0;
    for (auto a: edge) if (D.unite(a[1],a[2])) ans += a[0]; // edge is in MST   
    return ans;
}
