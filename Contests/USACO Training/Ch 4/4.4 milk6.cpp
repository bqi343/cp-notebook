/*
ID: bqi3431
LANG: C++11
TASK: milk6
*/

#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;
 
typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef pair<int, int> pi;
typedef pair<ll,ll> pl;
typedef pair<double,double> pd;

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
#define all(x) x.begin(), x.end()

const int MOD = 1000000007;
const double PI = 4*atan(1);
const ll INF = 1e18;

struct Edge {
    int v;
    double flow, C;
    int rev, ind;
};

vi ans;

template<int SZ> struct Dinic {
    int level[SZ], start[SZ];
    vector<Edge> adj[SZ]; 
     
    void addEdge(int u, int v, double C, int ind) {
        Edge a{v, 0, C, sz(adj[v]),ind};
        Edge b{u, 0, 0, sz(adj[u]),-ind};
        adj[u].pb(a), adj[v].pb(b); 
    } 
     
    bool BFS(int s, int t) {
        F0R(i,SZ) level[i] = -1;
        level[s] = 0;  
      
        queue<int> q; q.push(s);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (auto e: adj[u]) 
                if (level[e.v] < 0  && e.flow < e.C) {
                    level[e.v] = level[u] + 1;
                    q.push(e.v);
                }
        }
     
        return level[t] >= 0;
    }
      
    double sendFlow(int u, double flow, int t) {
        if (u == t) return flow;
      
        for (  ; start[u] < sz(adj[u]); start[u] ++) {
            Edge &e = adj[u][start[u]]; 
                                          
            if (level[e.v] == level[u]+1 && e.flow < e.C) {
                double curr_flow = min(flow, e.C - e.flow);
                double temp_flow = sendFlow(e.v, curr_flow, t);
    
                if (temp_flow > 0) {
                    e.flow += temp_flow;
                    adj[e.v][e.rev].flow -= temp_flow;
                    return temp_flow;
                }
            }
        }
      
        return 0;
    }
     
    double maxFlow(int s, int t) {
        if (s == t) return -1;
        double total = 0;  
      
        while (BFS(s, t)) {
            F0R(i,SZ) start[i] = 0;
            while (double flow = sendFlow(s, INT_MAX, t)) total += flow;
        }
     
        return total;
    } 
};

Dinic<33> D;

int N,M;

int main() {
    freopen("milk6.in","r",stdin);
    freopen("milk6.out","w",stdout);
    
    cin >> N >> M;
    F0R(i,M) {
        int S,E,C; cin >> S >> E >> C;
        D.addEdge(S,E,1001*C+1+1/pow(2,M+1-i),i+1);
    }
    double x = D.maxFlow(1,N);
    cout << ((ll)x/1001) << " " << ((ll)x%1001) << "\n";
    D.BFS(1,N);
    FOR(i,1,N+1) if (D.level[i] != -1) 
        for (auto a: D.adj[i]) if (a.ind > 0 && D.level[a.v] == -1) 
            ans.pb(a.ind);
    
    sort(all(ans));
    for (int i: ans) cout << i << "\n";
}
