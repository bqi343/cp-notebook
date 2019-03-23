/**
 * Description: ?
 * Source: GeeksForGeeks
 * Verification: https://codeforces.com/contest/164/problem/C
 */

template<class T> using pqg = priority_queue<T,vector<T>,greater<T>>;

template<class T> T poll(pqg<T>& x) {
    T y = x.top(); x.pop();
    return y;
}

template<int SZ> struct mcf { // assume no negative cycles
    struct Edge { int v, rev; ll flow, cap, cost; };

    vector<Edge> adj[SZ];

    void addEdge(int u, int v, ll cap, ll cost) {
        Edge a{v, sz(adj[v]), 0, cap, cost}, b{u, sz(adj[u]), 0, 0, -cost};
        adj[u].pb(a), adj[v].pb(b);
    }

    int ST, EN;
    pi pre[SZ]; // previous vertex, edge label on path
    pl cost[SZ]; // tot cost of path, amount of flow
    ll totFlow, totCost, curCost;

    void reweight() { // ensures all non-negative edge weights
    	F0R(i,SZ) trav(p,adj[i]) p.cost += cost[i].f-cost[p.v].f;
    }

    bool spfa() { // reweighting will ensure that there will be negative weights only during the first time you run this
        F0R(i,SZ) cost[i] = {INF,0};
        cost[ST] = {0,INF};
        pqg<pair<ll,int>> todo; todo.push({0,ST});

        while (sz(todo)) {
            auto x = poll(todo); if (x.f > cost[x.s].f) continue;
            trav(a,adj[x.s]) if (x.f+a.cost < cost[a.v].f && a.flow < a.cap) {
                pre[a.v] = {x.s,a.rev};
                cost[a.v] = {x.f+a.cost, min(a.cap-a.flow,cost[x.s].s)};
                todo.push({cost[a.v].f,a.v});
            }
        }

        curCost += cost[EN].f; return cost[EN].s;
    }

    void backtrack() {
        auto f = cost[EN].s; totFlow += f, totCost += curCost*f;
        for (int x = EN; x != ST; x = pre[x].f) {
            adj[x][pre[x].s].flow -= f;
            adj[pre[x].f][adj[x][pre[x].s].rev].flow += f;
        }
    }

    pl minCostFlow(int _ST, int _EN) {
        ST = _ST, EN = _EN; totFlow = totCost = curCost = 0;
        spfa();
        while (1) {
            reweight();
            if (!spfa()) return {totFlow, totCost};
            backtrack();
        }
    }
};
