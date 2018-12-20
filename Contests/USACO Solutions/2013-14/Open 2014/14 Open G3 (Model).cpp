// oops I should do this completely from scratch sometime

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

const int MOD = 1234567;
const int MX = 1<<15;

int N,M, p[MX];
set<int> cpath[MX], ppath[MX];
vector<pi> tmp[MX];
map<int,int> val[MX];

int SEG[2*MX], adp[1<<20], adp_index[1<<20], adp_start[1<<20];
vi atree[1<<20];

int con(string y) {
    int d = 0;
    F0R(i,sz(y)) d += (y[i]-'0'+1)<<(4*(sz(y)-1-i));
    return d;
}

void initialize() {
    freopen("code.in","r",stdin);
    freopen("code.out","w",stdout);
    
    fill_n(SEG,2*MX,1);
    fill_n(adp_index,1<<20,-1);
    
	cin >> N >> M;
	ppath[0].insert(0);
	FOR(i,1,N) {
	    cin >> p[i];
	    ppath[i].insert(0);
	    tmp[p[i]].pb({0,i});
	}
	F0R(i,M) {
	    int x; string y; cin >> x >> y;
	    int d = con(y);
	    cpath[x].insert(d);
	    
	    FORd(i,1,5) {
	        d %= 1<<(4*i); 
	        ppath[x].insert(d);
	        tmp[p[x]].pb({d,x});
	        x = p[x];
	    }
	}
	F0R(i,N) {
	    sort(all(tmp[i]));
	    tmp[i].erase(unique(all(tmp[i])),tmp[i].end());
	}
}

void recalc(int ind) {
    for (ind /= 2; ind; ind /= 2) SEG[ind] = (ll)SEG[2*ind]*SEG[2*ind+1]%MOD;
}

void solve_tree(int ind, int cur) {
    vi pre;
    
    for (int i = adp_start[cur]; i < sz(tmp[ind]) && tmp[ind][i].f == cur; ++i) {
        int v = tmp[ind][i].s;
        int prev = val[v][cur];
        int pos = MX + v;
        swap(prev, SEG[pos]);
        recalc(pos);
        pre.pb(prev);
    }
    
    adp[cur] = SEG[1];
    for (int i: atree[cur]) solve_tree(ind,i);
    for (int i = adp_start[cur], j = 0; i < sz(tmp[ind]) && tmp[ind][i].f == cur; ++i, ++j){
        int pos = MX + tmp[ind][i].s;
        SEG[pos] = pre[j];
        recalc(pos);
    }
}

void solve(int ind) {
    atree[0].clear(); adp_index[0] = ind; adp_start[0] = 0;
    
    F0R(i,sz(tmp[ind])) {
        int S = tmp[ind][i].f;
        if (S == 0 || (i > 0 && tmp[ind][i].f == tmp[ind][i-1].f)) continue;
        atree[S].clear(); adp_index[S] = ind; adp_start[S] = i;
        
        while (adp_index[S>>4] != ind) {
            atree[S>>4] = {S}; adp_index[S>>4] = ind; adp_start[S>>4] = i;
            S >>= 4;
        }
        atree[S>>4].pb(S);
    }
    
    solve_tree(ind,0);
    for (int i: ppath[ind]) {
        int ori = i;
        while (i && i < 1<<(4*3)) i <<= 4;
        FOR(j,1,11) {
            int I = i|(j<<(4*4));
            if (cpath[ind].count(I)) continue;
            while (adp_index[I] != ind) I >>= 4;
            val[ind][ori] = (val[ind][ori]+adp[I])%MOD;
        }
    }
}

int main() {
	initialize();
	F0Rd(i,N) solve(i);
	int ans = 1; F0R(i,N) ans = ans*10%MOD;
	ans = (ans-val[0][0]+MOD)%MOD;
	cout << ans;
}

// read!read!read!read!read!read!read!read!read!read!read!read!read!read!read!read!
// ll vs. int!
