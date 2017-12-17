/**
* Source: Wikipeddia
* unused
*/

int least_rotation(string S) {
    S += S;
    vi f = vi(S.length(),-1);
    int k = 0;       
    FOR(j,1,S.length()) {
        char sj = S[j];
        int i = f[j-k-1];
        while (i != -1 and sj != S[k+i+1]) {
            if (sj < S[k+i+1]) k = j-i-1;
            i = f[i];
        }
        if (sj != S[k+i+1]) {
            if (sj < S[k]) k = j;
            f[j-k] = -1;
        } else f[j-k] = i+1;
    }
    return k;
}
    
int main() {
	ios_base::sync_with_stdio(0);cin.tie(0);
	cout << least_rotation("cccaabbb");
}
