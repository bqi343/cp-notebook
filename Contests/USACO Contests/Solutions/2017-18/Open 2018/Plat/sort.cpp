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
const int MX = (1<<17)-1;

struct {
    int bit[MX+1];
    void upd(int x, int y) {
        x = MX-x;
        for (; x <= MX; x += (x&-x)) bit[x] += y;
    }
    int getlst0() { // MX --> -1 
        int lo = 0;
        F0Rd(i,17) if (bit[lo^(1<<i)] == (1<<i)) lo ^= 1<<i;
        return MX-1-lo;
    }
    int q(int x) {
        int ans = 0;
        for (;x>0; x -= (x&-x)) ans += bit[x];
        return ans;
    }
    int query(int x) { return q(MX)-q(MX-x); }
} BIT;

int n;
ll ans = 0;
vpi v;
int cur[MX], A[MX];

void process(pi a) {
    int x = BIT.getlst0();
    // F0R(i,n) cout << cur[i] << " ";
    // cout << "\n";
    // cout << x << " " << a.s << " " << BIT.query(max(x,a.s)) << "\n";
    ans += BIT.query(max(x,a.s)); // how many ones before
    BIT.upd(a.s,-1); cur[a.s] = 0;
}

void bubble_sort() {
    ans += n;
    F0R(i,n-1) if (A[i] > A[i+1]) swap(A[i],A[i+1]);
}

int main() {
    freopen("sort.in","r",stdin);
    freopen("sort.out","w",stdout);
    
    cin >> n;
    F0R(i,n) {
        cur[i] = 1;
        cin >> A[i];
    }
    bubble_sort();
    
    F0R(i,n) v.pb({A[i],i});
    F0R(i,MX) BIT.upd(i,1);
    sort(all(v));
    
    for (auto a: v) process(a);
    cout << ans;
}

// read the question correctly (is y a vowel?)
// look out for SPECIAL CASES (n=1?) and overflow (ll vs int?)