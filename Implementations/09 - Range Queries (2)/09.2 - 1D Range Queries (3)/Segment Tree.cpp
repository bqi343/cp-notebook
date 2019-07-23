/*
 * Source: http://codeforces.com/blog/entry/18051
 * Description: 1D point update, range query
 * Verification: SPOJ Fenwick
 */

template<class T, int SZ> struct Seg { // SZ should be power of 2
    T ID = 0; // comb(ID,b) must equal b
    T comb(T a, T b) { return a+b; } // easily change this to min or max

    T seg[2*SZ];
    Seg() { memset(seg,0,sizeof seg); }

    void build() { FORd(i,1,SZ) seg[i] = comb(seg[2*i],seg[2*i+1]); }

    void upd(int p, T value) {  // set value at position p
        seg[p += SZ] = value;
        for (p /= 2; p; p /= 2) seg[p] = comb(seg[2*p],seg[2*p+1]);
    }

    T query(int l, int r) {  // sum on interval [l, r]
        r ++; T lres = ID, rres = ID; // make sure non-commutative operations work
        for (l += SZ, r += SZ; l < r; l /= 2, r /= 2) {
            if (l&1) lres = comb(lres,seg[l++]);
            if (r&1) rres = comb(seg[--r],rres);
        }
        return comb(lres,rres);
    }
};
