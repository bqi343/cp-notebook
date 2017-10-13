// https://open.kattis.com/problems/segmentdistance

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

pii A,B,C,D;

pii operator-(pii l, pii r) {
    return {l.f-r.f,l.s-r.s};
}

double dist(pii a, pii b) {
    a = a-b;
    return sqrt(a.f*a.f+a.s*a.s);
}

double area(pii a, pii b, pii c) {
    b = b-a, c = c-a;
    return double(b.s*c.f-b.f*c.s)/2;
}

bool obtuse(pii a, pii b, pii c) {
    a = a-b, c = c-b;
    return a.f*c.f+a.s*c.s < 0;
}

double get(pii a, pii b, pii c) {
    if (b == c) return dist(a,b);
    if (obtuse(a,b,c)) return dist(a,b);
    if (obtuse(a,c,b)) return dist(a,c);
    return abs(2*area(a,b,c))/dist(b,c);
}

bool inter(pii A, pii B, pii C, pii D) {
    if (area(A,B,C)*area(A,B,D) > 0) return 0;
    if (area(C,D,A)*area(C,D,B) > 0) return 0;
    if (max(A,B) < min(C,D) || max(C,D)<min(A,B)) return 0;
    return 1;
}

double solve() {
    cin >> A.f >> A.s >> B.f >> B.s >> C.f >> C.s >> D.f >> D.s;
    if (A == B) return get(A,C,D);
    if (C == D) return get(C,A,B);
    
    if (inter(A,B,C,D)) return 0;
    return min(min(get(A,C,D),get(B,C,D)),min(get(C,A,B),get(D,A,B)));
}

int main() {
    ios_base::sync_with_stdio(0);cin.tie(0);
    int n; cin >> n;
    cout << fixed << setprecision(2);
    F0R(i,n) cout << solve() << "\n";
}

// read!
// ll vs. int!
