/**
* Description: Easy Geo
* Source: http://codeforces.com/blog/entry/22175
* Verification: ?
*/

namespace ComplexOp {
    template<class T> istream& operator>> (istream& is, complex<T>& p) {
        T value;
        is >> value; p.real(value);
        is >> value; p.imag(value);
        return is;
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

    ld cross(cd a, cd b) { return (conj(a)*b).imag(); }
    ld area(cd a, cd b, cd c) { return cross(b-a,c-a); }
    ld dot(cd a, cd b) { return (conj(a)*b).real(); }

    cd reflect(cd p, cd a, cd b) { return a+conj((p-a)/(b-a))*(b-a); }
    cd proj(cd p, cd a, cd b) { return (p+reflect(p,a,b))/(ld)2; }

    cd line(cd a, cd b, cd c, cd d) {
        ld x = area(a,b,c), y = area(a,b,d);
        return (x*d-y*c)/(x-y);
    }

    vcd segment(cd A, cd B, cd C, cd D) { // kattis segmentintersection
        if (A > B) swap(A,B);
        if (C > D) swap(C,D);

        ld a1 = area(A,B,C), a2 = area(A,B,D);
        if (a1 > a2) swap(a1,a2);
        if (!(a1 <= 0 && a2 >= 0)) return {};

        if (a1 == 0 && a2 == 0) {
            if (area(A,C,D) != 0) return {};
            cd x1 = max(A,C), x2 = min(B,D);
            if (x1 > x2) return {};
            if (x1 == x2) return {x1};
            return {x1,x2};
        }
        
        cd z = line(A,B,C,D);
        if (A <= z && z <= B) return {z};
        return {};
    }
}