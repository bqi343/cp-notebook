/*
* Description: Solves 2SAT
* Source: ?
* Verification: https://www.spoj.com/problems/BUGLIFE/
* Also useful: at most one
    http://codeforces.com/contest/1007
    /submission/40284510
*/

// struct scc

template<int SZ> struct twosat {
    scc<2*SZ> S;
    int N;
    
    void OR(int x, int y) { S.addEdge(x^1,y); S.addEdge(y^1,x); }
    
    int tmp[2*SZ];
    bitset<SZ> ans;
    
    bool solve() {
        S.N = 2*N; S.genSCC();
    	for (int i = 0; i < 2*N; i += 2) if (S.comp[i] == S.comp[i^1]) return 0;
    	reverse(all(S.allComp));
    	for (int i: S.allComp) if (tmp[i] == 0) 
    	    tmp[i] = 1, tmp[S.comp[i^1]] = -1;
	    F0R(i,N) if (tmp[S.comp[2*i]] == 1) ans[i] = 1;
    	return 1;
    }
};