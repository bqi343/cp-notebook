/**
 * Description: constructs in O(nloglogn) and queries a range in O(1)
 * Source: https://cp-algorithms.com/data_structures/sqrt-tree.html
 * Verification: ?
 */ 
 
template<int SZ> struct sqrtTree {
    int n, precomp[32-__builtin_clz(SZ)];
    vi suf[SZ], pre[SZ], block[SZ], a;
    vi levels;
    
    void build(int ind, int lev) {
        int lev2 = (lev+1)/2;
        F0R(i,1<<(lev-lev2)) {
            int ind2 = ind+(i<<lev2);
            int prod = 1;
            F0R(j,1<<lev2) {
                int cur = ind2+j; MUL(prod,a[cur]); 
                suf[cur].pb(prod);
            }
            prod = 1;
            F0Rd(j,1<<lev2) {
                int cur = ind2+j; MUL(prod,a[cur]); 
                pre[cur].pb(prod);
            }
        }
        F0R(i,1<<lev) block[ind+i].pb(1);
        F0R(i,1<<(lev-lev2)) {
            int prod = 1;
            FOR(j,i,1<<(lev-lev2)) {
                MUL(prod,pre[ind+(j<<lev2)].back());
                block[ind+(i<<lev2)+j].back() = prod;
            }
        }
    }
    
    void buildLevel(int lev) {
        levels.pb(lev);
        if (lev == 1) { levels.pb(0); return; }
        for (int i = 0; i < sz(a); i += (1<<lev)) build(i,lev);
        buildLevel((lev+1)/2);
    }
    
    int queryBad(int l, int r) {
        int prod = 1; FOR(i,l,r+1) MUL(prod,a[i]);
        return prod;
    }
        
    int query(int l, int r) {
        int t = 31-__builtin_clz(l^r);
        if (t <= 0) return queryBad(l,r);
        int ind = precomp[t]; 
        int b0 = (l>>levels[ind])+1, b1 = (r>>levels[ind])-1;
        int ans = mul(pre[l][ind-1],suf[r][ind-1]);
        if (b0 <= b1) MUL(ans,block[(b0<<levels[ind])+b1%(1<<(levels[ind-1]-levels[ind]))][ind-1]);
        return ans;
    }
    
    void init() {
        F0R(i,SZ) suf[i].clear(), pre[i].clear(), block[i].clear();
        levels.clear(); 
        
        n = 1; while ((1<<n) < sz(a)) n ++;
        a.resz(1<<n);
        
        buildLevel(n);
        F0Rd(i,n) {
            if (i != n-1) precomp[i] = precomp[i+1];
            else precomp[i] = 0;
            while (levels[precomp[i]] > i) precomp[i] ++;
        }
    }
};