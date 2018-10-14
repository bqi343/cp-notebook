/**
* Description: 
	* Supports point update & rectangle query
	* can be extended to rectangle update
	* can also use with unordered map
* Source: Own?
* Verification: SPOJ matsum
*/

// struct BIT

template<class T, int SZ> struct BIT2D { 
    BIT<T,SZ> bit[SZ+1];
    void upd(int X, int Y, T val) {
        for (; X <= SZ; X += (X&-X)) bit[X].upd(Y,val);
    }
    T query(int X, int Y) {
        T ans = 0;
        for (; X > 0; X -= (X&-X)) ans += bit[X].query(Y);
        return ans;
    }
    T query(int X1, int X2, int Y1, int Y2) {
        return query(X2,Y2)-query(X1-1,Y2)
            -query(X2,Y1-1)+query(X1-1,Y1-1);
    }
};