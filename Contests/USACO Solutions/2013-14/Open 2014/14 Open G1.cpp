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

int N, K, ans, MB[100000][8], MF[100000][8], PS[100001][8];
vector<pi> cows;

void init() {
    freopen("fairphoto.in","r",stdin);
    freopen("fairphoto.out","w",stdout);
    cin >> N >> K;
    F0R(i,N) {
        pi x; cin >> x.f >> x.s; x.s--;
        cows.pb(x);
    }
    sort(cows.begin(),cows.end());
} 

void gen() {
    F0R(i,8) MB[0][i] = 1<<cows[0].s;
    FOR(i,1,N) {
        int bt = 1<<cows[i].s;
        MB[i][0] = bt;
        FOR(j,1,8) {
            if (MB[i-1][j]&bt) MB[i][j] = MB[i-1][j];
            else MB[i][j] = MB[i-1][j-1]|bt;
        }
    }
    
    F0R(i,8) MF[N-1][i] = 1<<cows[N-1].s;
    F0Rd(i,N-1) {
        int bt = 1<<cows[i].s;
        MF[i][0] = bt;
        FOR(j,1,8)
            if (MF[i+1][j]&bt) MF[i][j] = MF[i+1][j];
            else MF[i][j] = MF[i+1][j-1]|bt;
    }
    F0R(i,N) {
        memcpy(PS[i+1],PS[i],sizeof(PS[i]));
        ++PS[i+1][cows[i].s];
    }
}

int main() {
    init();
    gen();
    FOR(j,K-1,8) {
        vi V(9);
        map<vi,int> cost;
        F0Rd(i,N) {
            int base = -1;
            int m = V[8] = MF[i][j];
            if (__builtin_popcount(m) <= j) continue;
            F0R(k,8)
                if (m&(1<<k)) {
                    if (base == -1) base = PS[i][k];
                    V[k] = PS[i][k]-base;
                } else V[k] = PS[i][k];
                
            cost[V] = cows[i].f;
        }
        F0R(i,N) {
            int base = -1;
            int m = V[8] = MB[i][j];
            if (__builtin_popcount(m) <= j) continue;
            
            F0R(k,8)
                if (m&(1<<k)) {
                    if (base == -1) base = PS[i+1][k];
                    V[k] = PS[i+1][k]-base;
                } else V[k] = PS[i+1][k];
            
            auto it = cost.find(V);
            if (it != cost.end()) {
                ans = max(ans,cows[i].f-(it->s));
            }
        }
    }
    if (ans) cout << ans;
    else cout << -1;
}
