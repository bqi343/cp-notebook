// http://www.geeksforgeeks.org/ford-fulkerson-algorithm-for-maximum-flow-problem/

#include <bits/stdc++.h>
  
using namespace std;
//using namespace __gnu_pbds;
  
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
//typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;
  
#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
  
#define mp make_pair
#define pb push_back
#define f first
#define s second
#define lb lower_bound
#define ub upper_bound
  
const int MOD = 1000000007;
double PI = 4*atan(1);

struct Edge {
    int v, flow, C, rev, cost;
};

template<int SZ> struct mcf {
    pii pre[SZ];
    int cost[SZ], num[SZ], SC, SNC;
    vector<Edge> adj[SZ]; 
     
    void addEdge(int u, int v, int C, int cost) {
        Edge a{v, 0, C, (int)adj[v].size(), cost};
        Edge b{u, 0, 0, (int)adj[u].size(), -cost};
        adj[u].pb(a);
        adj[v].pb(b); 
    } 
    
    bool bfs() {
        F0R(i,SZ) cost[i] = MOD, num[i] = 0;
        cost[SC] = 0, num[SC] = MOD;
        priority_queue<pii,vector<pii>,greater<pii>> todo; todo.push({0,SC}); 
        // doesn't handle negative edges very well
        // no negative cycles
        
        while (todo.size()) {
            pii x = todo.top(); todo.pop();
            if (x.s == SNC) return 1;
            for (auto a: adj[x.s]) if (x.f+a.cost < cost[a.v] && a.flow < a.C) {
                pre[a.v] = {x.s,a.rev};
                cost[a.v] = x.f+a.cost;
                num[a.v] = min(a.C-a.flow,num[x.s]);
                todo.push({cost[a.v],a.v});
            }
        }
        
        return num[SNC] > 0;
    }
    
    pii mincostflow(int sc, int snc) {
        SC = sc, SNC = snc;
        
        int flo = 0, ans = 0;
        while (bfs()) {
            flo += num[SNC], ans += (ll)num[SNC]*cost[SNC];
            for (int x = SNC; x != SC; x = pre[x].f) {
                adj[x][pre[x].s].flow -= num[SNC];
                int t = adj[x][pre[x].s].rev;
                adj[pre[x].f][t].flow += num[SNC];
            }
        }
        
        return {flo,ans};
    }
};

mcf<100> m;

int main() {
    m.addEdge(0, 1, 16, 5);
    m.addEdge(1, 2, 13, 7);
    m.addEdge(1, 2, 13, 8);
    
    pii x = m.mincostflow(0,2);
    cout << x.f << " " << x.s;
}
