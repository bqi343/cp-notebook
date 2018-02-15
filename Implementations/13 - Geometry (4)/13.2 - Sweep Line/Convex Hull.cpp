/**
* Source: Wikibooks
* Usage: https://open.kattis.com/problems/convexhull
*/

ll cross(pii O, pii A, pii B) {
    return (ll)(A.f-O.f)*(B.s-O.s)
            -(ll)(A.s-O.s)*(B.f-O.f);
}

vector<pii> convex_hull(vector<pii> P) {
    sort(P.begin(),P.end()); P.erase(unique(P.begin(),P.end()),P.end());
    if (P.size() == 1) return P;
    
    int n = P.size();
    
    vector<pii> bot = {P[0]};
    FOR(i,1,n) {
        while (bot.size() > 1 && cross(bot[bot.size()-2], bot.back(), P[i]) <= 0) bot.pop_back();
        bot.pb(P[i]);
    }
    bot.pop_back();
    
    vector<pii> up = {P[n-1]};
    F0Rd(i,n-1) {
        while (up.size() > 1 && cross(up[up.size()-2], up.back(), P[i]) <= 0) up.pop_back();
        up.pb(P[i]);
    }
    up.pop_back();
    
    bot.insert(bot.end(),all(up));
    return bot;
}

int main() {
    int n;
    while (cin >> n) {
        if (n == 0) break;
        vector<pii> P(n); F0R(i,n) cin >> P[i].f >> P[i].s;
        vector<pii> hull = convex_hull(P);
        
        cout << hull.size() << "\n";
        for (auto a: hull) cout << a.f << " " << a.s << "\n";
    }
}
