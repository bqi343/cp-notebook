/**
* Source: own
* Description: Pairs reduce frequency of collision
* Verification: Dec 17 Plat 1, CF Check Transcription
*/

using namespace pairOp;

const int tmp = (chrono::high_resolution_clock::now().time_since_epoch().count()%(MOD-1)+(MOD-1))%(MOD-1)+1;

struct hsh {
    string S; 
    vpi pows, ipows, cum;
    pi base = mp(948392576,tmp), invbase; // probably want to randomize base
    
    hsh() {}
    hsh(string s) { gen(s); }
    
    void gen(string _S) {
        invbase = {inv(base.f),inv(base.s)};
        S = _S; pows.resize(sz(S)), ipows.resize(sz(S)), cum.resize(sz(S)+1);
        
        pows[0] = ipows[0] = {1,1};
        FOR(i,1,sz(S)) pows[i] = pows[i-1]*base, ipows[i] = ipows[i-1]*invbase;
        F0R(i,sz(S)) cum[i+1] = cum[i]+pows[i]*(int)(S[i]-'a'+1);
    }
    
    pi get(int l, int r) {  return ipows[l]*(cum[r+1]-cum[l]); }
    
    int lcp(hsh& b) {
        int lo = 0, hi = min(sz(S),sz(b.S));
        while (lo < hi) {
            int mid = (lo+hi+1)/2;
            if (cum[mid] == b.cum[mid]) lo = mid;
            else hi = mid-1;
        }
        return lo;
    }
};
