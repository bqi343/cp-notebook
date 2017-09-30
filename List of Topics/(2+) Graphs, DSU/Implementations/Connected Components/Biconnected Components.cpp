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

ll N,M,K,I, p[150000];
const int NIL = -1;

int count = 0;

struct Edge {
    int u, v;
    Edge(int U, int V) { u = U, v = V; }
};

struct Graph {
    int V, E;    
    vector<vi> adj, fin;
    vi disc,low,parent;
    vector<Edge> st;
   
    Graph(int v) {
        V = v, E = 0;
        adj.resize(V);
    }
    void addEdge(int v, int w) {
        adj[v].pb(w), E++;
    }
    
    // st -- >> To store visited edges

    void BCCUtil(int u) {
        static int time = 0;
       
        disc[u] = low[u] = ++time;
        int children = 0;
       
        for (int v: adj[u]) {
            if (disc[v] == -1) {
                children++;
                parent[v] = u;
                st.pb(Edge(u,v));
                BCCUtil(v);
       
                // Check if the subtree rooted with 'v' has a
                // connection to one of the ancestors of 'u'
                // Case 1 -- per Strongly Connected Components Article
                low[u]  = min(low[u], low[v]);
      
                //If u is an articulation point,
                //pop all edges from stack till u -- v
                if( (disc[u] == 1 && children > 1) || (disc[u] > 1 && low[v] >= disc[u]) ) {
                    vi z;
                    while(st.back().u != u || st.back().v != v) {
                        z.pb(st.back().u); z.pb(st.back().v);
                        st.pop_back();
                    }
                    z.pb(st.back().u); z.pb(st.back().v);
                    sort(z.begin(),z.end()); 
                    z.erase(unique(z.begin(),z.end()),z.end());
                    fin.pb(z);
                    st.pop_back();
                }
            }
       
            // Update low value of 'u' only of 'v' is still in stack
            // (i.e. it's a back edge, not cross edge).
            // Case 2 -- per Strongly Connected Components Article
            else if(v != parent[u] && disc[v] < low[u]) {
                low[u]  = min(low[u], disc[v]);
                st.pb(Edge(u,v));
            }
        }
    }
    
    void BCC() {
        disc.resize(V), low.resize(V), parent.resize(V);
        F0R(i,V) disc[i] = low[i] = parent[i] = NIL;
       
        F0R(i,V) {
            if (disc[i] == NIL) BCCUtil(i);
              
            vi z;
            while(st.size() > 0) {
                z.pb(st.back().u), z.pb(st.back().v);
                st.pop_back();
            }
            if (z.size()) {
                sort(z.begin(),z.end());
                z.erase(unique(z.begin(),z.end()),z.end());
                fin.pb(z);
            }
        }
    }
};

int main() {
    ios_base::sync_with_stdio(0);cin.tie(0);
	Graph g(12);
    g.addEdge(0,1);g.addEdge(1,0);
    g.addEdge(1,2);g.addEdge(2,1);
    g.addEdge(1,3);g.addEdge(3,1);
    g.addEdge(2,3);g.addEdge(3,2);
    g.addEdge(2,4);g.addEdge(4,2);
    g.addEdge(3,4);g.addEdge(4,3);
    g.addEdge(1,5);g.addEdge(5,1);
    g.addEdge(0,6);g.addEdge(6,0);
    g.addEdge(5,6);g.addEdge(6,5);
    g.addEdge(5,7);g.addEdge(7,5);
    g.addEdge(5,8);g.addEdge(8,5);
    g.addEdge(7,8);g.addEdge(8,7);
    g.addEdge(8,9);g.addEdge(9,8);
    g.addEdge(10,11);g.addEdge(11,10);
    g.BCC();
    
    for (auto a: g.fin) {
        for (int b: a) cout << b << " ";
        cout << "\n";
    }
}

// read!
// ll vs. int!
