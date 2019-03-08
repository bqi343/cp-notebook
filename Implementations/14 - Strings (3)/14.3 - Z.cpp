/**
 * Source: http://codeforces.com/blog/entry/3107
 * Description: similar to KMP
 * Verification: POI 12 Template, https://codeforces.com/contest/1137/problem/B
 */

vi z(string s) {
    int N = sz(s); s += '#';
    vi ans(N); ans[0] = N; if (N == 1) return ans;
    while (s[1+ans[1]] == s[ans[1]]) ans[1] ++;
    int L = 1, R = ans[1];
    FOR(i,2,N) {
        if (i <= R) ans[i] = min(R-i+1,ans[i-L]);
        while (s[i+ans[i]] == s[ans[i]]) ans[i] ++;
        if (i+ans[i]-1 > R) L = i, R = i+ans[i]-1;
    }
    return ans;
}

vi getPrefix(string a, string b) { // find prefixes of a in b
    string s = a+"@"+b; 
    vi t = z(s);
    return vi(t.begin()+sz(a)+1,t.end());
}

// pr(z("abcababcabcaba"),getPrefix("abcab","uwetrabcerabcab"));
