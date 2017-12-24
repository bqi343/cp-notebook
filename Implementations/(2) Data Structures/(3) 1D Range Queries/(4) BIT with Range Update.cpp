/**
* Source: GeeksForGeeks?
* Description: 1D range update, range query
*/

template<int SZ> struct BITrange {
    ll bit[2][SZ+1]; // sums piecewise linear functions
    
    BITrange() { memset(bit,0,sizeof bit); }
    
    void u(int ind, int hi, ll val) {
        for(;hi <= SZ; hi += (hi&-hi)) bit[ind][hi] += val;
    }
    
    void upd(int hi, int val) {
        u(1,1,val), u(1,hi+1,-val);
        u(0,hi+1,hi*val);
    }
    void upd(int lo, int hi, ll val) { upd(lo-1,-val), upd(hi,val); }
    
    ll qsum(int x) {
        ll c1 = 0, c0 = 0;
        for (int x1 = x; x1 > 0; x1 -= (x1&-x1))
            c1 += bit[1][x1], c0 += bit[0][x1];
        return c1*x+c0;
    }
    ll qsum(int x, int y) { return qsum(y)-qsum(x-1); }
};

// BITrange<1<<17> b;