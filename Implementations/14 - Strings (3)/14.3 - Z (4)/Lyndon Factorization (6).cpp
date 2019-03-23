/**
 * Description: Compute Lyndon Factorization in O(n)
 * Source: https://cp-algorithms.com/string/lyndon_factorization.html
 * Verification: https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=660
 */

vector<string> duval(const string& s) {
    int n = sz(s); vector<string> factors;
    for (int i = 0; i < n; ) {
        int j = i + 1, k = i;
        for (; j < n && s[k] <= s[j]; j++) {
            if (s[k] < s[j]) k = i;
            else k ++;
        }
        for (; i <= k; i += j-k) factors.pb(s.substr(i, j - k));
    }
    return factors;
}

int minRotation(string s) { // get min index i such that cyclic shift starting at i is min rotation
    int n = sz(s); s += s;
    auto d = duval(s); int ind = 0, ans = 0;
    while (ans+sz(d[ind]) < n) ans += sz(d[ind++]);
    while (ind && d[ind] == d[ind-1]) ans -= sz(d[ind--]);
    return ans;
}
