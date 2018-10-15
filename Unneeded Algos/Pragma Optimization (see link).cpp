/**
 * Source: Misc solutions to CF Nagini
 * Description: 10^{10} operations are ok!
 * Passes the occasional disgusting CF task 
 * Also see "Welcome home, Chtholly"
 */

#pragma GCC optimize ("O3")
#pragma GCC target ("sse4")

int q, mx[MX], mn[MX];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin >> q;
    F0R(i,MX) mx[i] = -MOD, mn[i] = MOD;
    F0R(i,q) {
        int t,l,r,k; cin >> t >> l >> r;
        r -= l;
        
        auto a = mx+l, b = mn+l;
        if (t == 1) {
            cin >> k;
            if (k > 0) F0R(j,r) b[j] = min(b[j],k);
            else F0R(j,r) a[j] = max(a[j],k);
        } else {
            ll ans = 0;
            F0R(j,r) if (a[j] != -MOD && b[j] != MOD) ans += b[j]-a[j];
            cout << ans << "\n";
        }
    }
}