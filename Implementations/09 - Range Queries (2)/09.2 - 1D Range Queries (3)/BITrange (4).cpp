/**
* Description: 1D range update, range sum query
	* Alternative to lazy segment tree
* Source: GeeksForGeeks?
* Verification: ?
*/

// struct BIT

template<class T, int SZ> struct BITrange {
    BIT<T,SZ> bit[2]; // sums piecewise linear functions
    
    void upd(int hi, T val) {
        bit[1].upd(1,val), bit[1].upd(hi+1,-val);
        bit[0].upd(hi+1,hi*val);
    }
    void upd(int lo, int hi, T val) { upd(lo-1,-val), upd(hi,val); }
    
    T query(int x) { return bit[1].query(x)*x+bit[0].query(x); }
    T query(int x, int y) { return query(y)-query(x-1); }
};