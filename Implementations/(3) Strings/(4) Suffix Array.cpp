/**
* Source: SuprDewd CP Course
* Task: https://open.kattis.com/problems/suffixsorting
*/

struct suffix_array {
    int N;
    vector<vi> P;
    vector<pair<pii,int>> L;
    vi idx;
    string str;
    
    suffix_array(string _str) {
        str = _str; N = str.length();
        P.pb(vi(N)); L.resize(N);
        F0R(i,N) P[0][i] = str[i];
        
        for (int stp = 1, cnt = 1; cnt < N; stp ++, cnt *= 2) {
            P.pb(vi(N));
            F0R(i,N) L[i] = {{P[stp-1][i],i+cnt < N ? P[stp-1][i+cnt] : -1},i};
            sort(L.begin(),L.end());
            F0R(i,N) {
                if (i && L[i].f == L[i-1].f) P[stp][L[i].s] = P[stp][L[i-1].s];
                else P[stp][L[i].s] = i;
            }
        }
        
        idx.resize(N);
        F0R(i,P[P.size()-1].size()) idx[P[P.size()-1][i]] = i;
    }
    
    int lcp(int x, int y) {
        int res = 0;
        if (x == y) return N-x;
        for (int k = P.size() - 1; k >= 0 && x < N && y < N; k--) {
            if (P[k][x] == P[k][y]) {
                x += 1 << k;
                y += 1 << k;
                res += 1 << k;
            }
        }
        return res;
    }
};

int main() {
	string s;
	while (getline(cin,s)) {
	    if (s[s.length()-1] == '\r') s.erase(s.end()-1);
	    suffix_array sa = suffix_array(s);
	    int z; cin >> z;
	    F0R(i,z) {
	        int x; cin >> x;
	        cout << sa.idx[x] << " ";
	    }
	    cout << "\n";
	    getline(cin,s);
	}
}
