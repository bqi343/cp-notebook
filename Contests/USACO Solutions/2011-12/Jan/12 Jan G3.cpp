#include <fstream>
#include <vector>

using namespace std;
//using namespace __gnu_pbds;
 
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pi;
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

int N,M,visit[100001];
int sum = 0, cycle = 0;
ll ans = 1;
vi adj[100001];

void dfs(int par, int node) {
    if (visit[node]) {
        cycle = 1;
        return;
    }    
    sum ++; visit[node] = 1;
    for (int i: adj[node]) if (i != par) dfs(node,i);
}

int main() {
    ifstream cin ("alliance.in");
    ofstream cout ("alliance.out");
	cin >> N >> M;
	F0R(i,M) {
	    int u,v; cin >> u >> v;
	    adj[u].pb(v), adj[v].pb(u);
	}
	FOR(i,1,N+1) if (!visit[i]) {
	    sum = 0, cycle = 0;
	    dfs(0,i);
	    if (cycle) ans = (ans*2) % MOD;
	    else ans = (ans*sum) % MOD;
	}
	cout << ans;
}
