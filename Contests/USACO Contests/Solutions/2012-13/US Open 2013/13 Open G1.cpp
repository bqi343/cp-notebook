#include<fstream>
#include<vector>
#include<set>
// #include<iostream>
#include<algorithm>

using namespace std;
 
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pi;

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

int N,M, lst = 0;
int bad[200002], dp[200002];
int mn[200002], mx[200002];
set<pi> cur;
vector<pi> ok, z;

void setbad(int x, int y) {
    bad[x] ++; bad[y+1] --;
}

void solve() {
    dp[N+1] = 0;
    FORd(i,1,N+1) {
        dp[i] = -1;
        if (bad[i] == 0) if (dp[mx[i]+1] != -1) dp[i] = max(dp[i],1+dp[mx[i]+1]); // place it
        if (mn[i] != i) dp[i] = max(dp[i],dp[i+1]); // don't place it
    }
}

void createbad() {
    for (pi a: ok) {
	    while (cur.size() > 0 && cur.begin()->f < a.f) {
	        pi x = *cur.begin();
	        z.pb({x.s,x.f});
	        cur.erase(cur.begin());
	    }
	    while (cur.size() > 0 && prev(cur.end())->f >= a.s) {
	        setbad(prev(cur.end())->s,a.f-1);
	        setbad(a.s+1,prev(cur.end())->f);
	        cur.erase(prev(cur.end()));
	    }
	    cur.insert({a.s,a.f});
	}
	while (cur.size() > 0) {
	    pi x = *cur.begin();
	    z.pb({x.s,x.f});
	    cur.erase(cur.begin());
	}
	FOR(i,1,N+1) bad[i] += bad[i-1];
	sort(z.begin(),z.end());
}

void again() {
    int nex = 0;
    set<pi> cur;
    FOR(i,1,N+1) {
        while (cur.size() && cur.begin()->f < i) cur.erase(cur.begin());
        if (nex < z.size() && z[nex].f == i) {
            cur.insert({z[nex].s,z[nex].f});
            nex++;
        }
        if (cur.size()) mn[i] = cur.begin()->f, mx[i] = prev(cur.end())->f;
        else mn[i] = MOD,mx[i] = i;
    }
}

bool comp (pi a, pi b) {
    if (a.f != b.f) return (a.f < b.f);
    return (a.s > b.s);
}

int main() {
    ifstream cin ("photo.in");
    ofstream cout ("photo.out");
	cin >> N >> M;
	F0R(i,M) {
	    int a,b; cin >> a >> b;
	    ok.pb({a,b});
	}
	sort(ok.begin(),ok.end(),comp);
	createbad();
	//for (auto a: z) cout << a.f << " " << a.s << "\n";
	again();
	solve();
    cout << dp[1];
}
