/**
* Description: Computes # of rectangles of each size which contain no obstacles
* Verification: https://cses.fi/problemset/task/1148/
*/

const int MX = 1002;

int n,m, cur[MX],ans[MX][MX];
pi tmp[MX][MX];
char g[MX][MX];

pi operator+(pi a, pi b) {
    return {a.f+b.f,a.s+b.s};
}

pi operator-(pi a, pi b) {
    return {a.f-b.f,a.s-b.s};
}

void upd(int x, int l, int r, pi val) {
    tmp[x][l] = tmp[x][l] + val;
    tmp[x][r+1] = tmp[x][r+1] - val;
}

void ins(int x, int l, int r) {
    if (l > r) swap(l,r);
    
    upd(x,1,l-1,{1,0});
    upd(x,l,r,{0,l});
    upd(x,r+1,l+r-1,{-1,l+r});
}

void solve(int x) {
    vector<pi> v;
    F0R(i,n) v.pb({cur[i]-x,i});
    sort(v.rbegin(),v.rend());
    
    set<int> bad;
    FOR(i,-1,n+1) bad.insert(i);
    for (pi x: v) {
        auto it = bad.find(x.s);
        ins(x.f,x.s-*prev(it),*next(it)-x.s);
        bad.erase(it);
    }
}

void propagate(int x) {
    FOR(i,1,n+1) {
        tmp[x][i] = tmp[x][i]+tmp[x][i-1];
        ans[x][i] = tmp[x][i].f*i+tmp[x][i].s;
    }
}

int main() {
    cin >> n >> m;
    F0R(i,n) F0R(j,m) cin >> g[i][j];
    F0R(i,n) cur[i] = m;
    F0Rd(j,m) {
        F0R(i,n) if (g[i][j] == '*') cur[i] = j;
        solve(j);
    }
    FOR(j,1,m+1) propagate(j);
    FORd(j,1,m) FOR(i,1,n+1) ans[j][i] += ans[j+1][i];
    FOR(i,1,n+1) {
        FOR(j,1,m+1) cout << ans[j][i] << " ";
        cout << "\n";
    }
}
