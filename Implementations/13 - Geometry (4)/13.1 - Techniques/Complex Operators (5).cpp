ld sgn(cd a, cd b, cd c) {
    b -= a, c -= a;
    return (conj(b)*c).imag();
}

bool operator<(const cd& a, const cd& b) {
    if (a.real() != b.real()) return a.real() < b.real();
    return a.imag() < b.imag();
}

bool operator>(const cd& a, const cd& b) {
    if (a.real() != b.real()) return a.real() > b.real();
    return a.imag() > b.imag();
}

bool operator<=(const cd& a, const cd& b) { return a < b || a == b; }
bool operator>=(const cd& a, const cd& b) { return a > b || a == b; }
cd max(const cd& a, const cd& b) { return a>b?a:b; }
cd min(const cd& a, const cd& b) { return a<b?a:b; }