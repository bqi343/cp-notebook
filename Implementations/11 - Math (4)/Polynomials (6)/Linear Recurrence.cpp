/**
 * Description: Berlekamp-Massey Algo
    * Note: you may need to add a lot of terms to get the correct formula
 * Source: http://codeforces.com/blog/entry/61306
 * Verification: http://codeforces.com/contest/506/problem/E
 */

using namespace vecOp;

struct linRec {
    vector<vmi> seq;
    vmi x, delta, des;
    vi fail;

    void init(vmi _x) {
        x = _x; seq.pb({}); int best = 0;

        F0R(i,sz(x)) {
            delta.pb(-x[i]);
            F0R(j,sz(seq.back())) delta[i] += x[i-j-1]*seq.back()[j];
            if (delta[i] == 0) continue;

            fail.pb(i); if (sz(seq) == 1) { seq.pb(vmi(i+1)); continue; }

            auto k = -delta[i]/delta[fail[best]];
            vmi cur(i-fail[best]-1); cur.pb(-k);
            trav(a, seq[best]) cur.pb(a*k);

            cur += seq.back();
            if (i-fail[best]+sz(seq[best]) >= sz(seq.back())) best = sz(seq)-1;
                // take fail vector with smallest size

            seq.pb(cur);
        }

        F0Rd(i,sz(seq.back())) des.pb(-seq.back()[i]);
        des.pb(1);
    }

    vmi getPo(int n) {
        if (n == 0) return {1};
        vmi x = getPo(n/2); x = rem(x*x,des);
        if (n&1) {
            vmi v = {0,1};
            x = rem(x*v,des);
        }
        return x;
    }

    int get(int n) {
        vmi t = getPo(n);
        mi ANS = 0; F0R(i,sz(t)) ANS += t[i]*x[i];
        return (int)ANS;
    }
};
