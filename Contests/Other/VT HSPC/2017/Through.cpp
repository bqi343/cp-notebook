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
#define all(x) x.begin(), x.end()

const int MOD = 1000000007;
const int MX = 100000;

int n,m,d,T[MX], done[MX], ok[MX];
map<string,int> ma;
string S[MX];
vi adj[MX];
vi todo;

void process() {
    vi todo1;
    for (int i: todo) for (int j: adj[i]) {
        ok[j] = 1;
        if (T[j] > 0) {
            T[j] --;
            if (T[j] == 0) {
                todo1.pb(j);
            }
        }
    }
    swap(todo,todo1);
}

int main() {
	ios_base::sync_with_stdio(0);cin.tie(0);
	cin >> n >> m >> d;
	F0R(i,n) {
	    cin >> S[i] >> T[i];
	    ma[S[i]] = i;
	}
	F0R(i,m) {
	    string x,y; cin >> x >> y;
	    adj[ma[x]].pb(ma[y]), adj[ma[y]].pb(ma[x]);
	}
	string r; cin >> r; todo.pb(ma[r]);
	F0R(i,d) process();
	
	int ans = 0;
	F0R(i,n) if (ok[i] == 1 && i != ma[r]) ans++;
	cout << ans;
}

// read!read!read!read!read!read!read!read!read!read!read!read!read!read!read!read!
// ll vs. int!