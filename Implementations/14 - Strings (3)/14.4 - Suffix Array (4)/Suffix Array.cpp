/**
* Description:
* Source: SuprDewd, KACTL, majk, ekzhang
* Verification: 
    * http://usaco.org/index.php?page=viewproblem2&cpid=768
        * https://pastebin.com/y2Z9FYr6
    * https://open.kattis.com/problems/suffixsorting
    * https://codeforces.com/contest/1090/problem/J
*/

template<int SZ> struct LCP {
    string S; int N;
    void init(string _S) {
        S = _S; N = sz(S);
        suffixArray(); lcpArray();
        // R.init(lcp);
    }
    
    vi sa;
    void suffixArray() { // http://ekzlib.herokuapp.com
        sa.rsz(N); vi classes(N);
        F0R(i,N) sa[i] = N-1-i, classes[i] = S[i];
        stable_sort(all(sa), [this](int i, int j) { return S[i] < S[j]; });
        for (int len = 1; len < N; len *= 2) { 
            vi c(classes);
            F0R(i,N) { // compare first len characters of each suffix
                bool same = i && sa[i-1] + len < N
                              && c[sa[i]] == c[sa[i-1]]
                              && c[sa[i]+len/2] == c[sa[i-1] + len/2];
                classes[sa[i]] = same ? classes[sa[i-1]] : i;
            }
            vi nex(N), s(sa); F0R(i,N) nex[i] = i; // suffixes with <= len chars will not change pos 
            F0R(i,N) {
                int s1 = s[i]-len;
                if (s1 >= 0) sa[nex[classes[s1]]++] = s1; // order pairs w/ same first len chars by next len chars 
            }
        }
    }
    
    vi inv, lcp;
    void lcpArray() { // KACTL
        inv.rsz(N); F0R(i,N) inv[sa[i]] = i; // pos -> suffix rank
        lcp = vi(N-1);
        int h = 0;
        F0R(i,N) if (inv[i]) {
            int pre = sa[inv[i]-1];
            while (max(i,pre)+h < N && S[i+h] == S[pre+h]) h++;
            lcp[inv[i]-1] = h; // lcp of suffixes starting at pre and i
            if (h) h--; // if we cut off first chars of two strings with lcp h, then remaining portions still have lcp h-1 
        }
    }
    
    /*RMQ<int,SZ> R; 
    int getLCP(int a, int b) {
        if (max(a,b) >= N) return 0;
        if (a == b) return N-a;
        int t0 = inv[a], t1 = inv[b];
        if (t0 > t1) swap(t0,t1);
        return R.query(t0,t1-1);
    }*/
};