/**
 * Description: DP eliminates overcounting
 * Verification: ? https://cses.fi/problemset/task/1149/
 */

mi distinct(string S) {
    vmi tot(26); mi ans = 1;
    for (char c: S) {
        mi t = ans-tot[c-'a'];
        tot[c-'a'] += t, ans += t;
    }
    return ans;
}
