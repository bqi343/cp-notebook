/*#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp>*/
#include <bits/stdc++.h>

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
double PI = 4*atan(1);

int N,M;
ll wei = 0;
ll ans = 1;
vector<pi> edge[1000001]; 
int par[40001];

int getpar(int x) {
    if (par[par[x]] != par[x]) par[x] = getpar(par[x]);
    return par[x];
}

void unite(int a, int b, ll w) {
    a = getpar(a), b = getpar(b);
    if (a == b) return;
    wei += w;
    par[b] = a;
}

vector<pi> cur;

void test(ll i) {
    cur.clear();
    for (pi x: edge[i]) if (getpar(x.f) != getpar(x.s)) 
        cur.pb({min(getpar(x.f),getpar(x.s)),max(getpar(x.f),getpar(x.s))});
    if (cur.size() == 0) return;
    if (cur.size() == 1) {
        unite(cur[0].f,cur[0].s,i);
        return;
    }
    if (cur.size() == 2) {
        if (cur[0] == cur[1]) ans = (ans*2) % MOD;
        unite(cur[0].f,cur[0].s,i);
        unite(cur[1].f,cur[1].s,i);
        return;
    }
    if (cur[0] == cur[1] && cur[1] == cur[2]) ans = (ans*3) % MOD;
    else if (cur[0] == cur[1] || cur[1] == cur[2] || cur[0] == cur[2]) ans = (ans*2) % MOD;
    else {
        sort(cur.begin(),cur.end());
        if (cur[0].f == cur[1].f && cur[1].s == cur[2].s && cur[0].s == cur[2].f) ans = (ans*3) % MOD;
    }
    unite(cur[0].f,cur[0].s,i);
    unite(cur[1].f,cur[1].s,i);
    unite(cur[2].f,cur[2].s,i);
}

int main() {
	ios_base::sync_with_stdio(0);cin.tie(0);
	cin >> N >> M;
	F0R(i,M) {
	    int a,b,n; cin >> a >> b >> n;
	    edge[n].pb({a,b});
	}
	FOR(i,1,N+1) par[i] = i;
	FOR(i,1,1000001) test(i);
	cout << wei << " " << ans;
}
