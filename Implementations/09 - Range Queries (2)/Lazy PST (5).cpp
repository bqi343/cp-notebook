/**
* Description: persistent segtree without lazy updates
* Sources: CF, Franklyn Wang
*/ 

template<int SZ> struct pseg {
    static const int LIMIT = 10000000;
    int val[LIMIT], l[LIMIT], r[LIMIT], nex = 0;
    int lazy[LIMIT];
    
    //// HELPER
    int copy(int cur) {
        int x = nex ++;
        val[x] = val[cur], l[x] = l[cur], r[x] = r[cur], lazy[x] = lazy[cur];
        return x;
    }
    int comb(int a, int b) { return min(a,b); }
    void pull(int x) { val[x] = comb(val[l[x]],val[r[x]]); }
    void push(int cur, int L, int R) {
        if (!lazy[cur]) return;
        if (L != R) {
            l[cur] = copy(l[cur]);
            val[l[cur]] += lazy[cur];
            lazy[l[cur]] += lazy[cur];
            
            r[cur] = copy(r[cur]);
            val[r[cur]] += lazy[cur];
            lazy[r[cur]] += lazy[cur];
        }
        lazy[cur] = 0;
    }

    //// IMPORTANT
    int query(int cur, int lo, int hi, int L, int R) {  
        if (lo <= L && R <= hi) return val[cur];
        if (R < lo || hi < L) return MOD;
        int M = (L+R)/2;
        return lazy[cur]+comb(query(l[cur],lo,hi,L,M),query(r[cur],lo,hi,M+1,R));
    }
    int upd(int cur, int lo, int hi, int v, int L, int R) {
        if (R < lo || hi < L) return cur;
        
        int x = copy(cur);
        if (lo <= L && R <= hi) { val[x] += v, lazy[x] += v; return x; }
        push(x,L,R);
        
        int M = (L+R)/2;
        l[x] = upd(l[x],lo,hi,v,L,M), r[x] = upd(r[x],lo,hi,v,M+1,R);
        pull(x); return x;
    }
    int build(vi& arr, int L, int R) {
        int cur = nex++;
        if (L == R) {
            if (L < sz(arr)) val[cur] = arr[L];
            return cur;
        }
        
        int M = (L+R)/2;
        l[cur] = build(arr,L,M), r[cur] = build(arr,M+1,R);
        pull(cur); return cur;
    }
    
    //// PUBLIC
    vi loc;
    void upd(int lo, int hi, int v) { loc.pb(upd(loc.back(),lo,hi,v,0,SZ-1)); }
    int query(int ti, int lo, int hi) { return query(loc[ti],lo,hi,0,SZ-1); }
    void build(vi& arr) { loc.pb(build(arr,0,SZ-1)); }
};