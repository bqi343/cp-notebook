#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;
 
typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef pair<int, int> pi;
typedef pair<ll,ll> pl;
typedef pair<double,double> pd;

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

struct SegTree {
    ll seg[1<<18];
    
    SegTree() { F0R(i,1<<18) seg[i] = INF; }
    
    void upd(int x, ll val) {
        for (seg[x += (1<<17)] = val; x > 1; x /= 2) 
            seg[x/2] = min(seg[x],seg[x^1]);
    }
    
    ll query(int lo, int hi) {
        hi ++;
        ll ret = INF;
        for (lo += (1<<17), hi += (1<<17); lo < hi; lo /= 2, hi /= 2) {
            if (lo&1) ret = min(ret,seg[lo++]);
            if (hi&1) ret = min(ret,seg[--hi]);
        }
        return ret;
    }
};

SegTree S[2][2];
int N,M,co;
map<pi,int> m;
vector<array<int,3>> v, query, q;
ll ans[100000];

void init() {
    freopen("slingshot.in","r",stdin);
    freopen("slingshot.out","w",stdout);
    cin >> N >> M;
    F0R(i,N) {
        int x,y,t; cin >> x >> y >> t;
        if (!m.count({y,x})) m[{y,x}] = t;
        else m[{y,x}] = min(m[{y,x}],t);
    }
    for (auto& a: m) {
        v.pb({a.f.f,a.f.s,a.s}); // y, x
        q.pb({a.f.s,a.f.f,a.s});
        S[1][0].upd(co,(ll)a.f.s-a.f.f+a.s);
        S[1][1].upd(co,(ll)a.f.s+a.f.f+a.s);
        a.s = co++;
    }
    F0R(i,M) {
        int x,y; cin >> x >> y;
        query.pb({x,y,i});
    }
    
    sort(all(q));
    sort(all(query));
}

void answer() {
    int ind = 0;
    for (auto x: query) {
        ans[x[2]] = abs(x[1]-x[0]);
        while (ind < sz(q) && q[ind][0] <= x[0]) {
            auto a = q[ind++];
            
            swap(a[0],a[1]);
            int co = m[{a[0],a[1]}];
            S[1][0].upd(co,INF);
            S[1][1].upd(co,INF);
            S[0][0].upd(co,-(ll)a[1]-a[0]+a[2]);
            S[0][1].upd(co,-(ll)a[1]+a[0]+a[2]);
        }
        
        int tmp = co;
        auto it = m.lb({x[1],0});
        if (it != m.end()) tmp = it->s;
        
        ans[x[2]] = min(ans[x[2]],x[0]+x[1]+S[0][0].query(0,tmp-1));
        ans[x[2]] = min(ans[x[2]],x[0]-x[1]+S[0][1].query(tmp,co-1));
        ans[x[2]] = min(ans[x[2]],-x[0]+x[1]+S[1][0].query(0,tmp-1));
        ans[x[2]] = min(ans[x[2]],-x[0]-x[1]+S[1][1].query(tmp,co-1));
    }
}

int main() {
    init();
    answer();
    F0R(i,M) cout << ans[i] << "\n";
}

// read the question correctly (is y a vowel?)
// look out for special cases (n=1?) and overflow (ll vs int?)
