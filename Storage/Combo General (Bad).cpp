/**
* Description: MOD is any natural number
* Verification: https://dmoj.ca/problem/tle17c4p5
*/

template<int SZ> struct ComboGeneral {
    vector<ComboPower<SZ>> v;
    ll MOD;
    
    void init(ll _MOD) {
        MOD = _MOD;
        for (auto a: NT::fac(MOD)) {
            v.pb(ComboPower<SZ>());
            v.back().init(a);
        }
    }
    
    ll comb(ll a, ll b) {
        pl cur = {0,1};
        for (auto& x: v) cur = NT::CRT({x.comb(a,b),x.MOD},cur);
        return cur.f;
    }
};