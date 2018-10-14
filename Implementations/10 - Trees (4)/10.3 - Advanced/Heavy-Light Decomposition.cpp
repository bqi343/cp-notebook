/**
* Description: Heavy Light Decomposition
* Source: http://codeforces.com/blog/entry/22072
* Verification: USACO Grass Planting
*/

// struct LazySegTree

vector<vi> graph;

template <int V> struct HLD { // sum queries, sum updates
    int parent[V], heavy[V], depth[V];
    int root[V], treePos[V];
    LazySegTree<V> tree;

    void init() {
        int n = sz(graph)-1;
        FOR(i,1,n+1) heavy[i] = -1;
        parent[1] = -1, depth[1] = 0;
        dfs(1);
        for (int i = 1, currentPos = 0; i <= n; ++i)
		if (parent[i] == -1 || heavy[parent[i]] != i)
			for (int j = i; j != -1; j = heavy[j]) {
				root[j] = i;
				treePos[j] = currentPos++;
			}
    }
    
    int dfs(int v) {
        int size = 1, maxSubtree = 0;
        for (auto u : graph[v]) if (u != parent[v]) {
            parent[u] = v;
            depth[u] = depth[v] + 1;
            int subtree = dfs(u);
            if (subtree > maxSubtree) heavy[v] = u, maxSubtree = subtree;
            size += subtree;
        }
        return size;
    }

    template <class BinaryOperation>
    void processPath(int u, int v, BinaryOperation op) {
        for (; root[u] != root[v]; v = parent[root[v]]) {
            if (depth[root[u]] > depth[root[v]]) swap(u, v);
            op(treePos[root[v]], treePos[v]);
        }
        if (depth[u] > depth[v]) swap(u, v);
        op(treePos[u]+1, treePos[v]); // assumes values are stored in edges, not vertices
    }

    void modifyPath(int u, int v, int value) { // add one to vertices along path
        processPath(u, v, [this, &value](int l, int r) { tree.upd(l, r, value); });
    }

    ll queryPath(int u, int v) { // query sum of path
        ll res = 0;
        processPath(u, v, [this, &res](int l, int r) { res += tree.qsum(l, r); });
        return res;
    }
};