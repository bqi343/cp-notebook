/**
 * Description: N-D range sum query with point update
 * Sources: 
    * https://codeforces.com/blog/entry/64914
    * https://www.geeksforgeeks.org/binary-indexed-tree-range-update-range-queries/
 * Verification: SPOJ matsum
 */

template <class T, int ...Ns> struct BIT {
    T val = 0;
    void upd(T v) { val += v; }
    T query() { return val; }
};

template <class T, int N, int... Ns> struct BIT<T, N, Ns...> {
    BIT<T,Ns...> bit[N + 1];
    template<typename... Args> void upd(int pos, Args... args) {
        for (; pos <= N; pos += (pos&-pos)) bit[pos].upd(args...);
    }
    template<typename... Args> T sum(int r, Args... args) {
        T res = 0; for (; r; r -= (r&-r)) res += bit[r].query(args...); 
        return res;
    }
    template<typename... Args> T query(int l, int r, Args... args) {
        return sum(r,args...)-sum(l-1,args...);
    }
}; // BIT<int,10,10> gives a 2D BIT

template<class T, int SZ> struct BITrange {
    BIT<T,SZ> bit[2]; // piecewise linear functions
    // let cum[x] = sum_{i=1}^{x}a[i]
    void upd(int hi, T val) { // add val to a[1..hi]
        bit[1].upd(1,val), bit[1].upd(hi+1,-val); // if x <= hi, cum[x] += val*x
        bit[0].upd(hi+1,hi*val); // if x > hi, cum[x] += val*hi
    }
    void upd(int lo, int hi, T val) { upd(lo-1,-val), upd(hi,val); }
    T sum(int x) { return bit[1].sum(x)*x+bit[0].sum(x); } // get cum[x]
    T query(int x, int y) { return sum(y)-sum(x-1); }
}; // equivalent to 1D lazy segment tree for sum
