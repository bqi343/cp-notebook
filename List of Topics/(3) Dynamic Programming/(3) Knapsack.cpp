// https://open.kattis.com/problems/knapsack

double C;
int n,v[2000],w[2000],dp[2001][2001];

void solve() {
    F0R(i,n) cin >> v[i] >> w[i];
    F0R(i,n) {
        F0R(j,C+1) dp[i+1][j] = dp[i][j];
        F0R(j,C+1) if (w[i]+j <= C) dp[i+1][w[i]+j] = max(dp[i+1][w[i]+j],dp[i][j]+v[i]);
    }
    
    vi ans;
    int x = C;
    F0Rd(i,n) if (dp[i][x] != dp[i+1][x]) x -= w[i], ans.pb(i);
    
    cout << ans.size() << "\n";
    for (int i: ans) cout << i << " ";
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(0);cin.tie(0);
    while (cin >> C >> n) solve();
}