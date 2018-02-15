/**
* Description: FWHT, similar to FFT
* Source: CSA - FFT And Variations
* Verification: https://www.hackerrank.com/challenges/xor-subsequence/problem
*/

typedef vector<double> vd;
typedef vector<ll> vl;

int get(int s) {
    return s > 1 ? 32 - __builtin_clz(s - 1) : 0;
}

namespace FWHT {
    vd fwht(vd P) {
        for (int len = 1; 2 * len <= sz(P); len <<= 1) {
            for (int i = 0; i < sz(P); i += 2 * len) {
                for (int j = 0; j < len; j++) {
                    double u = P[i + j];
                    double v = P[i + len + j];
                    P[i + j] = u+v;
                    P[i + len + j] = u-v;
                }
            }
        }
    
        return P;
    }

    
    vd fwht_rev(vd& a) {
        vd res = fwht(a);
        F0R(i,sz(res)) res[i] /= a.size();
        return res;
    }
    
    vd conv(vd a, vd b) {
        int s = max(sz(a),sz(b)), L = get(s), n = 1<<L;
        if (s <= 0) return {};
        
        a.resize(n); a = fwht(a);
        b.resize(n); b = fwht(b);
        
        F0R(i,n) a[i] = a[i]*b[i];
        a = fwht_rev(a);
        return a;
    }
    
    vl conv(vl a, vl b) {
        vd A; for (ll x: a) A.pb(x);
        vd B; for (ll x: b) B.pb(x);
        vd c = conv(A,B);
        vl C; for (double x: c) C.pb(round(x));
        return C;
    }
}