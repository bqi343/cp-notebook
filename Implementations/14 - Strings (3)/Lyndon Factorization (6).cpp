/**
 * Description: Compute Lyndon Factorization in O(n)
 * Source: https://cp-algorithms.com/string/lyndon_factorization.html
 * Verification: https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=660
 */
 
vector<string> duval(string const& s) {
    int n = sz(s);
    vector<string> factorization;
    for (int i = 0; i < n; ) {
        int j = i + 1, k = i;
        for (;j < n && s[k] <= s[j]; ++j) {
            if (s[k] < s[j]) k = i;
            else k++;
        }
        while (i <= k) {
            factorization.pb(s.substr(i, j - k));
            i += j - k;
        }
    }
    return factorization;
}