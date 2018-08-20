/**
* Description: modular arithmetic with vectors
    * use for NTT
*/

namespace VecOp {
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
        vi L = l;
        for (int& i: L) MUL(i,r);
        return L;
    }
    template<class T> T operator+=(T& l, const T& r) { return l = l+r; }
    template<class T> T operator-=(T& l, const T& r) { return l = l-r; }
    template<class T> T operator*=(T& l, const T& r) { return l = l*r; }
    
    vi rem(vi a, vi b) {
        while (sz(a) >= sz(b)) {
            vi v(sz(a)-sz(b));  v.pb(a.back());
            a -= b*v;
            while (sz(a) && a.back() == 0) a.pop_back();
        }
        return a;
    }
    
    std::ostream& operator<<(std::ostream &strm, const vi& a) {
        cout << "{";
        F0R(i,sz(a)) {
            if (i) cout << ", ";
            cout << a[i];
        }
        cout << "}\n";
        return strm;
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