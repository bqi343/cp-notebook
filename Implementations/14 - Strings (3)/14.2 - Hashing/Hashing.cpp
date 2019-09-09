/**
 * Description: Pairs reduce frequency of collision
 * Source: mostly own +
    * https://codeforces.com/contest/1207/submission/59309672
 * Verification: Dec 17 Plat 1, CF Check Transcription
 */

using namespace pairOp;

uniform_int_distribution<int> MULT_DIST(0.1 * MOD, 0.9 * MOD); // not too close to ends
const pmi base = {MULT_DIST(rng),MULT_DIST(rng)};
const pmi ibase = {1/base.f,1/base.s};

struct hsh {
    string S; 
    vpmi pows, ipows, cum;
    
    void init(string _S) {
        S = _S; pows.rsz(sz(S)), ipows.rsz(sz(S)), cum.rsz(sz(S)+1);
        pows[0] = ipows[0] = {1,1};
        FOR(i,1,sz(S)) pows[i] = pows[i-1]*base, ipows[i] = ipows[i-1]*ibase;
        F0R(i,sz(S)) cum[i+1] = cum[i]+pows[i]*(S[i]-'a'+1);
    }
    
    pmi get(int l, int r) {  return ipows[l]*(cum[r+1]-cum[l]); }
    
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

// hsh H("ababab"); F0R(i,6) FOR(j,i,6) ps(i,j,H.get(i,j));
