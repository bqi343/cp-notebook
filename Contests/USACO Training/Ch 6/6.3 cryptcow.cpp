/*
ID: bqi3431
PROG: cryptcow
LANG: C++11
*/

#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;
 
typedef vector<int> vi;
typedef long long ll;

#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)
 
#define mp make_pair
#define pb push_back

int MOD = 1000000007;

string f = "Begin the Escape execution at the Break of Dawn", g;
string fin1, g1;
char nex1;
unordered_set<ll> hashed;
int asc[130], op = 0;

ll hsh(string s) {
	ll cur = 1, z = 0;
	for (char i: s) {
		z = (z+(ll)i*cur) % MOD;
		cur = (cur*200) % MOD;
	}
	return z;
}

int testok() {
	for (char a: f) asc[a-' ']++;
	for (char a: g) asc[a-' '] --;
	F0R(i,130) if (asc[i] != 0 && i != ('C'-' ') && i != ('W'-' ') && i != ('O'-' ')) return -1;
	if (asc['C'-' '] != asc['O'-' '] || asc['O'-' '] != asc['W'-' ']) return -1;
	return -asc['O'-' '];
}

void computeLPSArray(string pat, int M, int *lps) {
    int len = 0, i = 1; lps[0] = 0;
    while (i < M) {
        if (pat[i] == pat[len]) lps[i++] = ++len;
        else {
            if (len != 0) len = lps[len-1];
            else lps[i++] = 0;
        }
    }
}

vi KMPSearch(string pat, string txt) {
	vi ans;
    int M = pat.length(), N = txt.length();
    int lps[M];
    computeLPSArray(pat, M, lps);
 
    int i = 0, j = 0;  // index for pat[]
    while (i < N) {
        if (pat[j] == txt[i]) j++, i++;
        if (j == M) {
        	ans.pb(i-j);
        	if (ans.size()>1) return ans;
            j = lps[j-1];
        } else if (i < N && pat[j] != txt[i]) {
            if (j != 0) j = lps[j-1];
            else i++;
        }
    }
    return ans;
}
 
bool ok(string fin, string g, char nex) {
	string cur = "";
	F0R(i,g.length()+1) {
		if (i == g.length() || g[i] == 'O' || g[i] == 'C' || g[i] == 'W') {
			if (cur.length() <= 1) { cur = ""; continue;}
			vi x = KMPSearch(cur,fin);
			if (x.size() == 1) {
				 i -= cur.length();
				 g.erase(i,cur.length());
				 g.insert(i,string(1,nex));
				 i++;
				 fin.erase(x[0],cur.length());
				 fin.insert(x[0],string(1,nex));
				 nex ++; 
			} else if (x.size() == 0) return 0;
			cur = "";
		} else cur += g[i];
	}
	fin1 = fin, g1 = g, nex1 = nex;
	return 1;
}

bool search(string fin, string g, int left, char nex) {
	// if (left<2) cout << "XX\n" << fin << "\n" << g << "\n";
	if (hashed.find(hsh(g)) != hashed.end()) return 0;
	hashed.insert(hsh(g));
	int fir = -1, last = -1;
	F0R(i,g.length()) {
		if (g[i] == 'O' || g[i] == 'W') return 0;
		if (g[i] == 'C') {
			fir = i;
			break;
		}
		if (g[i] != fin[i]) return 0;
	}
	F0R(i,g.length()) {
		int j = g.length()-1-i;
		if (g[j] == 'O' || g[j] == 'C') return 0;
		if (g[j] == 'W') { last = i; break; }
		if (g[j] != fin[fin.length()-1-i]) return 0;
	}
	if (left == 0) return 1;
	g = g.substr(fir,g.length()-fir-last);
	fin = fin.substr(fir,fin.length()-fir-last);
	F0R(i,g.length()) if (g[i] == 'C')
		FOR(j,i+1,g.length()) if (g[j] == 'O')
			FOR(k,j+1,g.length()) if (g[k] == 'W') {
				string temp = g.substr(0,i)+g.substr(j+1,k-j-1)+g.substr(i+1,j-i-1)+g.substr(k+1,g.length()-k-1);
				if (ok(fin,temp,nex) && search(fin1,g1,left-1,nex1)) return 1; 
			}
	return 0;
}

int main() {
	//ifstream cin ("cryptcow.in");
	//ofstream cout ("cryptcow.out");
	getline(cin,g);
	int z = testok();
	if (z == -1 || !ok(f,g,'!')) {
		cout << "0 0\n";
		return 0;
	}
	bool k = search(fin1,g1,z,nex1);
	if (k == 0) cout << "0 0\n";
	else cout << "1 " << z << "\n";
}