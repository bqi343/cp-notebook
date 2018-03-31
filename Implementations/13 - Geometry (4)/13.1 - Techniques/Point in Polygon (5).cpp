/**
* Source: own
* Usage: https://open.kattis.com/problems/pointinpolygon
*/

int n,m;
pi p[1000];

int area(pi x, pi y, pi z) {
    return (y.f-x.f)*(z.s-x.s)-(y.s-x.s)*(z.f-x.f);
}

bool on(pi x, pi y, pi z) {
    if (area(x,y,z) != 0) return 0;
    return min(x,y) <= z && z <= max(x,y);
}

double get(pi x, pi y, int z) {
    return double((z-x.s)*y.f+(y.s-z)*x.f)/(y.s-x.s);
}

void test(pi z) {
    int ans = 0;
    F0R(i,n) {
        pi x = p[i], y = p[(i+1)%n];
        if (on(x,y,z)) {
            cout << "on\n";
            return;
        }
        if (x.s > y.s) swap(x,y);
        if (x.s <= z.s && y.s > z.s) {
            double t = get(x,y,z.s);
            if (t > z.f) ans++;
        }
    }
    if (ans % 2 == 1) cout << "in\n";
    else cout << "out\n";
}

void solve() {
    F0R(i,n) cin >> p[i].f >> p[i].s;
    cin >> m;
    F0R(i,m) {
        pi z; cin >> z.f >> z.s;
        test(z);
    }
}
