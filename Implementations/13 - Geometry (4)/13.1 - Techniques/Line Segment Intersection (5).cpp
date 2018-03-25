/**
* Verification: Kattis segmentintersection
* If numbers are small enough, fractions are recommended.
*/

pi A,B,C,D;

pd operator*(int x, pd y) {
    return {x*y.f,x*y.s};
}

pd operator/(pd y, int x) {
    return {y.f/x,y.s/x};
}

pd operator+(pd l, pd r) {
    return {l.f+r.f,l.s+r.s};
}

int sgn(pi a, pi b, pi c) {
    return (b.s-a.s)*(c.f-a.f)-(b.f-a.f)*(c.s-a.s);
}

pd get(pi a, pi b, pi c, pi d) {
    return (abs(sgn(a,b,c))*d+abs(sgn(a,b,d))*c)
     /(abs(sgn(a,b,c))+abs(sgn(a,b,d)));
}

void solve() {
    cin >> A.f >> A.s >> B.f >> B.s >> C.f >> C.s >> D.f >> D.s;
    if (A > B) swap(A,B);
    if (C > D) swap(C,D);

    int a1 = sgn(A,B,C), a2 = sgn(A,B,D);
    if (a1 > a2) swap(a1,a2);
    if (!(a1 <= 0 && a2 >= 0)) {
        cout << "none\n";
        return;
    }
    if (a1 == 0 && a2 == 0) {
        if (sgn(A,C,D) != 0) {
            cout << "none\n";
            return;
        }
        pi x1 = max(A,C), x2 = min(B,D);
        if (x1 > x2) cout << "none\n";
        else if (x1 == x2) cout << (double)x1.f << " " << (double)x1.s << "\n";
        else cout << (double)x1.f << " " << (double)x1.s << " " << (double)x2.f << " " << (double)x2.s << "\n";
        return;
    }
    pd z = get(A,B,C,D);
    if (mp((double)A.f,(double)A.s) <= z && z <= mp((double)B.f,(double)B.s)) cout << z.f << " " << z.s << "\n";
    else cout << "none\n";
}