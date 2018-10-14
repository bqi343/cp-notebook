/**
* Description: Shoelace Formula
* Source: Own
* Verification: https://open.kattis.com/problems/polygonarea
*/ 

ld area(vector<cd> v) {
    ld x = 0;
    F0R(i,sz(v)) {
        int j = (i+1)%sz(v);
        x += (ld)v[i].real()*v[j].imag();
        x -= (ld)v[j].real()*v[i].imag();
    }
    return abs(x)/2;
}
