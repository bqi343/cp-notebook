/**
* Source: SuprDewd CP Course
* Task: https://open.kattis.com/problems/suffixsorting
* KACTL version is slightly faster
* Verification: USACO December 2017: Standing out from the herd: http://usaco.org/index.php?page=viewproblem2&cpid=768
* Code to Verify: https://pastebin.com/y2Z9FYr6
*/

struct suffix_array {
    int N;
    vector<vi> P;
    vector<array<int,3>> L;
    vi idx;
    string str;
    
    /*void bucket(int ind) {
        int mn = MOD, mx = -MOD;
        
        for (auto a: L) mn = min(mn,a[ind]), mx = max(mx,a[ind]);
        vector<array<int,3>> tmp[mx-mn+1];
        F0Rd(i,sz(L)) tmp[L[i][ind]-mn].pb(L[i]);
        
        int nex = 0;
        F0R(i,mx-mn+1) for (auto a: tmp[i]) L[nex++] = a;
    }
    
    void bucket_sort() {
        bucket(1), bucket(0);
    }*/
    
    suffix_array(string _str) {
        str = _str; N = sz(str);
        P.pb(vi(N)); L.resize(N);
        F0R(i,N) P[0][i] = str[i];
        
        for (int stp = 1, cnt = 1; cnt < N; stp ++, cnt *= 2) {
            P.pb(vi(N));
            F0R(i,N) L[i] = {P[stp-1][i],i+cnt < N ? P[stp-1][i+cnt] : -1,i};
            sort(all(L)); // bucket_sort();
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
