#include<iostream>
#include<fstream>
#include<set>
#include<map>
#include<string>
#include<algorithm>
#include<vector>

using namespace std;
 
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pi;

#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
 
#define mp make_pair
#define pb push_back
#define f first
#define s second

const int MOD = 1000000007;

string s, ans;
ll N, bas = 241, invbas = 406639007, po[100000];
int stor[100001][500];
map<int,set<ll>> ma;
map<int,int> co;

ll hsh(string x) {
	ll ans = 0;
	F0R(i,x.length()) ans = (ans+(x[i]-'a'+1)*po[i]) % MOD;
	return ans;
}

void get(int ind, int len) {
	if (ans.length()) stor[ans.length()][ind] = stor[ans.length()-1][ind];
	if (len >= ans.length()) stor[ans.length()][ind] = 
		(stor[ans.length()][ind] + po[ans.length()-1]*(ans[ans.length()-1]-'a'+1)) % MOD;
	else {
		stor[ans.length()][ind] = (stor[ans.length()][ind]+po[len]*(ans[ans.length()-1]-'a'+1)) % MOD;
		stor[ans.length()][ind] = ((ll)stor[ans.length()][ind]+MOD-(ans[ans.length()-len-1]-'a'+1)) % MOD;
		stor[ans.length()][ind] = (stor[ans.length()][ind] * invbas) % MOD;
	}
}

bool comp (string a, string b) {
	return a.length()<b.length();
}

void init() {
	ifstream cin ("censor.in");
	cin >> s >> N; 
	po[0] = 1;
	FOR(i,1,100000) po[i] = (bas*po[i-1]) % MOD;
	F0R(i,N) {
		string t; cin >> t;
		ma[t.length()].insert(hsh(t));
	}
	int cur = 0;
	for (auto a: ma) co[a.f] = cur++;
}

int main() {
	ofstream cout ("censor.out");
	init();
	for (char i: s) {
		ans += i;
		for (auto j: co) {
			get(j.s,j.f);
			if (ma[j.f].find(stor[ans.length()][j.s]) != ma[j.f].end()) {
				ans.erase(ans.length()-j.f,j.f);
				break;
			}
		}
	}
	cout << ans;
}
