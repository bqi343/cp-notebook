/**
 * Description: Easy Geo
 * Source: http://codeforces.com/blog/entry/22175, KACTL
 * Verification: various
 */

// sorts points according to atan2
// verification: ?
template<class T> int half(pair<T,T> x) { return mp(x.s,x.f) > mp((T)0,(T)0); }
bool angleCmp(P a, P b) { 
    int A = half(a), B = half(b);
    return A == B ? cross(a,b) > 0 : A < B;
}

// computes the center of mass of a polygon with constant mass per unit area
// verification: kattis polygonarea, VT HSPC 2018 Holiday Stars
T area(const vP& v) {
    T area = 0;
    F0R(i,sz(v)) {
        int j = (i+1)%sz(v); T a = cross(v[i],v[j]);
        area += a;
    }
    return std::abs(area)/2;
}
P centroid(const vP& v) { 
    P cen(0,0); T area = 0; // 2*signed area
    F0R(i,sz(v)) {
        int j = (i+1)%sz(v); T a = cross(v[i],v[j]);
        cen += a*(v[i]+v[j]); area += a;
    }
    return cen/area/(T)3;
}

// tests whether a point is inside, on, or outside the perimeter of any polygon
// verification: https://open.kattis.com/problems/pointinpolygon
string inPoly(const vP& p, P z) {
    int n = sz(p), ans = 0;
    F0R(i,n) {
        P x = p[i], y = p[(i+1)%n];
        if (onSeg(z,x,y)) return "on";
        if (x.s > y.s) swap(x,y);
        if (x.s <= z.s && y.s > z.s && cross(z,x,y) > 0) ans ^= 1;
    }
    return ans ? "in" : "out";
}
