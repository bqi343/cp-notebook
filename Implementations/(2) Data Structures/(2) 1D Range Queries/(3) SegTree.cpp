/*
* Source: http://codeforces.com/blog/entry/18051
* Description: 1D point update, range query
* Verification: SPOJ Fenwick
*/

template<class T, int SZ> struct Seg {
    T seg[2*SZ], MN = 0;
    
    Seg() {
        memset(seg,0,sizeof seg);
    }
    
    T comb(T a, T b) { return a+b; } // easily change this to min or max
    
    void upd(int p, T value) {  // set value at position p
        for (seg[p += SZ] = value; p > 1; p >>= 1){ 
            //be careful here: some updates are noncommutative! 
            if (p < (p^1)){
                 seg[p>>1] = comb(seg[p],seg[p^1]);
            }
            else{
                 seg[p>>1] = comb(seg[p^1], seg[p]);    
            }
        }
    }
    
    void build() {
        F0Rd(i,SZ) seg[i] = comb(seg[2*i],seg[2*i+1]);
    }
    
    T query(int l, int r) {  // sum on interval [l, r]
        T res = MN; r++;
        for (l += SZ, r += SZ; l < r; l >>= 1, r >>= 1) {
            if (l&1) res = comb(res,seg[l++]);
            if (r&1) res = comb(res,seg[--r]);
        }
        return res;
    }
};
