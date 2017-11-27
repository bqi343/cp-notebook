// https://open.kattis.com/problems/longincsubseq

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

const int MOD = 1000000007;

int n, pre[100000], a[100000];
set<pair<ll,pii>> bes; // number, length, index

void solve() {
    bes.clear(); bes.insert({-1e18,{0,-1}});
    F0R(i,n) {
        cin >> a[i];
        auto b = *prev(bes.lb({a[i],{-MOD,-MOD}}));
        pre[i] = b.s.s;
        auto it = bes.lb({a[i],{-MOD,-MOD}});
        if (it != bes.end() && it->s.f == b.s.f+1) bes.erase(it);
        bes.insert({a[i],{b.s.f+1,i}});
    }
    auto z = *bes.rbegin();
    vi ans;
    
    int ind = z.s.s;
    while (ind != -1) {
        ans.pb(ind);
        ind = pre[ind];
    }
    reverse(ans.begin(),ans.end());
    cout << ans.size() << "\n";
    for (int i: ans) cout << i << " ";
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(0);cin.tie(0);
    while (cin >> n) solve();
}

// read!
// ll vs. int!