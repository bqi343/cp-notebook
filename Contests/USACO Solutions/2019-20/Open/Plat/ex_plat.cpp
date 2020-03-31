#include <bits/stdc++.h>
using namespace std;
 
void setIO(string s) {
    ios_base::sync_with_stdio(0); cin.tie(0); 
    freopen((s+".in").c_str(),"r",stdin);
    freopen((s+".out").c_str(),"w",stdout);
}
 
typedef long long ll;
const int MX = 7501;
 
typedef unsigned long long ul;
typedef __uint128_t L;
struct ModFast {
    ul b, m; ModFast(ul b) : b(b), m(ul((L(1)<<64)/b)) {}
    ul reduce(ul a) {
        ul q = (ul)((L(m)*a)>>64), r = a-q*b;
        return r>=b?r-b:r; }
};
 
ModFast MF(1);
 
int M,MOD,n;
int ad(int a, int b) { 
    a += b; if (a >= M) a -= M;
    return a;
}
int sub(int a, int b) { 
    a -= b; if (a < 0) a += M;
    return a; 
}
int mul(int a, int b) { return MF.reduce((ul)a*b); }
 
int choose[MX][MX];
int with(int z) { // # of permutations with z dividing some cycle length
    int res = 0;
    vector<int> dp(n/z+1); dp[0] = sub(0,1);
    for (int i = 1; i <= n/z; ++i) for (int j = 1; j <= i; ++j)
        dp[i] = sub(dp[i],mul(choose[i*z-1][j*z-1],dp[i-j]));
    for (int i = 1; i <= n/z; ++i) 
        res = ad(res,mul(choose[n][n-i*z],dp[i]));
    return res;
}
 
ll mpow(ll a, ll b) { return !b?1:mpow(a*a%MOD,b/2)*(b&1?a:1)%MOD; }
 
int main() {
    setIO("exercise"); 
    cin >> n >> MOD; M = MOD-1; MF = ModFast(M);
    for (int i = 0; i <= n; ++i) {
        choose[i][0] = 1;
        for (int j = 0; j < i; ++j) choose[i][j+1] = mul(choose[i][j],i-j);
    }
    vector<bool> comp(n+1); ll ans = 1;
    for (int i = 2; i <= n; ++i) if (!comp[i]) {
        for (int j = 2*i; j <= n; j += i) comp[j] = 1;
        for (int j = i; j <= n; j *= i) ans = ans*mpow(i,with(j))%MOD;
    }
    cout << ans << "\n";
}