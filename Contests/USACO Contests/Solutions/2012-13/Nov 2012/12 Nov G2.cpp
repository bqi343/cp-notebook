//#include<iostream>
#include<fstream>
#include<set>
#include<map>
#include<stack>
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

ifstream cin ("cbs.in");
ofstream cout ("cbs.out");

int K,N, cum[10][50001], lst[10][50001], ans = 0;
map<vi,vi> rec;

int main() {
	cin >> K >> N;
	F0R(i,K) {
		string s; cin >> s;
		F0R(j,N) {
			if (s[j] == '(') cum[i][j+1] ++;
			else cum[i][j+1] --;
			cum[i][j+1] += cum[i][j];
		}
	}
	F0R(i,K) {
		stack<int> todo;
		F0R(j,N+1) {
			lst[i][j] = -MOD;
			if (j == 0) {
				todo.push(0);
				continue;
			}
			if (cum[i][j]>cum[i][j-1]) {
				lst[i][j] = j-1;
				todo.push(j);
				continue;
			}
			while (todo.size() && cum[i][j] <= cum[i][todo.top()]) todo.pop();
			if (todo.size()) lst[i][j] = todo.top();
			todo.push(j);
		}
	}
	F0R(j,N+1) {
		vi temp;
		int mx = -MOD;
		F0R(i,K) {
			temp.pb(cum[i][j]);
			mx = max(mx,lst[i][j]);
		}
		for (int a: rec[temp]) if (a>mx) ans++;
		rec[temp].pb(j);
	}
	cout << ans;
}
