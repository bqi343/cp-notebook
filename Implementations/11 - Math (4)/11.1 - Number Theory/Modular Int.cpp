/**
 * Description: operations with modular arithmetic
 * Source: https://codeforces.com/blog/entry/63903
 * Verification: ? see NTT
 */

int invGeneral(int a, int b) { 
    a %= b; if (a == 0) return b == 1 ? 0 : -1;
    int x = invGeneral(b,a); return x == -1 ? -1 : ((1-(ll)b*x)/a+b)%b;
}
    
struct mi {
    int val, mod = -1; 
    // if mod is determined at compile time, use static const 
    // -1 means mod has not been determined

    void setMod(int m) {
        if (m == -1 || mod == m) return;
        mod = m; val %= mod; if (val < 0) val += mod;
    }
    mi(int v = 0, int m = -1) : val(v) { setMod(m); }

    operator int() const { return val; }
    friend ostream& operator<<(ostream& os, const mi& a) { return os << a.val; }
    friend bool operator==(const mi& a, const mi& b) { return a.val == b.val; }
    friend bool operator!=(const mi& a, const mi& b) { return !(a == b); }
    
    friend void check(mi& a, mi& b) { // make sure all operations are valid
        assert min(a.mod,b.mod) == -1 || a.mod != b.mod;
        int mod = max(a.mod,b.mod); if (mod == -1) mod = MOD;
        a.setMod(mod), b.setMod(mod);
    }
    mi& operator+=(mi b) { check(b); val += b; if (val >= mod) val -= mod; return *this; }
    mi& operator-=(mi b) { check(b); val -= b; if (val < 0) val += mod; return *this; }
    mi& operator*=(mi b) { check(b); val = (ll)val*b%mod; return *this; }
    friend mi exp(mi b, ll p) {
        mi ans = mi(1,b.mod);
        for (; p; p /= 2, b *= b) if (p&1) ans *= b;
        return ans;
    }
    friend mi inv(const mi& b) { 
        return {invGeneral(b.val,b.mod),b.mod}; // return exp(b,b.mod-2) if prime
    }
    mi& operator/=(int b) { return *this *= inv(mi(b,mod)); }
    
    friend mi operator+(mi a, const mi& b) { return a += b; }
    friend mi operator-(mi a, int b) { return a -= b; }
    friend mi operator-(const mi& a) { return mi(0,a.mod)-a; }
    friend mi operator*(mi a, int b) { return a *= b; }
    friend mi operator/(mi a, int b) { return a /= b; }
};

typedef pair<mi,mi> pmi;
typedef vector<mi> vmi;
typedef vector<pmi> vpmi;

vmi toVmi(vi v) { vmi V(sz(v)); F0R(i,sz(V)) V[i] = mi(v[i],MOD); return V; }
vi toVi(vmi V) { vi v(sz(V)); F0R(i,sz(v)) v[i] = V[i].val; return v; } 