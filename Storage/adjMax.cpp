/**
* Description: Gets closest element which is >= certain value 
* in certain direction
*/

template<class T, int SZ> struct adjMax {
    T mx[2*SZ];
    
    adjMax() { FOR(i,SZ,2*SZ) mx[i] = MOD; }
    
    void build() { F0Rd(i,SZ) mx[i] = max(mx[2*i],mx[2*i+1]); }
    
    T get(int x) { return mx[x^(1<<17)]; }
    
    T getDir(int a, int b, int dir) { 
        for (a ^= SZ;;a /= 2) // SZ is power of 2
            if ((a&1) != dir && mx[a^1] >= b) { 
                a ^= 1; 
                break; 
            }
            
        while (a < SZ) {
            if (mx[2*a^dir^1] >= b) a = 2*a^dir^1;
            else a = 2*a^dir;
        }
        
        return a^SZ;
    }
    
    void propagate(int x) {
        for (x += SZ; x > 1; x /= 2)
            mx[x/2] = max(mx[x],mx[x^1]);
    }
    
    void swa(int x) {
        swap(mx[x^SZ],mx[(x+1)^SZ]);
        propagate(x), propagate(x+1);
    }
};
