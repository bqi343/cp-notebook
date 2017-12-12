// NTT Template

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
        while (x.size() && x.back() == 0) x.pop_back();
    }
    
    vl transform(vl x) {
        int L = get(sz(x)), n = 1<<L; 
        x.resize(n);
        
        FOR(i,1,L+1) {
            int inc = n>>i;
            F0R(j,inc) {
                int z = 1<<(i-1); // 1<<(i-1)
                
                vl tmp(x.begin()+(2*j+1)*z,x.begin()+(2*j+2)*z);
                FOR(k,(2*j+1)*z,(2*j+2)*z) x[k] = 0;
                tmp = Poly::NTT::conv(tmp,po10[i-1]); normalize(tmp);
                F0R(k,2*z) {
                    if (k < sz(tmp)) x[k+2*j*z] += tmp[k];
                    if (x[k+2*j*z] >= base) {
                        x[k+2*j*z] -= base;
                        x[k+2*j*z+1] ++;
                    }
                }
            }
        }
        normalize(x);
        return x;
    }
};

Base B;

int main() {
	ios_base::sync_with_stdio(0);cin.tie(0);
	F0R(i,10) F0R(j,10) F0R(k,10) {
	    vl z = {k,j,i};
	    vl o = B.transform(z);
	    for (ll x: o) cout << x << " ";
	    cout << "\n";
	}
}