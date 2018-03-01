#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;
 
typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef pair<int, int> pi;
typedef vector<pi> vpi;
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
const int MX = 100000;

int N,B,A[MX],mxdif = 1;
bool ans[MX];
multiset<int> m;
vpi v;
vector<array<int,3>> q;

int main() {
    freopen("snowboots.in","r",stdin);
    freopen("snowboots.out","w",stdout);
    
    cin >> N >> B;
    F0R(i,N) m.insert(i);
    F0R(i,N) {
        cin >> A[i];
        v.pb({A[i],i});
    }
    sort(all(v));
    F0R(i,B) {
        int s,d; cin >> s >> d;
        q.pb({s,d,i});
    }
    sort(q.rbegin(),q.rend());
    for (auto a: q) {
        while (sz(v) && v.back().f > a[0]) {
            auto it = m.find(v.back().s);
            mxdif = max(mxdif,*next(it)-*prev(it));
            v.pop_back();
            m.erase(it);
        }
        if (a[1] >= mxdif) ans[a[2]] = 1;
    }
    F0R(i,B) cout << ans[i] << "\n";
}

// read the question correctly (is y a vowel?)
// look out for special cases (n=1?) and overflow (ll vs int?)
