/**
* Description: offline subtree queries in O(Nlog^2N)
*/

const int MX = 200001;

struct HeavyLightSet {
    int loc[MX], sub[MX], par[MX], val[MX];
    vi child[MX];
    map<int,int> dat[MX];
    
    void comb(int a, int b) {
        int A = loc[a], B = loc[b];
        if (sz(dat[A]) < sz(dat[B])) swap(a,b), swap(A,B);
        for (auto& x: dat[B]) dat[A][x.f] += x.s;
        dat[B].clear(); loc[b] = A;
    }
    
    void process(int ind) {
        sub[ind] = 1; loc[ind] = ind; dat[ind][val[ind]] ++;
        for (int i: child[ind]) {
            process(i); 
            comb(i,ind);
            sub[ind] += sub[i];
        }
        // now do stuff with values
    }
};