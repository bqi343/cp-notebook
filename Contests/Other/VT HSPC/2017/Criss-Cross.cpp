#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;
 
typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef pair<int, int> pii;
#define double long double
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

typedef pair<pair<ll,ll>,ll> point;

const int MOD = 1000000007;

int n;
point x[1000], y[1000];
set<point> S;

point A,B,C,D;

point simplify(point x) {
    if (x.s < 0) x.f.f *= -1, x.f.s *= -1, x.s *= -1;
    ll t = abs(__gcd(__gcd(x.f.f,x.f.s),x.s));
    x.f.f /= t, x.f.s /= t, x.s /= t;
    return x;
}

point operator*(ll x, point y) {
    y.f.f *= x, y.f.s *= x;
    return y;
}

point operator/(point y, ll x) {
    y.s *= x;
    return simplify(y);
}

point operator+(point l, point r) {
    return {{l.f.f+r.f.f,l.f.s+r.f.s},1};
}

ll sgn(point a, point b, point c) {
    return (b.f.s-a.f.s)*(c.f.f-a.f.f)-(b.f.f-a.f.f)*(c.f.s-a.f.s);
}

point get(point a, point b, point c, point d) {
    return (abs(sgn(a,b,c))*d+abs(sgn(a,b,d))*c)/(abs(sgn(a,b,c))+abs(sgn(a,b,d)));
}

void solve() {
    if (A > B) swap(A,B);
    if (C > D) swap(C,D);
    
    ll a1 = sgn(A,B,C), a2 = sgn(A,B,D);
    
    if (a1 > a2) swap(a1,a2);
    if (!(a1 <= 0 && a2 >= 0)) return;
    
    if (a1 == 0 && a2 == 0) {
        point x1 = max(A,C), x2 = min(B,D);
        if (x1 == x2) S.insert(x1);
        return;
    }
    
    ll a3 = sgn(C,D,A), a4 = sgn(C,D,B);
    if (a3 > a4) swap(a3,a4);
    if (!(a3 <= 0 && a4 >= 0)) return;
    
    point z = get(A,B,C,D);
    S.insert(z);
}

int main() {
    ios_base::sync_with_stdio(0);cin.tie(0);
    cin >> n;
    F0R(i,n) {
        /*while (x[i].f.f == y[i].f.f && x[i].f.s == y[i].f.s) {
            x[i].f.f = rand()%1000000, x[i].f.s = rand()%1000000;
            y[i].f.f = rand()%1000000, y[i].f.s = rand()%1000000;
        }*/
        cin >> x[i].f.f >> x[i].f.s >> y[i].f.f >> y[i].f.s;
        x[i].s = y[i].s = 1;
    }
    F0R(i,n) {
        FOR(j,i+1,n) {
            A = x[i], B = y[i];
            C = x[j], D = y[j];
            solve();
        }
    }
    cout << S.size();
    // for (auto a: S) cout << a.f.f << " " << a.f.s << " " << a.s << "\n";
}

// read!read!read!read!read!read!read!read!read!read!read!read!read!read!read!read!
// ll vs. int!