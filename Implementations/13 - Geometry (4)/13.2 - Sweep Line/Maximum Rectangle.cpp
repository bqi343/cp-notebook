/**
* Description: Computes size of max rectangle in grid w/ obstacles
* Source: Own
* Verification: https://cses.fi/problemset/task/1147/
*/

int n,m,cur[1000];
char g[1000][1000];
ll ans = 0;
 
void processCol(int x) {
    vi nex[m+1];
    F0R(i,n) nex[cur[i]-x].pb(i);
    
    DSU<1000> D = DSU<1000>();
    F0Rd(i,m+1) for (int a: nex[i]) {
        D.par[a] = a;
        if (a > 0 && D.par[a-1] != -1) D.unite(a,a-1);
        if (a < n-1 && D.par[a+1] != -1) D.unite(a,a+1);
        ans = max(ans,i*(ll)D.sz[D.get(a)]);
    }
}
 
int solve() {
    F0R(i,n) cur[i] = m;
    F0Rd(j,m) {
        F0R(i,n) if (g[i][j] == '*') cur[i] = j; // obstacle
        processCol(j);
    }
    return ans;
}