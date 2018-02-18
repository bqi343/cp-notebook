/**
* Description: DP eliminates overcounting
* Verification: https://cses.fi/problemset/task/1149/
*/

int distinct(string S) {
    vi tot(26);
    int ans = 1;
    for (char c: S) {
        int t = (ans-tot[c-'a']+MOD)%MOD;
        tot[c-'a'] = (tot[c-'a']+t)%MOD;
        ans = (ans+t)%MOD;
    }
    return ans;
}
