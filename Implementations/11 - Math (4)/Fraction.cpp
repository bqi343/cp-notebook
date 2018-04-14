/**
* Source: https://martin-thoma.com/fractions-in-cpp/
* Usage: TopCoder MinimizeAbsoluteDifferenceDiv1 
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
    
bool operator<(const Fraction& lhs, const Fraction& rhs) {
    return lhs.n*rhs.d < rhs.n*lhs.d;
}

bool operator==(const Fraction& lhs, const Fraction& rhs) {
    return lhs.n == rhs.n && lhs.d == rhs.d;
}

bool operator!=(const Fraction& lhs, const Fraction& rhs) { 
    return !(lhs == rhs); 
}

Fraction operator+(const Fraction& lhs, const Fraction& rhs) {
    return Fraction(lhs.n*rhs.d+rhs.n*lhs.d,lhs.d*rhs.d);
}

Fraction operator+=(Fraction& lhs, const Fraction& rhs) {
    return lhs = Fraction(lhs.n*rhs.d+rhs.n*lhs.d,lhs.d*rhs.d);
}

Fraction operator-(const Fraction& lhs, const Fraction& rhs) {
    return Fraction(lhs.n*rhs.d-rhs.n*lhs.d,lhs.d*rhs.d);
}

Fraction operator-=(Fraction& lhs, const Fraction& rhs) {
    return lhs = Fraction(lhs.n*rhs.d-rhs.n*lhs.d,lhs.d*rhs.d);
}

Fraction operator*(const Fraction& lhs, const Fraction& rhs) {
    return Fraction(lhs.n*rhs.n,lhs.d*rhs.d);
}

Fraction operator*=(Fraction& lhs, const Fraction& rhs) {
    return lhs = Fraction(lhs.n*rhs.n,lhs.d*rhs.d);
}

Fraction operator*(int lhs, const Fraction& rhs) {
    return Fraction(lhs*rhs.n,rhs.d);
}

Fraction operator*(const Fraction& rhs, int lhs) {
    return Fraction(lhs*rhs.n,rhs.d);
}

Fraction operator/(const Fraction& lhs, const Fraction& rhs) {
    return Fraction(lhs.n*rhs.d, lhs.d*rhs.n);
}

std::ostream& operator<<(std::ostream &strm, const Fraction &a) {
    if (a.d == 1) {
        strm << a.n;
    } else {
        strm << a.n << "/" << a.d;
    }
    return strm;
}
