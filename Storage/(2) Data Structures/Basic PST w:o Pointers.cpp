/**
* Description: persistent segtree without lazy updates
* Verification: https://beta.atcoder.jp/contests/arc068/tasks/arc068_c
* Sources: CF, Franklyn Wang
*/ 

template<int SZ> struct pseg {
    static const int LIMIT = 10000000;
    
    int val[LIMIT], l[LIMIT], r[LIMIT], nex = 0;
    
    int comb(int a, int b) { return a+b; }
    void pull(int x) { val[x] = comb(val[l[x]],val[r[x]]); }
    
    int query(int cur, int lo, int hi, int L, int R) {  
        if (lo <= L && R <= hi) return val[cur];
        if (R < lo || hi < L) return 0;
        int M = (L+R)/2;
        return comb(query(l[cur],lo,hi,L,M),query(r[cur],lo,hi,M+1,R));
    }
    
    int upd(int cur, int ind, int v, int L, int R) {
        if (R < ind || ind < L) return cur;
        
        int x = nex++;
        if (ind <= L && R <= ind) {
            val[x] = val[cur]+v;
            return x;
        }
        
        int M = (L+R)/2;
        l[x] = upd(l[cur],ind,v,L,M);
        r[x] = upd(r[cur],ind,v,M+1,R);
        pull(x); return x;
    }
    
    int build(vi& arr, int L, int R) {
        int cur = nex++;
        if (L == R) {
            if (L < sz(arr)) val[cur] = arr[L];
            return cur;
        }
        
        int M = (L+R)/2;
        l[cur] = build(arr,L,M);
        r[cur] = build(arr,M+1,R);
        pull(cur); return cur;
    }
    
    vi loc;
    void upd(int ind, int v) { loc.pb(upd(loc.back(),ind,v,0,SZ-1)); }
    int query(int ti, int lo, int hi) { return query(loc[ti],lo,hi,0,SZ-1); }
    void build(vi& arr) { loc.pb(build(arr,0,SZ-1)); }
};