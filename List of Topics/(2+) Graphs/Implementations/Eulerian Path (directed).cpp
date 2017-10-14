// https://open.kattis.com/problems/eulerianpath
// extra log factor

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

vi circuit;
multiset<int> adj[10000], adj1[10000];
int N,M, out[10000], in[10000];

void find_circuit(int x) { // directed graph, possible that resulting circuit is not valid
    while (adj[x].size()) {
        int j = *adj[x].begin(); adj[x].erase(adj[x].begin());
        find_circuit(j);
    }
    circuit.pb(x);
}

int a,b,start; 

void solve() {
    F0R(i,N) {
        adj[i].clear(), adj1[i].clear();
        out[i] = in[i] = 0;
    }
    circuit.clear();
    F0R(i,M) {
        cin >> a >> b; 
        adj[a].insert(b), adj1[a].insert(b);
        out[a] ++, in[b] ++;
    }
    start = a;
    F0R(i,N) if (out[i]-in[i] == 1) start = i;
    
    find_circuit(start);
    reverse(circuit.begin(),circuit.end());
    
    if (circuit.size() != M+1) {
        cout << "Impossible\n";
        return;
    }
    
    F0R(i,M) {
        if (adj1[circuit[i]].find(circuit[i+1]) == adj1[circuit[i]].end()) {
            cout << "Impossible\n";
            return;
        }
        adj1[circuit[i]].erase(adj1[circuit[i]].find(circuit[i+1]));
    }
    F0R(i,M+1) cout << circuit[i] << " ";
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(0);cin.tie(0);
    while (cin >> N >> M) {
        if (N+M == 0) break;
        solve();
    }
}

// read!
// ll vs. int!
