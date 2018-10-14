/**
* Description: Operations with fractions
* Source: https://martin-thoma.com/fractions-in-cpp/
* Verification: TopCoder MinimizeAbsoluteDifferenceDiv1 
*/

namespace frac {
    struct frac {
        ll n,d;
        frac() { n = 0, d = 1; }
        frac(ll _n, ll _d) {
            n = _n, d = _d;
            ll g = __gcd(n,d);
            n /= g, d /= g;
            if (d < 0) n *= -1, d *= -1;
        }
    };

    frac abs(frac F) { return frac(abs(F.n),F.d); }
        
    bool operator<(const frac& l, const frac& r) { return l.n*r.d < r.n*l.d; }
    bool operator==(const frac& l, const frac& r) { return l.n == r.n && l.d == r.d; }
    bool operator!=(const frac& l, const frac& r) { return !(l == r); }

    frac operator+(const frac& l, const frac& r) { return frac(l.n*r.d+r.n*l.d,l.d*r.d); }
    frac operator-(const frac& l, const frac& r) { return frac(l.n*r.d-r.n*l.d,l.d*r.d); }
    frac operator*(const frac& l, const frac& r) { return frac(l.n*r.n,l.d*r.d); }
    frac operator*(const frac& l, int r) { return l*frac(r,1); }
    frac operator*(int r, const frac& l) { return l*r; }
    frac operator/(const frac& l, const frac& r) { return l*frac(r.d,r.n); }
    frac operator/(const frac& l, const int& r) { return l/frac(r,1); }
    frac operator/(const int& l, const frac& r) { return frac(l,1)/r; }

    frac operator+=(frac& l, const frac& r) { return l = l+r; }
    frac operator-=(frac& l, const frac& r) { return l = l-r; }
    template<class T> frac operator*=(frac& l, const T& r) { return l = l*r; }
    template<class T> frac operator/=(frac& l, const T& r) { return l = l/r; }

    ostream& operator<<(ostream &strm, const frac &a) {
        strm << a.n;
        if (a.d != 1) strm << "/" << a.d;
        return strm;
    }
}

using namespace frac;