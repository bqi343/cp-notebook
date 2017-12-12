// https://open.kattis.com/problems/polygonarea

int n;

double area(vector<pii> v) {
    double x = 0;
    F0R(i,v.size()) {
        x += v[i].f*v[(i+1)%v.size()].s;
        x -= v[(i+1)%v.size()].f*v[i].s;
    }
    return x/2;
}

int main() {
    ios_base::sync_with_stdio(0);cin.tie(0);
    cout << fixed << setprecision(1);
    while (cin >> n) {
        if (n == 0) return 0;
        vector<pii> v(n); F0R(i,n) cin >> v[i].f >> v[i].s;
        double tmp = area(v);
        if (tmp < 0) cout << "CW ";
        else cout << "CCW ";
        cout << abs(tmp) << "\n";
    }
}