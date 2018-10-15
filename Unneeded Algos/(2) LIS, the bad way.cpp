// https://open.kattis.com/problems/longincsubseq

int n, pre[100000], a[100000];
set<pair<ll,pi>> bes; // number, length, index

void solve() {
    bes.clear(); bes.insert({-1e18,{0,-1}});
    F0R(i,n) {
        cin >> a[i];
        auto b = *prev(bes.lb({a[i],{-MOD,-MOD}}));
        pre[i] = b.s.s;
        auto it = bes.lb({a[i],{-MOD,-MOD}});
        if (it != bes.end() && it->s.f == b.s.f+1) bes.erase(it);
        bes.insert({a[i],{b.s.f+1,i}});
    }
    auto z = *bes.rbegin();
    vi ans;
    
    int ind = z.s.s;
    while (ind != -1) {
        ans.pb(ind);
        ind = pre[ind];
    }
    reverse(ans.begin(),ans.end());
    cout << ans.size() << "\n";
    for (int i: ans) cout << i << " ";
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(0);cin.tie(0);
    while (cin >> n) solve();
}

// read!
// ll vs. int!
