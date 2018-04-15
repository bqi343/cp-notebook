namespace Poly {
    ll norm(ll x) { return (x%MOD+MOD)%MOD; }

    vl operator+(vl a, vl b) {
        a.resize(max(sz(a),sz(b)));
        F0R(i,sz(a)) a[i] = norm(a[i]+b[i]);
        return a;
    }
    
    vl operator*(vl a, vl b) {
        vl x(sz(a)+sz(b)-1);
        F0R(i,sz(a)) F0R(j,sz(b)) x[i+j] = norm(x[i+j]+a[i]*b[j]);
        return x;
    }
    
    vl operator*(vl a, ll b) {
        for (ll& i: a) i = norm(i*b);
        return a;
    }
    
    vl interpolate(vector<pl> v) {
        vl ret;
        F0R(i,sz(v)) {
            vl prod = {1};
            ll todiv = 1;
            F0R(j,sz(v)) if (i != j) {
                todiv = norm(todiv*(v[i].f-v[j].f));
                vl tmp = {norm(-v[j].f),1};
                prod = prod*tmp;
            }
            prod = prod*inv(todiv);
            prod = prod*v[i].s;
            ret = ret+prod;
        }
        return ret;
    }
    
    void prin(vl x) {
        for (ll i: x) cout << i << " ";
        cout << "\n";
    }
}
