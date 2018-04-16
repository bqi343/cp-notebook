/**
* Description: sorts vertices such that if there exists an edge x->y, then x goes before y
*/

struct Topo {
    int N, in[MX];
    vi res, adj[MX];
    
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
