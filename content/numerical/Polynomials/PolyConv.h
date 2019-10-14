/**
 * Description: multiply two polynomials directly if small, otherwise use FFT
 * Source: KACTL, https://cp-algorithms.com/algebra/fft.html
 * Dependency: FFT
 */

using namespace VecOp;

namespace PolyConv {
    template<class T> bool small(const vector<T>& a, const vector<T>& b) { 
        return (ll)sz(a)*sz(b) <= 500000; // for small vectors, multiply directly
    } 
    vmi smart(const vmi& a, const vmi& b) { return mult(a,b); }
    vcd smart(const vcd& a, const vcd& b) { return mult(a,b); }
    vl smart(const vl& a, const vl& b) {
        auto X = smart(vcd(all(a)),vcd(all(b)));
        vl x(sz(X)); F0R(i,sz(X)) x[i] = round(X[i].real());
        return x;
    }
    template<class T> vector<T> conv(const vector<T>& a, const vector<T>& b) {
        if (small(a,b)) return a*b;
        return smart(a,b);
    } 
}

using namespace PolyConv;