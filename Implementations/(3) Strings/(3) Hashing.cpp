/**
* Source: own
* Description: Pairs reduce frequency of collision
*/

typedef pair<ll, ll> pll;

template<class T> pair<T,T> operator+(const pair<T,T>& l, const pair<T,T>& r) {
    return {(l.f+r.f)%MOD,(l.s+r.s)%MOD};
}
 
template<class T> pair<T,T> operator-(const pair<T,T>& l, const pair<T,T>& r) {
    return {(l.f-r.f+MOD)%MOD,(l.s-r.s+MOD)%MOD};
}
 
template<class T> pair<T,T> operator*(const pair<T,T>& l, const T& r) {
    return {l.f*r%MOD,l.s*r%MOD};
}

template<class T> pair<T,T> operator*(const pair<T,T>& l, const pair<T,T>& r) {
    return {l.f*r.f%MOD,l.s*r.s%MOD};
}
    
struct hsh {
    string S; 
    vector<pll> po, ipo, cum;
    pll base = mp(948392576,573928192);
    
    ll modpow(ll b, ll p) {
        return !p?1:modpow(b*b%MOD,p/2)*(p&1?b:1)%MOD;
    }
    
    ll inv(ll x) {
        return modpow(x,MOD-2);
    }
    
    void gen(string _S) {
        S = _S;
        po.resize(sz(S)), ipo.resize(sz(S)), cum.resize(sz(S)+1);
        po[0] = ipo[0] = {1,1};
        FOR(i,1,sz(S)) {
            po[i] = po[i-1]*base;
            ipo[i] = {inv(po[i].f),inv(po[i].s)};
        }
        F0R(i,sz(S)) cum[i+1] = cum[i]+po[i]*(ll)(S[i]-'a'+1);
    }
    
    pll get(int l, int r) {
        return ipo[l]*(cum[r+1]-cum[l]);
    }
};

int lcp(hsh& a, hsh& b) { // can be used to generate a suffix array
    int lo = 0, hi = min(sz(a.S),sz(b.S));
    while (lo < hi) {
        int mid = (lo+hi+1)/2;
        if (a.get(0,mid-1) == b.get(0,mid-1)) lo = mid;
        else hi = mid-1;
    }
    return lo;
}

int main() {
    string _S = "abacaba";
    hsh h; h.gen(_S);
    F0R(i,sz(_S)) FOR(j,i,sz(_S)) cout << i << " " << j << " " << h.get(i,j).f << " " << h.get(i,j).s << "\n";
    
    hsh H; H.gen("abadaba");
    cout << lcp(h,H);
}
