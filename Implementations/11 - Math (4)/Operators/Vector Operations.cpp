/**
* Description: modular arithmetic with vectors
    * use for NTT
* Source: Own
* Verification: ?
*/

using namespace modOp; 

namespace vecOp {
    template<class T> T operator+=(T& l, const T& r) { return l = l+r; }
    template<class T> T operator-=(T& l, const T& r) { return l = l-r; }
    template<class T> T operator*=(T& l, const T& r) { return l = l*r; }

    vi rev(vi v) { reverse(all(v)); return v; }
    vi operator+(const vi& l, const vi& r) {
        vi res(max(sz(l),sz(r)));
        F0R(i,sz(l)) res[i] = l[i];
        F0R(i,sz(r)) AD(res[i],r[i]);
        return res;
    }
    vi operator-(const vi& l, const vi& r) {
        vi res(max(sz(l),sz(r)));
        F0R(i,sz(l)) res[i] = l[i];
        F0R(i,sz(r)) SUB(res[i],r[i]);
        return res;
    }
    vi operator*(const vi& l, const vi& r) {
        if (min(sz(l),sz(r)) == 0) return {};
        vi x(sz(l)+sz(r)-1);
        F0R(i,sz(l)) F0R(j,sz(r)) AD(x[i+j],mul(l[i],r[j]));
        return x;
    }
    vi operator*(const vi& l, const int& r) {
        int R = (r%MOD+MOD)%MOD;
        vi L = l; 
        for (int& i: L) MUL(i,R); 
        return L;
    }
    vi operator*(const int& l, const vi& r) { return r*l; }
    vi operator*=(vi& l, const int& r) { return l = l*r; }
    
    vi rem(vi a, vi b) { 
        while (sz(b) && b.back() == 0) b.pop_back();
        assert(sz(b)); b *= inv(b.back());
        while (sz(a) >= sz(b)) {
            int k = a.back();
            F0R(i,sz(b)) SUB(a[sz(a)-sz(b)+i],mul(k,b[i]));
            while (sz(a) && a.back() == 0) a.pop_back();
        }
        return a;
    }
        
    vi interpolate(vpi v) {
        vi ret;
        F0R(i,sz(v)) {
            vi prod = {1};
            int todiv = 1;
            F0R(j,sz(v)) if (i != j) {
                MUL(todiv,sub(v[i].f,v[j].f));
                vi tmp = {sub(0,v[j].f),1};
                prod *= tmp;
            }
            ret += prod*mul(inv(todiv),v[i].s);
        }
        return ret;
    }
}

using namespace vecOp;