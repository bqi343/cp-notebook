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

int N,M,mx,cow[100],cow1[100];
vi ans;
pi cur = {0,0}; // num, gang

int solve() {
	F0R(i,M) cow1[i] = cow[i];
	pi cur1 = cur;
	while (1) {
		int sum = 0;
		F0R(i,M) sum += cow1[i];
		if (sum == 0) break;
		pi best = {0,-1};
		FOR(j,1,M) if ((j != cur1.s || cur1.f == 0) && cow1[j] > best.f) best = {cow1[j],j};
		if (best.f == 0) best = {cow1[cur1.f],cur1.f};
		if (best.f == 0) best = {cow1[0],0};
		cow1[best.s] --;
		if (cur1.f == 0) cur1 = {1,best.s};
		else if (cur1.s == best.s) cur1.f ++;
		else cur1.f --;
	}
	if (cur1.s == 0) return cur1.f;
	return 0;
}

void dfs() {
	F0R(i,M) if (cow[i]>0) {
		cow[i] --;
		pi cur1 = cur;
		if (cur.f == 0) cur = {1,i};
		else if (cur.s == i) cur.f ++;
		else cur.f --;
		if (solve() == mx) {
			ans.pb(i+1);
			dfs();
			return;
		}
		cow[i] ++;
		cur = cur1;
	}
}

int main() {
	ifstream cin ("gangs.in");
	ofstream cout ("gangs.out");
	cin >> N >> M; 
	F0R(i,M) cin >> cow[i];
	mx = solve();
	if (mx <= 0) {
		cout << "NO";
		return 0;
	}
	dfs();
	cout << "YES\n" << mx << "\n";
	F0R(i,ans.size()) cout << ans[i] << "\n";
}
