/**
* Source: own
* Description: Pairs reduce frequency of collision
* Verification: Dec 17 Plat 1
*/

// See Mod.cpp for pair operators

struct hsh {
    string S; 
    vpi po, ipo, cum;
    pi base = mp(948392576,573928192), invbase; // probably want to randomize base
    
    void gen(string _S) {
        invbase = {inv(base.f),inv(base.s)};
        S = _S; po.resize(sz(S)), ipo.resize(sz(S)), cum.resize(sz(S)+1);
        
        po[0] = ipo[0] = {1,1};
        FOR(i,1,sz(S)) po[i] = po[i-1]*base, ipo[i] = ipo[i-1]*invbase;
        F0R(i,sz(S)) cum[i+1] = cum[i]+po[i]*(int)(S[i]-'a'+1);
    }
    
    pi get(int l, int r) {  return ipo[l]*(cum[r+1]-cum[l]); }
    
    int lcp(hsh& b) {
        int lo = 0, hi = min(sz(S),sz(b.S));
        while (lo < hi) {
            int mid = (lo+hi+1)/2;
            if (get(0,mid-1) == b.get(0,mid-1)) lo = mid;
            else hi = mid-1;
        }
        return lo;
    }
};