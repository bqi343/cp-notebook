/**
 * Description: operations with modular arithmetic
 * Source: https://codeforces.com/blog/entry/63903
 * Verification: see Combo
 */

int invGeneral(int a, int b) {
    a %= b; if (a == 0) return b == 1 ? 0 : -1;
    int x = invGeneral(b,a); return x == -1 ? -1 : ((1-(ll)b*x)/a+b)%b;
}

struct mi {
    int val;
    int mod = 0;
    // static const int mod = MOD;

    void normalize() {
        if (mod == 0) return;
        val %= mod; if (val < 0) val += mod;
    }
    mi(int v = 0, int m = 0) : val(v), mod(m) { normalize(); }
    // mi(int v = 0, int m = 0) : val(v) { normalize(); }

    explicit operator int() const { return val; }
    friend ostream& operator<<(ostream& os, const mi& a) { return os << a.val; }
    friend bool operator==(const mi& a, const mi& b) { return a.val == b.val; }
    friend bool operator!=(const mi& a, const mi& b) { return !(a == b); }

    void check(mi& b) { // make sure all operations are valid
        // comment out if mod is static const
        mi& a = *this;
        if (a.mod > 0 && b.mod > 0) { assert(a.mod == b.mod); return; }
        int mod = max(a.mod,b.mod); if (mod == 0) mod = MOD;
        if (a.mod != mod) { a.mod = mod; a.normalize(); }
        if (b.mod != mod) { b.mod = mod; b.normalize(); }
    }
    mi& operator+=(mi b) { check(b); val += int(b); if (val >= mod) val -= mod; return *this; }
    mi& operator-=(mi b) { check(b); val -= int(b); if (val < 0) val += mod; return *this; }
    mi& operator*=(mi b) { check(b); val = (ll)val*int(b)%mod; return *this; }
    friend mi operator+(mi a, const mi& b) { return a += b; }
    friend mi operator-(mi a, const mi& b) { return a -= b; }
    friend mi operator-(const mi& a) { return mi(0)-a; }
    friend mi operator*(mi a, const mi& b) { return a *= b; }
    friend mi exp(mi b, ll p) {
        mi ans = mi(1,b.mod);
        for (; p; p /= 2, b *= b) if (p&1) ans *= b;
        return ans;
    }

    friend mi inv(const mi& b) {
        return {invGeneral(b.val,b.mod),b.mod};
        // return exp(b,b.mod-2) if prime
    }
    mi& operator/=(mi b) { check(b); return *this *= inv(b); }
    friend mi operator/(mi a, const mi& b) { return a /= b; }
};

typedef pair<mi,mi> pmi;
typedef vector<mi> vmi;
typedef vector<pmi> vpmi;
vmi toVmi(vi v) { vmi V(sz(v)); F0R(i,sz(V)) V[i] = v[i]; return V; }
vi toVi(vmi V) { vi v(sz(V)); F0R(i,sz(v)) v[i] = int(V[i]); return v; }
