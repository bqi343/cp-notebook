/**
* Description: misc operations with circles
* Source: Own
* Verification: https://codefights.com/tournaments/s8thqrnQL2YPK7XQt/L
*/

typedef pair<cd,ld> circle;

cd intersect(circle a, circle b, int x = 0) { 
    ld d = sqrt(norm(a.f-b.f));
    ld co = (a.s*a.s+d*d-b.s*b.s)/(2*a.s*d);
    ld theta = acos(co);
    
    cd tmp = (b.f-a.f)/d;
    if (x == 0) return a.f+tmp*a.s*polar((ld)1.0,theta);
    return a.f+tmp*a.s*polar((ld)1.0,-theta);
}

ld arc(circle x, cd a, cd b) {
    cd d = (a-x.f)/(b-x.f);
    return x.s*acos(d.real());
}

bool on (circle x, cd y) {
    return norm(y-x.f) == x.s*x.s;
}
