/**
 * Description: Main-Lorentz Algorithm
    * Finds all (x,y) such that s.substr(x,y-1) == s.substr(x+y,y-1)
    * https://cp-algorithms.com/string/main_lorentz.html
 * Source: own
 * Usage: http://codeforces.com/contest/1043/problem/G
 */
 
template<int SZ> struct stringRepeat {
    string S;
    vector<array<int,3>> al;
    
    vector<array<int,3>> solveLeft(string s, int m) {
        vector<array<int,3>> v;
        
        vi v2 = get(string(s.begin()+m+1,s.end()),string(s.begin(),s.begin()+m+1));
        string V = string(s.begin(),s.begin()+m+2); reverse(all(V)); vi v1 = z(V); reverse(all(v1));
        
        F0R(i,m+1) if (v1[i]+v2[i] >= m+2-i) {
            int lo = max(1,m+2-i-v2[i]), hi = min(v1[i],m+1-i); 
            lo = i-lo+1, hi = i-hi+1; swap(lo,hi); 
            v.pb({2*(m+1-i),lo,hi});
        }
        
        return v;
    }
    
    void divi(int l, int r) {
        if (l == r) return;
        int m = (l+r)/2; divi(l,m); divi(m+1,r);
        
        string t = string(S.begin()+l,S.begin()+r+1);
        m = (sz(t)-1)/2;
        auto a = solveLeft(t,m);
        reverse(all(t));
        auto b = solveLeft(t,sz(t)-2-m);
        
        for (auto x: a) al.pb({x[0],x[1]+l,x[2]+l}); 
        for (auto x: b) {
            int ad = r-x[0]+1; 
            al.pb({x[0],ad-x[2],ad-x[1]}); 
        }
    }
    
    void init(string _S) {
        S = _S;
        divi(0,sz(S)-1);
    }
    
    vi genLen() { // for each index
        priority_queue<pi,vpi,greater<pi>> m; m.push({MOD,MOD});
        vpi ins[SZ]; for (auto a: al) ins[a[1]].pb({a[0],a[2]}); 
        vi len(SZ);
        F0R(i,sz(S)) {
            for (auto j: ins[i]) m.push(j);
            while (m.top().s < i) m.pop();
            len[i] = m.top().f;
        }
        return len;
    }
};