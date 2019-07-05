/**
 * Description: Basic 3D Geometry
 * Source: Own
 * Verification: 
    * AMPPZ 2011 Cross Spider
    * https://atcoder.jp/contests/JAG2013Spring/tasks/icpc2013spring_h
 */

namespace point3 {
    typedef double T;
    typedef array<T,3> P;
    
    T norm(P x) { 
        T sum = 0; F0R(i,sz(x)) sum += (ld)x[i]*x[i];
        return sum;
    }
    T abs(P x) { return sqrt(norm(x)); }
    
    P operator+(const P& l, const P& r) {
        P c; F0R(i,sz(l)) c[i] = l[i]+r[i];
        return c;
    }
    P operator-(const P& l, const P& r) {
        P c; F0R(i,sz(l)) c[i] = l[i]-r[i];
        return c;
    }
    P operator*(const P& l, const T& r) { 
        P c; F0R(i,sz(l)) c[i] = l[i]*r;
        return c;
    }
    P operator*(const T& l, const P& r) { return r*l; }
    P operator/(const P& l, const T& r) { 
        P c; F0R(i,sz(l)) c[i] = l[i]/r;
        return c; 
    }
    
    P& operator+=(P& l, const P& r) { return l = l+r; }
    P& operator-=(P& l, const P& r) { return l = l-r; }
    P& operator*=(P& l, const ld& r) { return l = l*r; }
    P& operator/=(P& l, const ld& r) { return l = l/r; }
    
    T dot(P a, P b) { 
        T sum = 0; F0R(i,sz(a)) sum += a[i]*b[i];
        return sum;
    }
    P cross(P a, P b) {
        return {a[1]*b[2]-a[2]*b[1],
                a[2]*b[0]-a[0]*b[2],
                a[0]*b[1]-a[1]*b[0]};
    }
    
    bool isMult(P a, P b) {
        auto c = cross(a,b); 
        F0R(i,sz(c)) if (c[i] != 0) return 0; 
        return 1;
    }
    bool collinear(P a, P b, P c) { return isMult(b-a,c-a); }
    bool coplanar(P a, P b, P c, P d) { 
        return isMult(cross(b-a,c-a),cross(b-a,d-a)); 
    }
}

using namespace point3;