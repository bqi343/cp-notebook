#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;
 
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
#define double long double
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

typedef pair<double,double> pdd;

const int MOD = 1000000007;

int m,n;

const int SZ = 100;
 
struct Edge {
    int v, flow, C, rev;
};
 
struct Dinic {
    int level[SZ], start[SZ];
    vector<Edge> adj[SZ]; 
     
    void addEdge(int u, int v, int C) {
        Edge a{v, 0, C, (int)adj[v].size()};
        Edge b{u, 0, 0, (int)adj[u].size()};
        adj[u].pb(a);
        adj[v].pb(b); 
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
      
    int sendFlow(int u, int flow, int t) {
        if (u == t) return flow;
      
        for (  ; start[u] < adj[u].size(); start[u] ++) {
            Edge &e = adj[u][start[u]]; 
                                          
            if (level[e.v] == level[u]+1 && e.flow < e.C) {
                int curr_flow = min(flow, e.C - e.flow);
                int temp_flow = sendFlow(e.v, curr_flow, t);
    
                if (temp_flow > 0) {
                    e.flow += temp_flow;
                    adj[e.v][e.rev].flow -= temp_flow;
                    return temp_flow;
                }
            }
        }
      
        return 0;
    }
     
    int DinicMaxflow(int s, int t) {
        if (s == t) return -1;
        int total = 0;  
      
        while (BFS(s, t)) {
            F0R(i,SZ) start[i] = 0;
            while (int flow = sendFlow(s, INT_MAX, t)) total += flow;
        }
     
        return total;
    } 
};
  
Dinic D;
string name[61];
vi ADJ[61];

bool test(int mid) {
    D = Dinic();
    FOR(i,1,m+1) {
        D.addEdge(0,i,mid);
        for (int j: ADJ[i]) D.addEdge(i,j,1);
    }
    FOR(i,1,n+1) D.addEdge(i+60,99,2);
    return D.DinicMaxflow(0,99) == 2*n;
}

vector<string> ans[40];

void finish() {
    FOR(i,1,m+1) for (auto a: D.adj[i]) if (a.C > 0 && a.flow > 0) ans[a.v-60].pb(name[i]);
    FOR(i,1,n+1) {
        cout << "Day " << i << ": ";
        cout << ans[i][0] << " " << ans[i][1] << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(0);cin.tie(0);
    cin >> m >> n;
    FOR(i,1,m+1) {
        cin >> name[i];
        int k; cin >> k;
        F0R(j,k) {
            int d; cin >> d;
            ADJ[i].pb(d+60);
        }
    }
    int lo = 1, hi = 31;
    while (lo < hi) {
        int mid = (lo+hi)/2;
        bool f = test(mid);
        if (f) hi = mid;
        else lo = mid+1;
    }
    test(lo);
    cout << lo << "\n";
    finish();
}

// read!read!read!read!read!read!read!read!read!read!read!read!read!read!read!read!
// ll vs. int!