#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
 
using namespace std;
using namespace __gnu_pbds;
  
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pi;
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
 
int N,Q, ans[100001];
vector<array<int,3>> ed, q;
 
template<int SZ> struct DSU {
    int par[SZ], sz[SZ];
    DSU() {
        F0R(i,SZ) par[i] = i, sz[i] = 1;
    }
     
    int get(int x) { // path compression
        if (par[x] != x) par[x] = get(par[x]);
        return par[x];
    }
     
    bool unite(int x, int y) { // union-by-rank
        x = get(x), y = get(y);
        if (x == y) return 0;
        if (sz[x] < sz[y]) swap(x,y);
        sz[x] += sz[y], par[y] = x;
        return 1;
    }
};
 
DSU<100001> D;
 
int main() {
    freopen("mootube.in","r",stdin);
    freopen("mootube.out","w",stdout);
     
    cin >> N >> Q;
    F0R(i,N-1) {
        int a,b,c; cin >> a >> b >> c;
        ed.pb({c,a,b});
    }
    F0R(i,Q) {
        int k,v; cin >> k >> v;
        q.pb({k,v,i});
    }
    sort(ed.rbegin(),ed.rend());
    sort(q.rbegin(),q.rend());
     
    int nex = 0;
    for (auto a: q) {
        while (nex < sz(ed) && ed[nex][0] >= a[0]) {
            D.unite(ed[nex][1],ed[nex][2]);
            nex ++;
        }
        ans[a[2]] = D.sz[D.get(a[1])];
    }
    F0R(i,Q) cout << ans[i]-1 << "\n";
}
 
// read!read!read!read!read!read!read!read!read!read!read!read!read!read!read!read!
// ll vs. int!
