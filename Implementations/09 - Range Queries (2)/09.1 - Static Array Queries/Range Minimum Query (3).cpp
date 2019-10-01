/**
 * Description: supports 1D range minimum query in constant time
 * Source: own
 * Verification: 
    * http://wcipeg.com/problem/ioi1223
    * https://pastebin.com/ChpniVZL
 */

template<class T, int SZ> struct RMQ {
    constexpr static int level(int x) { return 31-__builtin_clz(x); } // floor(log_2(x))
    int stor[SZ][level(SZ)+1];
    vector<T> v;
    
    int comb(int a, int b) { return v[a] == v[b] ? min(a,b) : (v[a] < v[b] ? a : b); } // index of minimum
    
    void init(const vector<T>& _v) {
        v = _v; F0R(i,sz(v)) stor[i][0] = i; 
        FOR(j,1,level(sz(v))+1) F0R(i,sz(v)-(1<<j)+1) 
            stor[i][j] = comb(stor[i][j-1],stor[i+(1<<(j-1))][j-1]);
    }
    
    int index(int l, int r) { // get index of min element
        int x = level(r-l+1);
        return comb(stor[l][x],stor[r-(1<<x)+1][x]);
    }
    T query(int l, int r) { return v[index(l,r)]; }
};