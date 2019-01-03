/**
* Description:
* Sources: SuprDewd, KACTL, majk, ekzhang
* Verification: 
    * http://usaco.org/index.php?page=viewproblem2&cpid=768
        * https://pastebin.com/y2Z9FYr6
    * https://open.kattis.com/problems/suffixsorting
    * https://codeforces.com/contest/1090/problem/J
*/

struct LCP {
    string S; int N;
    vi sa, inv, lcp;
    RMQ<int,MX> R; 
    
    void suffixArray() { // http://ekzlib.herokuapp.com
        sa.resz(N);
        vi classes(N);
        F0R(i,N) {
            sa[i] = N - 1 - i;
            classes[i] = S[i];
        }
        stable_sort(all(sa), [this](int i, int j) { return S[i] < S[j]; });
        for (int len = 1; len < N; len *= 2) {
            vi c(classes);
            F0R(i,N) {
            	bool same = i && sa[i - 1] + len < N
            	              && c[sa[i]] == c[sa[i - 1]]
            	              && c[sa[i] + len / 2] == c[sa[i - 1] + len / 2];
            	classes[sa[i]] = same ? classes[sa[i - 1]] : i;
            }
            vi cnt(N), s(sa);
            F0R(i,N) cnt[i] = i;
            F0R(i,N) {
                int s1 = s[i] - len;
                if (s1 >= 0) sa[cnt[classes[s1]]++] = s1; // order pairs w/ same first element by second element
            }
        }
    }
    
    void lcpArray() { // KACTL
        int h = 0;
        inv.resz(N), lcp.resz(N);
        F0R(i,N) inv[sa[i]] = i;
        F0R(i,N) if (inv[i]) {
            int p0 = sa[inv[i] - 1];
            while (max(i,p0)+h < N && S[i+h] == S[p0+h]) h++;
            lcp[inv[i]] = h; // lcp of suffixes starting at p0 and i
            if (h) h--;
        }
    }
    
    void init(string _S) {
        S = _S; N = sz(S);
        suffixArray(); lcpArray();
        R.build(lcp);
    }
    
    int getLCP(int a, int b) {
        if (max(a,b) >= N) return 0;
        if (a == b) return N-a;
        int t0 = inv[a], t1 = inv[b];
        if (t0 > t1) swap(t0,t1);
        return R.query(t0+1,t1);
    }
};
