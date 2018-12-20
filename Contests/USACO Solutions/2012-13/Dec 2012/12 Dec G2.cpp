// #include<iostream>
#include<fstream>
#include<set>
#include<map>
#include<unordered_map>
#include<cmath>
#include<cstring>
#include<string>
#include<bitset>
#include<algorithm>
#include<vector>

using namespace std;
//using namespace __gnu_pbds;
 
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pi;
//typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;

#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
 
#define mp make_pair
#define pb push_back
#define f first
#define s second
#define lb lower_bound
#define ub upper_bound

const int MOD = 1000000007;
double PI = 4*atan(1);

ifstream cin ("first.in");
ofstream cout ("first.out");

int t[300001][26], nex = 1, N;
vector<string> v[300001], ans;
map<string,int> val;
bitset<26> fi[300001][26];

void insert(string s) {
	int cur = 0;
	for (char c: s) {
		if (t[cur][c-'a'] == 0) t[cur][c-'a'] = nex++;
		cur = t[cur][c-'a'];
	}
	v[cur].pb(s);
}

void dfs(int cur) {
	for (string s: v[cur]) ans.pb(s);
	if (v[cur].size()) return;
	F0R(i,26) if (t[cur][i]) {
		bool f = 0;
		F0R(j,26) if (t[cur][j]>0 && fi[cur][j][i]) {
			f = 1;
			break;
		}
		if (f) continue;
		F0R(j,26) fi[t[cur][i]][j] = fi[cur][j];
		F0R(j,26) if (j != i && t[cur][j]>0) {
			fi[t[cur][i]][i][j] = 1;
		}
		F0R(a,26) F0R(b,26) 
			if (fi[t[cur][i]][b][a]) 
				fi[t[cur][i]][b] |= fi[t[cur][i]][a];
		dfs(t[cur][i]);
	}
}

bool comp (string a, string b) {
	return (val[a]<val[b]);
}

int main() {
	cin >> N;
	F0R(i,N) {
		string s; cin >> s;
		val[s] = i;
		insert(s);
	}
	dfs(0);
	cout << ans.size() << "\n";
	sort(ans.begin(),ans.end(),comp);
	for (string s: ans) cout << s << "\n";
}
