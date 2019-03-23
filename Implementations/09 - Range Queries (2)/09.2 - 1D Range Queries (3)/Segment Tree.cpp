/*
 * Source: http://codeforces.com/blog/entry/18051
 * Description: 1D point update, range query
 * Verification: SPOJ Fenwick
 */

template<class T, int SZ> struct Seg { // SZ should be power of 2
    T seg[2*SZ], ID = 0;

    Seg() { memset(seg,0,sizeof seg); }
    T comb(T a, T b) { return a+b; }
    // easily change this to min or max
    // comb(ID,b) must equal b

    void build() { F0Rd(i,SZ) seg[i] = comb(seg[2*i],seg[2*i+1]); }

    void upd(int p, T value) {  // set value at position p
        for (seg[p += SZ] = value; p > 1; p >>= 1)
            seg[p>>1] = comb(seg[(p|1)^1],seg[p|1]);
            // make sure non-commutative operations work
    }

    T query(int l, int r) {  // sum on interval [l, r]
        T res1 = ID, res2 = ID; r++;
        for (l += SZ, r += SZ; l < r; l >>= 1, r >>= 1) {
            if (l&1) res1 = comb(res1,seg[l++]);
            if (r&1) res2 = comb(seg[--r],res2);
        }
        return comb(res1,res2);
    }
};
