// https://open.kattis.com/problems/segmentdistance

pii A,B,C,D;

pii operator-(pii l, pii r) {
    return {l.f-r.f,l.s-r.s};
}

double dist(pii a, pii b) {
    a = a-b;
    return sqrt(a.f*a.f+a.s*a.s);
}

double area(pii a, pii b, pii c) {
    b = b-a, c = c-a;
    return double(b.s*c.f-b.f*c.s)/2;
}

bool obtuse(pii a, pii b, pii c) {
    a = a-b, c = c-b;
    return a.f*c.f+a.s*c.s < 0;
}

double get(pii a, pii b, pii c) {
    if (b == c) return dist(a,b);
    if (obtuse(a,b,c)) return dist(a,b);
    if (obtuse(a,c,b)) return dist(a,c);
    return abs(2*area(a,b,c))/dist(b,c);
}

bool inter(pii A, pii B, pii C, pii D) {
    if (area(A,B,C)*area(A,B,D) > 0) return 0;
    if (area(C,D,A)*area(C,D,B) > 0) return 0;
    if (max(A,B) < min(C,D) || max(C,D)<min(A,B)) return 0;
    return 1;
}

double solve() {
    cin >> A.f >> A.s >> B.f >> B.s >> C.f >> C.s >> D.f >> D.s;
    if (A == B) return get(A,C,D);
    if (C == D) return get(C,A,B);
    
    if (inter(A,B,C,D)) return 0;
    return min(min(get(A,C,D),get(B,C,D)),min(get(C,A,B),get(D,A,B)));
}

int main() {
    ios_base::sync_with_stdio(0);cin.tie(0);
    int n; cin >> n;
    cout << fixed << setprecision(2);
    F0R(i,n) cout << solve() << "\n";
}

// read!
// ll vs. int!
