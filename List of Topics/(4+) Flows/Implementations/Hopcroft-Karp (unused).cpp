// https://en.wikipedia.org/wiki/Hopcroft%E2%80%93Karp_algorithm

#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;
 
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
template <class T> using Tree = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;

#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)

#define sz(x) (int)(x).size()
#define mp make_pair
#define pb push_back
#define f first
#define s second
#define lb lower_bound
#define ub upper_bound

const int MOD = 1000000007;
  
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