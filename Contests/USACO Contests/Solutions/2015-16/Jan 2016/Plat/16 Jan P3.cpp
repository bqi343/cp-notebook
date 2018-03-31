#include <vector>
#include <iostream>
#include <map>

using namespace std;
 
typedef vector<int> vi;
typedef pair<int, int> pi;
typedef long long ll;

#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
 
#define mp make_pair
#define pb push_back
#define f first
#define s second

const int MOD = 1000000007;

struct {
    int L = -MOD, R = -MOD;
    int val = MOD;
} dp[200][200][200][2]; 

int N, cum[400];
pi nex[200][200];
vi x;
vector<pi> point;
map<ll,pi> fst;

int dist (pi a, pi b) {
    return abs(a.f-b.f)+abs(a.s-b.s);
}

int getsum(int l, int r) {
    if (l > r) r += N;
    return cum[r]-cum[l];
}

ll hsh(vi z) {
    ll cur = 0, mult = 1;
    F0R(i,z.size()) {
        cur = (cur+mult*z[i]) % MOD;
        mult = (mult*1347135) % MOD;
    }
    return cur;
}

int angle(pi a, pi b, pi c, int d) {
    if (d == 0) return 0;
    a.f -= b.f, a.s -= b.s;
    c.f -= b.f, c.s -= b.s;
    if (a.s*c.f-a.f*c.s > 0) return 1;
    return 2;
}

void input() {
    freopen("lightsout.in","r",stdin);
    freopen("lightsout.out","w",stdout);
	cin >> N; point.resize(N);
	F0R(i,N) cin >> point[i].f >> point[i].s;
	F0R(i,N) {
	    x.pb(angle(point[(i+(N-1))%N],point[i],point[(i+1)%N],i));
	    x.pb(dist(point[i],point[(i+1)%N]));
	}
	F0R(i,2*N) x.pb(x[i]);
	FOR(i,1,2*N+1) cum[i] = cum[i-1]+x[2*i-1];
}

void gen(int len) {
    F0Rd(i,N) {
        vi tmp(x.begin()+2*i,x.begin()+2*i+2*len+1);
        fst[hsh(tmp)] = mp(i,(i+len)%N);
    }
    F0R(i,N) {
        vi tmp(x.begin()+2*i,x.begin()+2*i+2*len+1);
        nex[i][(i+len)%N] = fst[hsh(tmp)];
    }
    fst.clear();
}

void solve(int st, int lo, int hi, int d) {
    if (lo == 0 || hi == 0 || lo > hi) {
        int tmp;
        if (d == 0) tmp = min(getsum(lo,0),getsum(0,lo));
        else tmp = min(getsum(hi,0),getsum(0,hi));
        dp[st][lo][hi][d].val = tmp-min(getsum(st,0),getsum(0,st));
    } else dp[st][lo][hi][d].val = min(dp[st][lo][hi][d].L,dp[st][lo][hi][d].R);
    
    //cout << st << " " << lo << " " << hi << " " << d << " " << dp[st][lo][hi][d].val << "\n";
    if (lo != hi) {
        if (d == 0) {
            pi t = nex[(lo+1)%N][hi];
            int st1 = (st-(lo+1)+t.f+N) % N;
            dp[st1][t.f][t.s][0].L = max(dp[st1][t.f][t.s][0].L,dp[st][lo][hi][d].val+getsum(lo,lo+1));
            dp[st1][t.f][t.s][1].L = max(dp[st1][t.f][t.s][1].L,dp[st][lo][hi][d].val+getsum(lo,hi));
        } else {
            pi t = nex[lo][(hi+N-1)%N];
            int st1 = (st-lo+t.f+N) % N;
            dp[st1][t.f][t.s][0].R = max(dp[st1][t.f][t.s][0].R,dp[st][lo][hi][d].val+getsum(lo,hi));
            dp[st1][t.f][t.s][1].R = max(dp[st1][t.f][t.s][1].R,dp[st][lo][hi][d].val+getsum(hi+N-1,hi));
        }
    }
}

int main() {
    input();
    F0Rd(len,N+1) gen(len);
	F0Rd(len,N) F0R(i,N) if (nex[i][(i+len)%N] == mp(i,(i+len)%N))
	    FOR(j,i,i+len+1) F0R(k,2) solve(j%N,i,(i+len)%N,k);
	    
	int ans = 0;
	F0R(i,N) if (nex[i][i] == mp(i,i)) ans = max(ans,dp[i][i][i][0].val);
    cout << ans;
}
