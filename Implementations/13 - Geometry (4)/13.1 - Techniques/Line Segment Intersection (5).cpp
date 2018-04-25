/**
* Verification: Kattis segmentintersection
* If numbers are small enough, fractions are recommended.
*/

namespace intersect {
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

    ld cross(cd b, cd c) { return (conj(b)*c).imag(); }
    ld cross(cd a, cd b, cd c) { return cross(b-a,c-a); }

    cd line(cd a, cd b, cd c, cd d) {
        return (cross(a,b,c)*d-cross(a,b,d)*c)
         /(cross(a,b,c)-cross(a,b,d));
    }

    vcd segment(cd A, cd B, cd C, cd D) {
        if (A > B) swap(A,B);
        if (C > D) swap(C,D);

        ld a1 = cross(A,B,C), a2 = cross(A,B,D);
        if (a1 > a2) swap(a1,a2);
        if (!(a1 <= 0 && a2 >= 0)) return {};

        if (a1 == 0 && a2 == 0) {
            if (cross(A,C,D) != 0) return {};
            cd x1 = max(A,C), x2 = min(B,D);
            if (x1 > x2) return {};
            if (x1 == x2) return {x1};
            return {x1,x2};
        }
        
        cd z = line(A,B,C,D);
        if (A <= z && z <= B) return {z};
        return {};
    }
};