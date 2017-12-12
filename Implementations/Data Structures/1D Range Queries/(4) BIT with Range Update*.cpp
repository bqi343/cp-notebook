// 1D range update, range query
// 6 min

template<int SZ> struct BIT {
    ll bit[2][SZ+1]; // sums piecewise linear functions
    
    BIT() { memset(bit,0,sizeof bit); }
    
    void u(int ind, int hi, int val) {
        for(;hi <= SZ; hi += (hi&-hi)) bit[ind][hi] += val;
    }
    
    void upd(int hi, int val) {
        u(1,1,val), u(1,hi+1,-val);
        u(0,hi+1,hi*val);
    }
    void upd(int lo, int hi, int val) { upd(lo-1,-val), upd(hi,val); }
    
    ll qsum(int x) {
        ll c1 = 0, c0 = 0;
        for (int x1 = x; x1 > 0; x1 -= (x1&-x1))
            c1 += bit[1][x1], c0 += bit[0][x1];
        return c1*x+c0;
    }
    ll qsum(int x, int y) { return qsum(y)-qsum(x-1); }
};

int main() {
    BIT<1<<17> bit;
    bit.upd(2,5,7);
    cout << bit.qsum(1,2) << " " << bit.qsum(4,6) << "\n"; // 7 14
}
