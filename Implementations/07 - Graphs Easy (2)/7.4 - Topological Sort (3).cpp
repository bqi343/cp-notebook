/**
 * Description: sorts vertices such that if there exists an edge x->y, then x goes before y
 * Source: own?
 * Verification: https://open.kattis.com/problems/quantumsuperposition
 */

template<int SZ> struct TopoSort {
    int N, in[SZ];
    vi res, adj[SZ];

    void addEdge(int x, int y) { adj[x].pb(y), in[y] ++; }

    bool sort(int _N) {
        N = _N; queue<int> todo;
        FOR(i,1,N+1) if (in[i] == 0) todo.push(i);
        while (sz(todo)) {
            int x = todo.front(); todo.pop(); res.pb(x);
            trav(i,adj[x]) {
                in[i] --;
                if (!in[i]) todo.push(i);
            }
        }
        return sz(res) == N;
    }
};