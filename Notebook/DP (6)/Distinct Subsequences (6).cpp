/**
 * Description: DP eliminates overcounting
 * Source: Own
 * Verification: CSES String Removals
 	* https://cses.fi/problemset/task/1149/
 */

mi distinct(const string& S) {
    vmi tot(26); mi ans = 1; // tot[i] stands for number of distinct strings ending with character 'a'+i
    trav(c,S) tie(ans,tot[c-'a']) = mp(2*ans-tot[c-'a'],ans);
    return ans;
}
