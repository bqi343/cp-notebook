/**
* Description: NTT Application
* Usage: 2017 VT HSPC - Alien Codebreaking
*/

// insert NTT template

struct Base {
    vl po10[21];
    const int base = 27;
    
    Base() {
        po10[0] = {10};
        FOR(i,1,21) {
            po10[i] = Poly::NTT::conv(po10[i-1],po10[i-1]);
            normalize(po10[i]);
        }
    }
    
    void normalize(vl& x) {
        F0R(i,sz(x)) if (x[i] >= base) {
            if (i == sz(x)-1) x.pb(0);
            x[i+1] += x[i]/base;
            x[i] %= base;
        }
        while (sz(x) && !x.back()) x.pop_back();
    }
    
    vl convert(vl in) {
        if (sz(in) == 1) return in;
        vl l = convert(vl(in.begin(),in.begin()+sz(in)/2));
        vl r = convert(vl(in.begin()+sz(in)/2,in.end()));
        
        r = Poly::NTT::conv(r,po10[get(sz(in))-1]);
        normalize(r);
        
        int z = max(sz(l),sz(r));
        r.resize(z);
        F0R(i,sz(l)) r[i] += l[i];
        normalize(r);
        return r;
    }
};

Base B;

int main() {
	F0R(i,10) F0R(j,10) F0R(k,10) {
	    vl z = {k,j,i};
	    vl o = B.transform(z);
	    for (ll x: o) cout << x << " ";
	    cout << "\n";
	}
}