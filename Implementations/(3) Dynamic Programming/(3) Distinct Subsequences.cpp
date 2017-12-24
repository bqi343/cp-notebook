/**
* Description: DP eliminates overcounting
*/

int distinct(string S) {
    vi tot(26);
    int ans = 1;
    for (char c: S) {
        int t = (ans-tot[c-'A']+MOD)%MOD;
        tot[c-'A'] = (tot[c-'A']+t)%MOD;
        ans = (ans+t)%MOD;
    }
    return ans;
}