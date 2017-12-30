/**
* Description: Shoelace Formula
* Usage: https://open.kattis.com/problems/polygonarea
*/ 

double area(vector<pii> v) {
    double x = 0;
    F0R(i,sz(v)) {
        int j = (i+1)%sz(v);
        x += (ll)v[i].f*v[j].s;
        x -= (ll)v[j].f*v[i].s;
    }
    return abs(x)/2;
}
