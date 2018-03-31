// #include<iostream>
#include<fstream>
#include<vector>
#include<set>
#include<map>

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

int R,C,K,grid[750][750];
set<int> xco[526501];
map<int,int> conv[526501];
vi bit[526501];

void update(int col, int sz, int val) {
	while (sz < bit[col].size()) {
		bit[col][sz] = (bit[col][sz]+val) % MOD;
		sz += (sz & -sz);
	}
}

int query(int col, int sz) {
	int ans = 0;
	while (sz) {
		ans = (ans+bit[col][sz]) % MOD;
		sz -= (sz & -sz);
	}
	return ans;
}

void init() {
	ifstream cin ("hopscotch.in");
	cin >> R >> C >> K;
	F0R(i,R) F0R(j,C) {
		cin >> grid[i][j];
		if (j) xco[grid[i][j]].insert(j);
	}
	F0R(i,751) bit[0].pb(0);
	FOR(i,1,526501) {
		bit[i].pb(0);
		int cur = 0;
		for (int j: xco[i]) {
			bit[i].pb(0);
			conv[i][j] = ++cur;
		}
	}
}

int main() {
	ofstream cout ("hopscotch.out");
	init();
	F0Rd(i,R) F0R(j,C) {
		ll ans = 0;
		if (i == R-1 && j == C-1) ans = 1;
		else {
			ans = (query(0,C-1)-query(0,j)) % MOD;
			ans = (ans-query(grid[i][j],bit[grid[i][j]].size()-1)) % MOD;
			ans = (ans+query(grid[i][j],conv[grid[i][j]][j])) % MOD;
			while (ans<0) ans += MOD;
		}
		if (j != 0) {
			update(grid[i][j],conv[grid[i][j]][j],ans);
			update(0,j,ans);
		}
		if (i == 0 && j == 0) {
			cout << ans;
			return 0;
		}
	}
}
