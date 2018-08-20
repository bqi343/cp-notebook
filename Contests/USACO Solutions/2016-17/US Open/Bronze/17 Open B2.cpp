// #include<iostream>
#include<fstream>
#include<vector>
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

ifstream cin("cownomics.in");
ofstream cout ("cownomics.out");

int n,m,ans;
map<char,int> x;
vector<string> v1, v2;

int main() {
	cin >> n >> m; v1.resize(n), v2.resize(n);
	x['A'] = 0;
	x['C'] = 1;
	x['G'] = 2;
	x['T'] = 3;
	F0R(i,n) cin >> v1[i];
	F0R(i,n) cin >> v2[i];
	F0R(i,m) {
		int a=0,b=0;
		F0R(j,n) a |= (1<<x[v1[j][i]]), b |= (1<<x[v2[j][i]]);
		if ((a&b) == 0) ans++;
	}
	cout << ans;
}
