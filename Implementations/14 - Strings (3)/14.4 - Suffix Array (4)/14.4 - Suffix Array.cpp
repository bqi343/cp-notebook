/**
* Sources: SuprDewd, KACTL, majk
* Task: https://open.kattis.com/problems/suffixsorting
* Verification: USACO December 2017: Standing out from the herd: http://usaco.org/index.php?page=viewproblem2&cpid=768
* Code to Verify: https://pastebin.com/y2Z9FYr6
*/

struct suffix_array {
    int N;
    vi idx;
    string str;
    
    void compress(vi& v) {
        vi V = v; sort(all(V)); V.erase(unique(all(V)),V.end());
        for (int& i: v) i = lb(all(V),i)-V.begin()+1;
    }
    
    vi a, A, A2, L, L2, cum;
    
    void initVar(string _str) {
        str = _str; N = sz(str);
        a.resize(N);
        A.resize(N); F0R(i,N) A[i] = str[i]; compress(A); A2.resize(N);
        L.resize(N); F0R(i,N) L[i] = i; L2.resize(N);
        cum.resize(N+1); 
    }
    
    int get(int x) { return x >= N ? 0 : A[x]; }
    
    void sort_by(int x) { // stable sort elements in a by b
    	fill(all(cum),0); F0R(i,N) cum[get(i+x)] ++;
        int sum = 0; F0R(i,N+1) cum[i] = (sum += cum[i], sum-cum[i]);
        
        for (int i: L) L2[cum[get(i+x)]++] = i;
        swap(L,L2);
    }
    
    void init(string _str) {
        initVar(_str);
        
        for (int cnt = 1; cnt < N; cnt <<= 1) { 
            sort_by(cnt), sort_by(0);
        
            F0R(i,N) {
                if (i == 0) A2[L[i]] = 1;
                else A2[L[i]] = A2[L[i-1]]+
                    (mp(get(L[i]),get(L[i]+cnt)) != mp(get(L[i-1]),get(L[i-1]+cnt)));
            }
            
            swap(A,A2);
        }
        
        F0R(i,N) a[A[i]-1] = i;
    }
    
	vi lcp() { // KACTL
		int n = sz(str), h = 0;
		vi inv(n), res(n);
		F0R(i,N) inv[a[i]] = i;
		F0R(i,N) if (inv[i]) {
			int p0 = a[inv[i] - 1];
			while (max(i,p0)+h < N && str[i+h] == str[p0+h]) h++;
			res[inv[i]] = h;
			if (h) h--;
		}
		return res;
	}
};
