/**
 * Description: Easy Geo
 * Source: http://codeforces.com/blog/entry/22175, KACTL
 * Verification: various
 */

typedef ld T;

namespace Point {
    typedef pair<T,T> P;
    typedef vector<P> vP;

    P dir(T ang) {
        cd c = exp(ang*complex<T>(0,1));
        return P(c.real(),c.imag());
    }
    
    T norm(P x) { return x.f*x.f+x.s*x.s; }
    T abs(P x) { return sqrt(norm(x)); }
    T angle(P x) { return atan2(x.s,x.f); }
    P conj(P x) { return P(x.f,-x.s); }
    
    P operator+(const P& l, const P& r) { return P(l.f+r.f,l.s+r.s); }
    P operator-(const P& l, const P& r) { return P(l.f-r.f,l.s-r.s); }
    P operator*(const P& l, const T& r) { return P(l.f*r,l.s*r); }
    P operator*(const T& l, const P& r) { return r*l; }
    P operator/(const P& l, const T& r) { return P(l.f/r,l.s/r); }
    P operator*(const P& l, const P& r) { return P(l.f*r.f-l.s*r.s,l.s*r.f+l.f*r.s); }
    P operator/(const P& l, const P& r) { return l*conj(r)/norm(r); }
    
    P& operator+=(P& l, const P& r) { return l = l+r; }
    P& operator-=(P& l, const P& r) { return l = l-r; }
    P& operator*=(P& l, const T& r) { return l = l*r; }
    P& operator/=(P& l, const T& r) { return l = l/r; }
    P& operator*=(P& l, const P& r) { return l = l*r; }
    P& operator/=(P& l, const P& r) { return l = l/r; }
    
    P unit(P x) { return x/abs(x); }
    T dot(P a, P b) { return (conj(a)*b).f; }
    T cross(P a, P b) { return (conj(a)*b).s; }
    T cross(P p, P a, P b) { return cross(a-p,b-p); }
    T dist(P p, P a, P b) { return std::abs(cross(p,a,b))/abs(a-b); }
    
    P rotate(P a, T b) { return a*P(cos(b),sin(b)); }
    P reflect(P p, P a, P b) { return a+conj((p-a)/(b-a))*(b-a); }
    P foot(P p, P a, P b) { return (p+reflect(p,a,b))/(T)2; }
    P extension(P a, P b, P c, P d) {
        T x = cross(a,b,c), y = cross(a,b,d);
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
            if (cross(x,y,z) == 0 && min(x,y) <= z && z <= max(x,y)) return "on";
            if (x.s > y.s) swap(x,y);
            if (x.s <= z.s && y.s > z.s && cross(z,x,y) > 0) ans ^= 1;
        }
        return ans ? "in" : "out";
    }

    pair<P,double> ccCenter(P a, P b, P c) { // circumcenter
        b -= a; c -= a;
        P res = b*c*(conj(c)-conj(b))/(b*conj(c)-conj(b)*c);
        return {a+res,abs(res)};
    }
     
    pair<P, double> mec(vP ps) { // minimum enclosing circle, ex. USACO Camp 2019 Contest 2 #4
        shuffle(all(ps), mt19937(time(0)));
        P o = ps[0]; double r = 0, EPS = 1 + 1e-8;
        F0R(i,sz(ps)) if (abs(o-ps[i]) > r*EPS) {
            o = ps[i], r = 0;
            F0R(j,i) if (abs(o-ps[j]) > r*EPS) {
                o = (ps[i]+ps[j])/2, r = abs(o-ps[i]);
                F0R(k,j) if (abs(o-ps[k]) > r*EPS) 
                    tie(o,r) = ccCenter(ps[i],ps[j],ps[k]);
            }
        }
        return {o,r};
    }
};

using namespace Point;