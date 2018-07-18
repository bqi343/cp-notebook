/**
* Source: https://martin-thoma.com/fractions-in-cpp/
* Verification: TopCoder MinimizeAbsoluteDifferenceDiv1 
*/

struct Fraction {
    ll n,d;
    Fraction() { n = 0, d = 1; }
    Fraction(ll _n, ll _d) {
        n = _n, d = _d;
        ll g = __gcd(n,d);
        n /= g, d /= g;
        if (d < 0) n *= -1, d *= -1;
    }
};

Fraction abs(Fraction F) { return Fraction(abs(F.n),F.d); }
    
bool operator<(const Fraction& l, const Fraction& r) { return l.n*r.d < r.n*l.d; }
bool operator==(const Fraction& l, const Fraction& r) { return l.n == r.n && l.d == r.d; }
bool operator!=(const Fraction& l, const Fraction& r) { return !(l == r); }

Fraction operator+(const Fraction& l, const Fraction& r) { return Fraction(l.n*r.d+r.n*l.d,l.d*r.d); }
Fraction operator-(const Fraction& l, const Fraction& r) { return Fraction(l.n*r.d-r.n*l.d,l.d*r.d); }
Fraction operator*(const Fraction& l, const Fraction& r) { return Fraction(l.n*r.n,l.d*r.d); }
Fraction operator*(const Fraction& l, int r) { return l*Fraction(r,1); }
Fraction operator*(int r, const Fraction& l) { return l*r; }
Fraction operator/(const Fraction& l, const Fraction& r) { return l*Fraction(r.d,r.n); }
Fraction operator/(const Fraction& l, const int& r) { return l/Fraction(r,1); }
Fraction operator/(const int& l, const Fraction& r) { return Fraction(l,1)/r; }

Fraction operator+=(Fraction& l, const Fraction& r) { return l = l+r; }
Fraction operator-=(Fraction& l, const Fraction& r) { return l = l-r; }
template<class T> Fraction operator*=(Fraction& l, const T& r) { return l = l*r; }
template<class T> Fraction operator/=(Fraction& l, const T& r) { return l = l/r; }

std::ostream& operator<<(std::ostream &strm, const Fraction &a) {
    strm << a.n;
    if (a.d != 1) strm << "/" << a.d;
    return strm;
}