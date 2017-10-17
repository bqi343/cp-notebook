// http://www.geeksforgeeks.org/biconnected-components/

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

struct BCC {
    int V, ti = 0;
    vector<vi> adj;
    vi par, disc, low;
    vector<vector<pii>> fin;
    vector<pii> st;
    
    void init(int _V) {
        V = _V;
        par.resize(V), disc.resize(V), low.resize(V), adj.resize(V);
        F0R(i,V) par[i] = disc[i] = low[i] = -1;
    }
    void addEdge(int u, int v) {
        adj[u].pb(v), adj[v].pb(u);
    }
    
    void BCCutil(int u) {
        disc[u] = low[u] = ti++;
        int child = 0;
        
        for (int i: adj[u]) if (i != par[u]) {
            if (disc[i] == -1) {
                par[i] = u;
                child ++;
                st.pb({u,i});
                BCCutil(i);
                low[u] = min(low[u],low[i]);
                
                if ((disc[u] == 0 && child > 1) || (disc[u] != 0 && disc[u] <= low[i])) {
                    vector<pii> tmp;
                    while (st.back() != mp(u,i)) tmp.pb(st.back()), st.pop_back();
                    tmp.pb(st.back()), st.pop_back();
                    fin.pb(tmp);
                }
            } else if (disc[i] < low[u]) {
                low[u] = disc[i];
                st.pb({u,i});
            }
        }
    }
    
    void bcc() {
        F0R(i,V) if (disc[i] == -1) {
            BCCutil(i);
            if (st.size()) fin.pb(st);
            st.clear();
        }
    }
};

int main() {
	ios_base::sync_with_stdio(0);cin.tie(0);
	BCC g; g.init(12);
	g.addEdge(0,1);
    g.addEdge(1,2);
    g.addEdge(1,3);
    g.addEdge(2,3);
    g.addEdge(2,4);
    g.addEdge(3,4);
    g.addEdge(1,5);
    g.addEdge(0,6);
    g.addEdge(5,6);
    g.addEdge(5,7);
    g.addEdge(5,8);
    g.addEdge(7,8);
    g.addEdge(8,9);
    g.addEdge(10,11);
    g.bcc();
    
    for (auto a: g.fin) {
        for (pii b: a) cout << b.f << " " << b.s << " | ";
        cout << "\n";
    }
}

// read!
// ll vs. int!
