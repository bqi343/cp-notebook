/**
 * Description: Evaluate degree n polynomial at n points in O(nlog^2n) time
 * Source: CF, http://people.csail.mit.edu/madhu/ST12/scribe/lect06.pdf
 * Verification: https://codeforces.com/contest/438/problem/E
 */

using namespace FFT;

namespace FFTextend { 
    vmi inv(vmi v, int p) { // compute inverse of v mod x^p, where v[0] = 1 
        v.resize(p); if (p == 1) return {1};
        // assert(v[0] == 1);
        if (p&1) { // naive
            mi cur = 0; auto V = inv(v,p-1);
            F0R(i,p-1) if (p-1-i < sz(v)) cur -= V[i]*v[p-1-i];
            V.pb(cur); return V;
        }
        vmi a = inv(v,p/2);
        vmi h0 = vmi(v.begin(),v.begin()+p/2);
        vmi h1 = vmi(v.begin()+p/2,v.end());
        vmi c = conv(a,h0); c = vmi(c.begin()+p/2,c.end()); 
        // assert(c[0].val == 1);
        
        vmi b = conv(mi(-1)*a,conv(h1,a)+c); b.resz(p/2); 
        a.insert(a.end(),all(b)); return a;
    }
    
    pair<vmi,vmi> divmi(vmi f, vmi g) { // f = q*g+r
        if (sz(f) < sz(g)) return {{},f};
        vmi q = conv(inv(rev(g),sz(f)-sz(g)+1),rev(f));
        q.resz(sz(f)-sz(g)+1); q = rev(q);
        vmi r = f-conv(q,g); r.resize(sz(g)-1);
        return {q,r};
    }
    
    vmi sqrt(vmi v, int p) { // S*S = v mod x^p, p is power of 2
        v.resz(p);
        if (p == 1) return {1};
        vmi S = sqrt(v,p/2);
        vmi ans = S+conv(v,inv(S,p));
        while (sz(ans) > p) ans.pop_back();
        ans *= mi(1)/2;
        return ans;
    }
    
    vmi poly[1<<19];
    
    void precompute(int ind, vmi vals) { 
        if (sz(vals) == 1) { poly[ind] = {-vals[0],1}; return; }
        int m = sz(vals)/2;
        precompute(2*ind,vmi(vals.begin(),vals.begin()+m));
        precompute(2*ind+1,vmi(vals.begin()+m,vals.end()));
        poly[ind] = conv(poly[2*ind],poly[2*ind+1]);
    }
    
    void eval(int ind, vmi p, vmi& ans) { // evaluate p over all elements of val
        p = divmi(p,poly[ind]).s;
        if (sz(poly[ind]) == 2) { ans.pb(p[0]); return; }
        eval(2*ind,p,ans); eval(2*ind+1,p,ans);
    }
}

using namespace FFTextend;