// https://en.wikibooks.org/wiki/Algorithm_Implementation/Geometry/Convex_hull/Monotone_chain
// 5 min
// https://open.kattis.com/problems/convexhull

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

#define mp make_pair
#define pb push_back
#define f first
#define s second
#define lb lower_bound
#define ub upper_bound

const int MOD = 1000000007;

ll cross(pii O, pii A, pii B) {
    return (ll)(A.f-O.f)*(B.s-O.s)-(ll)(A.s-O.s)*(B.f-O.f);
}

vector<pii> convex_hull(vector<pii> P) {
    sort(P.begin(),P.end()); P.erase(unique(P.begin(),P.end()),P.end());
    if (P.size() == 1) return P;
    
    int n = P.size();
    
    vector<pii> bot = {P[0]};
    FOR(i,1,n) {
        while (bot.size() > 1 && cross(bot[bot.size()-2], bot[bot.size()-1], P[i]) <= 0) bot.pop_back();
        bot.pb(P[i]);
    }
    bot.pop_back();
    
    vector<pii> up = {P[n-1]};
    F0Rd(i,n-1) {
        while (up.size() > 1 && cross(up[up.size()-2], up[up.size()-1], P[i]) <= 0) up.pop_back();
        up.pb(P[i]);
    }
    up.pop_back();
    
    bot.insert(bot.end(),up.begin(),up.end());
    return bot;
}

int main() {
    int n;
    while (cin >> n) {
        if (n == 0) break;
        vector<pii> P(n); F0R(i,n) cin >> P[i].f >> P[i].s;
        vector<pii> hull = convex_hull(P);
        
        cout << hull.size() << "\n";
        for (auto a: hull) cout << a.f << " " << a.s << "\n";
    }
}
