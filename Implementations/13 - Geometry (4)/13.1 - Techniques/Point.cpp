/**
 * Description: Easy Geo
 * Source: http://codeforces.com/blog/entry/22175, KACTL
 * Verification: various
 */

namespace point {
    typedef pd P;
    typedef vector<P> vP;

    P dir(ld ang) {
        cd c = exp(ang*cd(0,1));
        return P(c.real(),c.imag());
    }
    
    ld norm(P x) { return x.f*x.f+x.s*x.s; }
    ld abs(P x) { return sqrt(norm(x)); }
    ld angle(P x) { return atan2(x.s,x.f); }
    P conj(P x) { return P(x.f,-x.s); }
    
    P operator+(const P& l, const P& r) { return P(l.f+r.f,l.s+r.s); }
    P operator-(const P& l, const P& r) { return P(l.f-r.f,l.s-r.s); }
    P operator*(const P& l, const ld& r) { return P(l.f*r,l.s*r); }
    P operator*(const ld& l, const P& r) { return r*l; }
    P operator/(const P& l, const ld& r) { return P(l.f/r,l.s/r); }
    P operator*(const P& l, const P& r) { return P(l.f*r.f-l.s*r.s,l.s*r.f+l.f*r.s); }
    P operator/(const P& l, const P& r) { return l*conj(r)/norm(r); }
    
    P& operator+=(P& l, const P& r) { return l = l+r; }
    P& operator-=(P& l, const P& r) { return l = l-r; }
    P& operator*=(P& l, const ld& r) { return l = l*r; }
    P& operator/=(P& l, const ld& r) { return l = l/r; }
    P& operator*=(P& l, const P& r) { return l = l*r; }
    P& operator/=(P& l, const P& r) { return l = l/r; }
    
    P unit(P x) { return x/abs(x); }
    
    ld dot(P a, P b) { return (conj(a)*b).f; }
    ld cross(P a, P b) { return (conj(a)*b).s; }
    ld cross(P p, P a, P b) { return cross(a-p,b-p); }
    ld dist(P p, P a, P b) { return std::abs(cross(p,a,b))/abs(a-b); }
    
    P rotate(P a, ld b) { return a*P(cos(b),sin(b)); }
    P reflect(P p, P a, P b) { return a+conj((p-a)/(b-a))*(b-a); }
    P foot(P p, P a, P b) { return (p+reflect(p,a,b))/(ld)2; }
    P extension(P a, P b, P c, P d) {
        ld x = cross(a,b,c), y = cross(a,b,d);
        return (d*x-c*y)/(x-y);
    }
    // computes the intersection of line segments AB, CD
    // verification: https://open.kattis.com/problems/segmentintersection
    vP segIntersect(P a, P b, P c, P d) {
        if (a > b) swap(a,b);
        if (c > d) swap(c,d);
    
        auto a1 = cross(a,b,c), a2 = cross(a,b,d);
        if (a1 > a2) swap(a1,a2);
        if (!(a1 <= 0 && a2 >= 0)) return {};
    
        if (a1 == 0 && a2 == 0) {
            if (cross(a,c,d) != 0) return {};
            auto x1 = max(a,c), x2 = min(b,d);
            if (x1 > x2) return {};
            if (x1 == x2) return {x1};
            return {x1,x2};
        }
        
        auto z = extension(a,b,c,d);
        if (a <= z && z <= b) return {z};
        return {};
    }
    
    // sorts points according to atan2
    // verification: ?
    template<class T> int half(pair<T,T> x) { return mp(x.s,x.f) > mp((T)0,(T)0); }
    bool cmp(P a, P b) { 
        int A = half(a), B = half(b);
        if (A != B) return A < B;
        return cross(a,b) > 0;
    }
    
    // computes the center of mass of a polygon with constant mass per unit area
    // verification: kattis polygonarea, VT HSPC 2018 Holiday Stars
    ld area(const vP& v) {
        ld area = 0;
        F0R(i,sz(v)) {
            int j = (i+1)%sz(v); ld a = cross(v[i],v[j]);
            area += a;
        }
        return std::abs(area)/2;
    }
    P centroid(const vP& v) { 
        P cen(0,0); ld area = 0; // 2*signed area
        F0R(i,sz(v)) {
            int j = (i+1)%sz(v); ld a = cross(v[i],v[j]);
            cen += a*(v[i]+v[j]); area += a;
        }
        return cen/area/(ld)3;
    }
    
    // tests whether a point is inside, on, or outside the perimeter of any polygon
    // verification: https://open.kattis.com/problems/pointinpolygon
    string inPoly(const vP& p, P z) {
        int n = sz(p), ans = 0;
        F0R(i,n) {
            P x = p[i], y = p[(i+1)%n];
            if (cross(x,y,z) == 0 && min(x,y) <= z && z <= max(x,y)) return "on";
            if (x.s > y.s) swap(x,y);
            if (x.s <= z.s && y.s > z.s && cross(z,x,y) > 0) ans ^= 1;
        }
        return ans ? "in" : "out";
    }
};

using namespace point;