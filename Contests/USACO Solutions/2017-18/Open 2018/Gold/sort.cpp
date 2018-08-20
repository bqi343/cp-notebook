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

int N,ans;
Tree<int> le, ge;
vpi all;

int main() {
    freopen("sort.in","r",stdin);
    freopen("sort.out","w",stdout);
    cin >> N;
    F0R(i,N) {
        int x; cin >> x;
        all.pb({x,i});
        ge.insert(i);
    }
    sort(all(all));
    for (auto a: all) {
        le.insert(a.s);
        int lo = 0, hi = min(sz(le),sz(ge));
        while (lo < hi) {
            int mid = (lo+hi)/2;
            if (*le.find_by_order(sz(le)-1-mid) <= *ge.find_by_order(mid)) hi = mid;
            else lo = mid+1;
        }
        ans = max(ans,lo);
        ge.erase(a.s);
    }
    cout << ans;
}

// read the question correctly (is y a vowel?)
// look out for SPECIAL CASES (n=1?) and overflow (ll vs int?)

/* Python simulator:
N = 11 
A = [0,1,1,1,0,0.5,1,1,0,0,0]

for i in range(11):
    print(A)
    
    for i in range(0,N-1):
        if A[i+1] < A[i]:
            A[i], A[i+1] = A[i+1], A[i]
    
    print(A)
    for i in range(N-2,-1,-1):
        if A[i+1] < A[i]:
            A[i], A[i+1] = A[i+1], A[i]
            
    print(A)
    print("-----")
*/
