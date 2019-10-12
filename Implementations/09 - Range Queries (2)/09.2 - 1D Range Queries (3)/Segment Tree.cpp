/*
 * Source: http://codeforces.com/blog/entry/18051
 * Description: 1D point update, range query
 * Verification: SPOJ Fenwick
 */

template<class T, int SZ> struct Seg { // SZ doesn't have to be power of 2
    const T ID = 0; // comb(ID,b) must equal b
    T comb(T a, T b) { return a+b; } // easily change this to min or max

    T seg[2*SZ];
    Seg() { memset(seg,0,sizeof seg); }

    void pull(int p) { seg[p] = comb(seg[2*p],seg[2*p+1]); }
    void build() { ROF(i,1,SZ) pull(i); }
    
    void upd(int p, T value) {  // set value at position p
        seg[p += SZ] = value;
        for (p /= 2; p; p /= 2) pull(p);
    }

    T query(int l, int r) {  // sum on interval [l, r]
        T resl = ID, resr = ID; // make sure non-commutative operations work
        for (l += SZ, r += SZ+1; l < r; l /= 2, r /= 2) {
            if (l&1) resl = comb(resl,seg[l++]);
            if (r&1) resr = comb(seg[--r],resr);
        }
        return comb(resl,resr);
    }
};