// Source: https://en.wikipedia.org/wiki/Hopcroft%E2%80%93Karp_algorithm
// unused
  
int Pair_U[100], Pair_V[100], Dist[100];
vi U, V, Adj[100];

bool BFS () {
    queue<int> Q;
    for (int u: U) {
        if (Pair_U[u] == 0) {
            Dist[u] = 0;
            Q.push(u);
        } else Dist[u] = MOD;
    }
    Dist[0] = MOD;
    while (Q.size()) {
        int u = Q.front(); Q.pop();
        if (Dist[u] < Dist[0]) 
            for (int v: Adj[u])
                if (Dist[ Pair_V[v] ] == MOD) {
                    Dist[Pair_V[v]] = Dist[u]+1;
                    Q.push(Pair_V[v]);
                }
    }
    return Dist[0] != MOD;
}

bool DFS (int u) {
    if (u) {
        for (int v: Adj[u])
            if (Dist[ Pair_V[v] ] == Dist[u] + 1)
                if (DFS(Pair_V[v])) {
                    Pair_V[v] = u, Pair_U[u] = v;
                    return 1;
                }
        Dist[u] = MOD;
        return 0;
    }
    return 1;
}

int HK () {
    for (int u: U) Pair_U[u] = 0;
    for (int v: V) Pair_V[v] = 0;
    
    int matching = 0;
    while (BFS())
        for (int u: U) if (Pair_U[u] == 0 && DFS(u)) 
            matching++;
                    
    return matching;
}
    
int main() {
	ios_base::sync_with_stdio(0);cin.tie(0);
	
}

// read!
// ll vs. int!