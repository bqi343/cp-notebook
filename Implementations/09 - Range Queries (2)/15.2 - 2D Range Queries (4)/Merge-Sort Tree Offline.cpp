/**
 * Description: merge-sort tree with offline updates
    * O(nlogn) memory, O(nlog^2n) time with better constant
 * Source: own
 * Verification: https://codeforces.com/contest/1093/problem/E
 */

template<class T> struct BIT {
    vector<T> bit, vals;
    
    void build() {
        vals.pb(0);
        sort(all(vals)); vals.erase(unique(all(vals)),vals.end());
        bit.resize(sz(vals));
    }
    
    int getInd(T k) {
        return ub(all(vals),k)-vals.begin()-1;
    }
    
    void upd(int k, T val) { // add val to index k
        k = getInd(k);
        for ( ;k < sz(vals); k += (k&-k)) bit[k] += val;
    }
    
    T query(int k) {
        k = getInd(k);
        T temp = 0;
        for (;k;k -= (k&-k)) temp += bit[k];
        return temp;
    }
    
    T query(int l, int r) { return query(r)-query(l-1); } // range query [l,r]
};

template<class T, int SZ> struct mstree { 
    BIT<T> val[SZ+1]; 
    
    void updPre(int x, int y) {
        for (int X = x; X <= SZ; X += X&-X) val[X].vals.pb(y);
    }
    
    void build() {
        F0R(i,SZ+1) val[i].build();
    }
    
    void upd(int x, int y, int t = 1) { // x-coordinate between 1 and SZ inclusive
        for (int X = x; X <= SZ; X += X&-X) val[X].upd(y,t);
    }
    
    int query(int x, int y) { 
        int t = 0;    
        for (;x > 0; x -= x&-x) t += val[x].query(y);
        return t;
    }
    
    int query(int lox, int hix, int loy, int hiy) { // query number of elements within a rectangle
        return query(hix,hiy)-query(lox-1,hiy)
            -query(hix,loy-1)+query(lox-1,loy-1);
    }
};
