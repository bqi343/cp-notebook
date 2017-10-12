// https://open.kattis.com/problems/intervalcover

#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;
 
typedef long long ll;
typedef vector<int> vi;
typedef pair<double, double> pdd;
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

double A,B,cur;
vector<pair<pdd,int>> in;
int N,nex;
vi ans;

void solve() {
    nex = 0; ans.clear();
    cin >> N; in.resize(N);
    F0R(i,N) {
        cin >> in[i].f.f >> in[i].f.s;
        in[i].s = i;
    }
    
    sort(in.begin(),in.end());
    pair<double,int> mx = {-DBL_MAX,-1};
    
    while (nex < in.size() && in[nex].f.f <= A) {
        mx = max(mx,{in[nex].f.s,in[nex].s});
        nex++;
    }
    if (nex == 0) {
        cout << "impossible\n";
        return;
    }
    ans.pb(mx.s);
    
    while (mx.f < B) {
        cur = mx.f;
        while (nex < in.size() && in[nex].f.f <= cur) {
            mx = max(mx,{in[nex].f.s,in[nex].s});
            nex++;
        }
        if (mx.f == cur) {
            cout << "impossible\n";
            return;
        }
        ans.pb(mx.s);
    }
    cout << ans.size() << "\n";
    for (int i: ans) cout << i << " ";
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(0);cin.tie(0);
    while (cin >> A >> B) solve();
}

// read!
// ll vs. int!