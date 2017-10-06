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

vi circuit, adj[10];

void find_circuit(int x) { // directed graph, possible that resulting circuit is not valid
    while (adj[x].size()) {
        int j = adj[x][adj[x].size()-1]; adj[x].erase(adj[x].end()-1);
        find_circuit(j);
    }
    circuit.pb(x);
}

int main() {
	ios_base::sync_with_stdio(0);cin.tie(0);
	int N,M; cin >> N >> M;
	F0R(i,M) {
	    int a,b; cin >> a >> b; 
	    adj[a].pb(b);
	}
	find_circuit(1);
	for (int i: circuit) cout << i << " ";
}

// read!
// ll vs. int!
