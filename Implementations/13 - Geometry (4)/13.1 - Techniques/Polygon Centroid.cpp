/**
* Description: computes the center of mass of a polygon with constant mass per unit area
* Source: https://stackoverflow.com/questions/2792443/finding-the-centroid-of-a-polygon
* Verification: https://open.kattis.com/problems/polygonarea, VT HSPC 2018 Holiday Stars
*/ 

cd centroid(vcd v) {
    cd cen(0,0); ld area = 0;
    F0R(i,sz(v)) {
        int j = (i+1)%sz(v);
        ld a = (v[j]*conj(v[i])).imag();
        cen += a*(v[i]+v[j]); area += a;
    }
    area /= (ld)2; // positive if ccw
    return cen/area/(ld)6;
}
