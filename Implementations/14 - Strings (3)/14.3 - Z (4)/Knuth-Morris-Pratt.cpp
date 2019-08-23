/**
 * Source: Own
 * Description: f[i] equals the length of the longest proper suffix of the i-th prefix of s
    * that is a prefix of s
 * Verification: https://open.kattis.com/problems/stringmatching
 */

vi kmp(string s) {
    int n = sz(s); vi f(n+1); f[0] = -1;
    FOR(i,1,n+1) {
        f[i] = f[i-1];
        while (f[i] != -1 && s[f[i]] != s[i-1]) f[i] = f[f[i]];
        f[i] ++;
    }
    return f;
}

vi getOc(string a, string b) { // find occurrences of a in b
    vi f = kmp(a), ret;
    int cur = 0;
    F0R(i,sz(b)) {
        while (cur != -1 && a[cur] != b[i]) cur = f[cur];
        cur ++; if (cur == sz(a)) ret.pb(i-sz(a)+1);
    }
    return ret;
}
