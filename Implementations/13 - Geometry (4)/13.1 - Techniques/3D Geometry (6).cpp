/**
 * Description: Basic 3D Geometry
 * Source: Own
 * Verification: AMPPZ 2011 Cross Spider
 */

typedef vl P;

namespace point3 {
    ld norm(P x) { 
        ld sum = 0; F0R(i,sz(x)) sum += (ld)x[i]*x[i];
        return sum;
    }
    ld abs(P x) { return sqrt(norm(x)); }

    P operator+(const P& a, const P& b) {
        P c(sz(a)); F0R(i,sz(a)) c[i] = a[i]+b[i];
        return c;
    }
    P operator+=(P& l, const P& r) { return l = l+r; }
    P operator-(const P& a, const P& b) {
        P c(sz(a)); F0R(i,sz(a)) c[i] = a[i]-b[i];
        return c;
    }
    P operator-=(P& l, const P& r) { return l = l-r; }
    
    ld dot(P a, P b) { 
        ld sum = 0; F0R(i,sz(a)) sum += a[i]*b[i];
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