#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;
 
typedef long long ll;
typedef long double ld;
typedef complex<ld> cd;

typedef pair<int, int> pi;
typedef pair<ll,ll> pl;
typedef pair<double,double> pd;

typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<pi> vpi;

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
const int MX = 100001;

int N,M, in[100001];
vi res, adj[100001];
vi v[50000];

vi get(int mid) {
    priority_queue<int,vi,greater<int>> todo;
    res.clear();
    FOR(i,1,N+1) {
        in[i] = 0;
        adj[i].clear();
    }
    
    F0R(i,mid) F0R(j,sz(v[i])-1) {
        in[v[i][j+1]] ++;
        adj[v[i][j]].pb(v[i][j+1]);
    }
    
    FOR(i,1,N+1) if (in[i] == 0) todo.push(i);
    while (sz(todo)) {
        int x = todo.top(); todo.pop();
        res.pb(x);
        for (int i: adj[x]) {
            in[i] --;
            if (!in[i]) todo.push(i);
        }
    }
    return res;
}

int main() {
    freopen("milkorder.in","r",stdin);
    freopen("milkorder.out","w",stdout);
    cin >> N >> M;
    F0R(i,M) {
        int m; cin >> m; v[i].resize(m);
        F0R(j,m) cin >> v[i][j];
    }
    int lo = 0, hi = M;
    while (lo < hi) {
        int mid = (lo+hi+1)/2;
        vi x = get(mid);
        if (sz(x) == N) lo = mid;
        else hi = mid-1;
    }
    vi x = get(lo); 
    F0R(i,sz(x)) {
        if (i) cout << " ";
        cout << x[i];
    }
}

// read the question correctly (is y a vowel?)
// look out for SPECIAL CASES (n=1?) and overflow (ll vs int?)