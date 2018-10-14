/**
* Source: http://codeforces.com/blog/entry/12143
* Description: Calculates length of largest palindrome centered at each character of string
* Verification: http://www.spoj.com/problems/MSUBSTR/
*/

vi manacher(string s) {
    string s1 = "@";
    for (char c: s) s1 += c, s1 += "#";
    s1[s1.length()-1] = '&'; 
    
    vi ans(s1.length()-1);
    int lo = 0, hi = 0; 
    FOR(i,1,s1.length()-1) {
        if (i != 1) ans[i] = min(hi-i,ans[hi-i+lo]);
        while (s1[i-ans[i]-1] == s1[i+ans[i]+1]) ans[i] ++;
        if (i+ans[i] > hi) lo = i-ans[i], hi = i+ans[i];
    }
    
    ans.erase(ans.begin());
    F0R(i,sz(ans)) if ((i&1) == (ans[i]&1)) ans[i] ++; // adjust lengths
    return ans;
}

// vi v = manacher("abacaba"); cout << v;