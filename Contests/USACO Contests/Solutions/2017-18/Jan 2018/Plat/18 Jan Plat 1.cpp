#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;
 
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pi;
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

int dp[100001][101];
int N, K;
vector<pi> p, P;

bool cmp (pi a, pi b) {
    if (a.f != b.f) return a.f < b.f;
    return a.s > b.s;
}

struct maxDeque {
    deque<pi> mx;
    deque<int> tmp;
    
    int l = 0,r = -1;
    
    int del() {
        if (mx.front().s == l++) mx.pop_front();
        int t = tmp.front();
        tmp.pop_front();
        return t;
    }
    int query() {
        if (mx.size() == 0) return -MOD;
        return mx.front().f;
    }
    void ad(int x) {
        while (sz(mx) && mx.back().f <= x) mx.pop_back();
        mx.pb({x,++r});
        tmp.pb(x);
    }
};

int mx[100001];
maxDeque d[100001];

void upd0(int ind) {
    F0R(i,101) if (ind >= i && dp[ind][i] >= 0) { // remove from deque
        mx[ind-i] = max(mx[ind-i],d[ind-i].del()+P[ind].s);
        if (mx[ind-i] < 0) mx[ind-i] = -MOD;
    }
}

void upd1(int ind) {
    F0R(i,101) if (ind >= i && dp[ind][i] >= 0) {
        d[ind-i].ad(dp[ind][i]-P[ind].s);
    }
}

int get0(int i, int j) {
    // i-k ranges from 0 to nex-1 
	// dp[i][j] = max(dp[i-k][j-(k-1)]);
	int t = mx[i-j-1];
	if (t == -MOD) return t;
	return t+P[i].s-P[i].f;
}

int get1(int i, int j) {
	// nex to i-1
	// dp[i][j] = max(dp[i-k][j-(k-1)]-P[i-k].s);
	if (i-j-1 < 0) return -MOD;
    int t = d[i-j-1].query();
	if (t == -MOD) return t;
	return t+P[i].s;
}

void input() {
    freopen("lifeguards.in","r",stdin);
	freopen("lifeguards.out","w",stdout);
	
	cin >> N >> K; p.resize(N);
	F0R(i,N) cin >> p[i].f >> p[i].s;
	sort(all(p),cmp);
	P.pb({-1,-1});
	
	for (auto a: p) {
	    if (sz(P) && P.back().s >= a.s) {
	        N --;
	        K --;
	        continue;
	    }
	    P.pb(a);
	}
	if (K < 0) K = 0;
}

int main() {
	input();
	F0R(i,N+1) {
	    F0R(j,101) dp[i][j] = -MOD;
	    mx[i] = -MOD;
	}
	dp[0][0] = 0;
	
	int nex = 0;
	upd1(0);
	FOR(i,1,N+1) {
	    while (P[nex].s < P[i].f) upd0(nex++);
	    F0R(j,min(101,i)) {=
	        dp[i][j] = max(get0(i,j),get1(i,j));
	        if (dp[i][j] < 0) dp[i][j] = -MOD;
	    }
	    upd1(i);
	}
	
	int ans = 0;
	F0R(i,N+1) if (K-N+i >= 0) ans = max(ans,dp[i][K-N+i]);
	cout << ans;
}

// read!read!read!read!read!read!read!read!read!read!read!read!read!read!read!read!
// ll vs. int!
