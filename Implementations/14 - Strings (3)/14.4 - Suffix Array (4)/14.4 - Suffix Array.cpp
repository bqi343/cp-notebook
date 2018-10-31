/**
* Description:
* Sources: SuprDewd, KACTL, majk
* Verification: 
    * http://usaco.org/index.php?page=viewproblem2&cpid=768
        * https://pastebin.com/y2Z9FYr6
    * https://open.kattis.com/problems/suffixsorting
*/

struct SuffixArray {
    int N;
    vi idx;
    string str;
    // RMQ<int,MX> R; 
    
    void compress(vi& v) {
        vi V = v; sort(all(V)); V.erase(unique(all(V)),V.end());
        for (int& i: v) i = lb(all(V),i)-V.begin()+1;
    }
    
    vi A, L; // A stores lexicographic value, L stores suffixes in order
    
    int get(int x) { return x >= N ? 0 : A[x]; }
    
    void sort_by(int x) { // stable sort elements in a by b
        vi cum(N+1); F0R(i,N) cum[get(i+x)] ++;
        int sum = 0; F0R(i,N+1) cum[i] = (sum += cum[i], sum-cum[i]);
        
        vi L2(N);
        for (int i: L) L2[cum[get(i+x)]++] = i;
        swap(L,L2);
    }
    
    void init(string _str) {
        str = _str; N = sz(str);
        A.resize(N); F0R(i,N) A[i] = str[i]; compress(A); 
        L.resize(N); F0R(i,N) L[i] = i;
        
        for (int cnt = 1; cnt < N; cnt <<= 1) { 
            sort_by(cnt), sort_by(0);
        
            vi A2(N);
            F0R(i,N) {
                if (i == 0) A2[L[i]] = 1;
                else A2[L[i]] = A2[L[i-1]]+
                    (mp(get(L[i]),get(L[i]+cnt)) != mp(get(L[i-1]),get(L[i-1]+cnt)));
            }
            
            swap(A,A2);
        }
        
        // vi v = lcpArray(); R.build(v);
    }
    
    vi lcpArray() { // KACTL
        int h = 0;
        vi inv(N), res(N);
        F0R(i,N) inv[L[i]] = i;
        F0R(i,N) if (inv[i]) {
            int p0 = L[inv[i] - 1];
            while (max(i,p0)+h < N && str[i+h] == str[p0+h]) h++;
            res[inv[i]] = h;
            if (h) h--;
        }
        return res;
    }
    
    /*int lcp(int a, int b) {
        if (a == b) return N-a;
        int t0 = A[a], t1 = A[b];
        if (t0 > t1) swap(t0,t1);
        return R.query(t0,t1-1);
    }*/
};

SuffixArray S; // S.init("bcabcb");
