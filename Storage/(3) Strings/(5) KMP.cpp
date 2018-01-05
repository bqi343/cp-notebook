// note that Z algorithm can be used in place of this
// have not used in actual contest

vi kmp_table(string W) { 
    vi T(W.length()+1); T[0] = -1;
    int pos = 1; // the current position we are computing in T
    int cnd = 0; // the zero-based index in W of the next character of the current candidate substring

    while (pos < (int)W.length()) {
        if (W[pos] == W[cnd]) T[pos] = T[cnd];
        else {
            T[pos] = cnd; cnd = T[cnd];
            while (cnd >= 0 && W[pos] != W[cnd]) cnd = T[cnd];
        }
        pos++, cnd++;
    }
    T[pos] = cnd;
    return T;
}

vi kmp_search(string S, string W) {
    int m = 0; // beginning of the current match in S
    int i = 0; // position of the current character in W
    vi T = kmp_table(W);
    vi ans;
    
    while (m+i < (int)S.length()) 
        if (W[i] == S[m+i]) {
            i++;
            if (i == (int)W.length()) {
                ans.pb(m);
                m = m+i-T[i], i = T[i]; 
            }
        } else {
            if (T[i] > -1) m = m+i-T[i], i = T[i];
            else m = m+i+1, i = 0;
        }
    return ans;
}

int main() {
	ios_base::sync_with_stdio(0);cin.tie(0);
	vi x = kmp_search("abacaba","aba");
	cout << x.size() << "\n";
	for (int i: x) cout << i << " ";
}

// read!
// ll vs. int!