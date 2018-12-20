#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
 
using namespace std;
using namespace __gnu_pbds;
 
template <class T> using Tree = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;
 
#define F0R(i,a) for (int i = 0; i < a; ++i)
#define FOR(i,a,b) for (int i = a; i < b; ++i)
#define sz(a) (int)((a).size())
#define all(a) a.begin(), a.end()
#define f first
#define s second
#define lb lower_bound
#define ub upper_bound
 
typedef long long ll;
typedef pair<int,int> pi;
typedef vector<pi> vpi;
 
const int MX = 100001;
const int SZ = 1<<17;
const int MOD = 1000000007;
 
int D,Tc,T[MX];
pi a,b;
 
ll test(int ind) {
    ll tmp = ind*(Tc-b.f);
    map<int,int> z; z[-MOD] = ind;
    F0R(i,D) {
        int need = T[i];
        while (need) {
            auto it = z.ub(i-b.s);
            if (it == z.begin()) {
                auto it = z.ub(i-a.s);
                if (it == z.begin()) return 2*MOD;
                
                it = prev(it);
                int t = min(need,it->s);
                it->s -= t, need -= t, z[i] += t, tmp += a.f*t;
                if (it->s == 0) z.erase(it);
            } else {
                it = prev(it);
                int t = min(need,it->s);
                it->s -= t, need -= t, z[i] += t, tmp += b.f*t;
                if (it->s == 0) z.erase(it);
            }
        }
        // if (ind == 8) cout << "HI " << i << " " << tmp << "\n";
    }
    return tmp;
}
 
int ternary() {
    int lo = 1, hi = 50*D;
    while (lo+2 < hi) {
        int l = (2*lo+hi)/3, r = (lo+2*hi)/3;
        ll a = test(l), b = test(r);
        if (a == 2*MOD) {
            lo = l+1;
            continue;
        }
        if (a < b) hi = r-1;
        else lo = l+1;
    }
    return min(min(test(lo),test(lo+1)),test(lo+2));
}
 
int main() {
    cin >> D >> a.f >> a.s >> b.f >> b.s >> Tc;
    F0R(i,D) cin >> T[i];
    if (a.s > b.s) swap(a,b);
    a.f = min(a.f,Tc), b.f = min(b.f,a.f);
    cout << ternary();
}