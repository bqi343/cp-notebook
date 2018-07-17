/**
* Description: sorts vertices such that if there exists an edge x->y, then x goes before y
*/

template<int SZ> struct Topo {
    int N, in[SZ];
    vi res, adj[SZ];
    
    void addEdge(int x, int y) {
    	adj[x].pb(y), in[y] ++;
    }
    
    void sort() {
        queue<int> todo;
        FOR(i,1,N+1) if (in[i] == 0) todo.push(i);
        while (sz(todo)) {
            int x = todo.front(); todo.pop();
            res.pb(x);
            for (int i: adj[x]) {
                in[i] --;
                if (!in[i]) todo.push(i);
            }
        }
    }
};
