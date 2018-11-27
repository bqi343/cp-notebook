/**
* Description: Evaluate degree n polynomial at n points in O(nlog^2n) time
* Source: CF, http://people.csail.mit.edu/madhu/ST12/scribe/lect06.pdf
* Verification: https://codeforces.com/contest/438/problem/E
*/

using namespace vecOp;
using namespace NTT;

namespace NTTextend { 
    vi inv(vi v, int p) { // compute inverse of v mod x^p, where v[0] = 1 
        v.resize(p); if (p == 1) return {1};
        assert(v[0] == 1);
        if (p&1) { // naive
            int cur = 0; auto V = inv(v,p-1);
            F0R(i,p-1) if (p-1-i < sz(v)) SUB(cur,mul(V[i],v[p-1-i]));
            V.pb(cur); return V;
        }
        vi a = inv(v,p/2);
        vi h0 = vi(v.begin(),v.begin()+p/2);
        vi h1 = vi(v.begin()+p/2,v.end());
        vi c = conv(a,h0); c = vi(c.begin()+p/2,c.end()); 
        assert(c[0] == 1);
        
        vi b = conv(-1*a,conv(h1,a)+c); b.resz(p/2); 
        a.insert(a.end(),all(b)); return a;
    }
    
    pair<vi,vi> divi(vi f, vi g) { // f = q*g+r
        if (sz(f) < sz(g)) return {{},f};
        vi q = conv(inv(rev(g),sz(f)-sz(g)+1),rev(f));
        q.resz(sz(f)-sz(g)+1); q = rev(q);
        vi r = f-conv(q,g); r.resize(sz(g)-1);
        return {q,r};
    }
    
    vi sqrt(vi v, int p) { // S*S = v mod x^p, p is power of 2
        v.resize(p);
        if (p == 1) return {1};
        vi S = sqrt(v,p/2);
        vi ans = S+conv(v,inv(S,p));
        while (sz(ans) > p) ans.pop_back();
        ans *= inv(2);
        return ans;
    }
    
    vi poly[1<<19];
    
    void precompute(int ind, vi vals) { 
        if (sz(vals) == 1) { poly[ind] = {sub(MOD,vals[0]),1}; return; }
        int m = sz(vals)/2;
        precompute(2*ind,vi(vals.begin(),vals.begin()+m));
        precompute(2*ind+1,vi(vals.begin()+m,vals.end()));
        poly[ind] = conv(poly[2*ind],poly[2*ind+1]);
    }
    
    void eval(int ind, vi p, vi& ans) { // evaluate p over all elements of val
        p = divi(p,poly[ind]).s;
        if (sz(poly[ind]) == 2) { ans.pb(p[0]); return; }
        eval(2*ind,p,ans); eval(2*ind+1,p,ans);
    }
}

using namespace NTTextend;