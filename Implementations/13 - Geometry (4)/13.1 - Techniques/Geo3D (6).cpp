/**
* Description: Basic 3D Geometry
* Source: Own
* Verification: AMPPZ 2011 Cross Spider
*/

namespace Geo3d {
    vl operator-(vl a, vl b) {
        vl c(sz(a)); F0R(i,sz(a)) c[i] = a[i]-b[i];
        return c;
    }

    bool ismult(vl b, vl c) {
        if ((ld)b[0]*c[1] != (ld)b[1]*c[0]) return 0;
        if ((ld)b[0]*c[2] != (ld)b[2]*c[0]) return 0;
        if ((ld)b[2]*c[1] != (ld)b[1]*c[2]) return 0;
        return 1;
    }

    bool collinear(vl a, vl b, vl c) {
        b = b-a, c = c-a;
        return ismult(b,c);
    }

    vl cross(vl a, vl b) {
        return {a[1]*b[2]-a[2]*b[1], 
                a[2]*b[0]-a[0]*b[2],
                a[0]*b[1]-a[1]*b[0]};
    }

    bool coplanar(vl a, vl b, vl c, vl d) {
        b = b-a, c = c-a, d = d-a;
        return ismult(cross(b,c),cross(b,d));
    }
}

using namespace Geo3d;