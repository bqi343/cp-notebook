/**
* Source: SuprDewd CP Course
* Task: https://open.kattis.com/problems/suffixsorting
* Verification: USACO December 2017: Standing out from the herd: http://usaco.org/index.php?page=viewproblem2&cpid=768
* Code to Verify: https://pastebin.com/y2Z9FYr6
*/

struct suffix_array {
    int N;
    vector<vi> P;
    vector<array<int,3>> L;
    vi idx;
    string str;
    
    void bucket_sort(vector<array<int,3>>& v, int ind) {
        int mn = MOD, mx = -MOD;
        for (auto a: v) mn = min(mn,a[ind]), mx = max(mx,a[ind]);
        
        vi tmp(mx-mn+1), st(mx-mn+1);
        F0R(i,sz(v)) tmp[L[i][ind]-mn] ++;
        FOR(i,1,mx-mn+1) st[i] = st[i-1]+tmp[i-1];
        
        vector<array<int,3>> V(sz(v));
        F0R(i,sz(v)) V[st[v[i][ind]-mn]++] = v[i];
        v = V;
    }
    
    suffix_array(string _str) {
        str = _str; N = sz(str);
        P.pb(vi(N)); L.resize(N);
        F0R(i,N) P[0][i] = str[i];
        
        for (int stp = 1, cnt = 1; cnt < N; stp ++, cnt *= 2) {
            P.pb(vi(N));
            F0R(i,N) L[i] = {P[stp-1][i],i+cnt < N ? P[stp-1][i+cnt] : -1,i};
            bucket_sort(L,1); bucket_sort(L,0); // sort(all(L));
            F0R(i,N) {
                if (i && mp(L[i][0],L[i][1]) == mp(L[i-1][0],L[i-1][1])) P[stp][L[i][2]] = P[stp][L[i-1][2]];
                else P[stp][L[i][2]] = i;
            }
        }
        
        idx.resize(N);
        F0R(i,sz(P.back())) idx[P.back()[i]] = i;
    }
    
    int lcp(int x, int y) {
        int res = 0;
        if (x == y) return N-x;
        for (int k = sz(P) - 1; k >= 0 && x < N && y < N; k--) {
            if (P[k][x] == P[k][y]) {
                x += 1 << k;
                y += 1 << k;
                res += 1 << k;
            }
        }
        return res;
    }
};
