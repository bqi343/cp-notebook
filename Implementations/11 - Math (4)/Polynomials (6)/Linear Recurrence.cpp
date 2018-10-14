/**
* Description: Berlekamp-Massey Algo
* Source: http://codeforces.com/blog/entry/61306
* Verification: http://codeforces.com/contest/506/problem/E
*/

using namespace VecOp;

struct linRec {
    vector<vi> seq;
    vi x, fail, delta, des;
    
    linRec (vi _x) {
        x = _x; seq.pb({}); int best = 0;
        
        F0R(i,sz(x)) {
            delta.pb(mul(-1,x[i]));
            F0R(j,sz(seq.back())) AD(delta[i],mul(x[i-j-1],seq.back()[j]));
            if (delta[i] == 0) continue;
            
            fail.pb(i); if (sz(seq) == 1) { seq.pb(vi(i+1)); continue; }
            
            int k = mul(mul(-1,delta[i]),inv(delta[fail[best]]));
            vi cur(i-fail[best]-1); cur.pb(mul(-1,k)); 
            for (auto a: seq[best]) cur.pb(mul(a,k));
            
            cur += seq.back();
            if (i-fail[best]+sz(seq[best]) >= sz(seq.back())) best = sz(seq)-1; 
                // take fail vector with smallest size
            
            seq.pb(cur);
        }
        
        F0Rd(i,sz(seq.back())) des.pb(mul(-1,seq.back()[i]));
        des.pb(1);
    }
    
    vi getPo(int n) {
        if (n == 0) return {1};
        vi x = getPo(n/2); x = rem(x*x,des);
        if (n&1) {
            vi v = {0,1};
            x = rem(x*v,des);
        }
        return x;
    }
    
    int get(int n) {
        vi t = getPo(n);
        int ANS = 0;
        F0R(i,sz(t)) AD(ANS,mul(t[i],x[i]));
        return ANS;
    }
};