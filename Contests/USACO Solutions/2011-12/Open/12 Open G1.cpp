/*#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp>*/
#include <bits/stdc++.h>

using namespace std;
//using namespace __gnu_pbds;
 
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pi;
//typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;

#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
 
#define mp make_pair
#define pb push_back
#define f first
#define s second
#define lb lower_bound
#define ub upper_bound

const int MOD = 1000000007;
double PI = 4*atan(1);

int N,M,bx,by;
pi fence[10], rope[10000];
vi z;

int get(double x) {
    F0R(i,N) if (fence[i].s > x) return i;
    return N;
}

double yint(pi a, pi b) {
    return double(abs(a.f)*b.s+abs(b.f)*a.s)/abs(a.f-b.f);
}

int side(int x) {
    return (x < 0) ? 0 : 1;
}

bool ok (int ind) {
    int key[N+1]; key[0] = 0;
    F0R(i,N) {
        if (ind&(1<<i)) key[i+1] = i+1;
        else key[i+1] = key[i];
    }
    vi c;
    for (int i: z) {
        if (c.size() && c[c.size()-1] == key[i]) c.erase(c.end()-1);
        else c.pb(key[i]);
    }
    return (c.size() == 0);
}

int main() {
	ios_base::sync_with_stdio(0);cin.tie(0);
	cin >> N >> M >> bx >> by;
	F0R(i,N) cin >> fence[i].f >> fence[i].s;
	sort(fence,fence+N);
	F0R(i,M) cin >> rope[i].f >> rope[i].s;
	F0R(i,M) rope[i].f -= fence[0].f;
	F0R(i,M) 
	    if (side(rope[i].f) != side(rope[(i+1)%M].f)) 
	        z.pb(get(yint(rope[i],rope[(i+1)%M])));
	
	int ans = MOD;
	F0R(i,1<<N) if (ok(i)) ans = min(ans,N-__builtin_popcount(i));
	cout << ans;
}
