/**
* Verification: Kattis segmentintersection
* If numbers are small enough, fractions are recommended.
*/


ld sgn(cd a, cd b, cd c) {
    b -= a, c -= a;
    return (conj(b)*c).imag();
}

cd get(cd a, cd b, cd c, cd d) {
    return (abs(sgn(a,b,c))*d+abs(sgn(a,b,d))*c)
     /(abs(sgn(a,b,c))+abs(sgn(a,b,d)));
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

vector<cd> solve(cd A, cd B, cd C, cd D) {
    if (A > B) swap(A,B);
    if (C > D) swap(C,D);

    ld a1 = sgn(A,B,C), a2 = sgn(A,B,D);
    if (a1 > a2) swap(a1,a2);
    if (!(a1 <= 0 && a2 >= 0)) return {};

    if (a1 == 0 && a2 == 0) {
        if (sgn(A,C,D) != 0) return {};
        cd x1 = max(A,C), x2 = min(B,D);
        if (x1 > x2) return {};
        if (x1 == x2) return {x1};
        return {x1,x2};
    }
    
    cd z = get(A,B,C,D);
    if (A <= z && z <= B) return {z};
    return {};
}