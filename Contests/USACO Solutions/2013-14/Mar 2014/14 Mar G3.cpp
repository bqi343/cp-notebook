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

int N;
vi all;

bool test(vi x) {
	int sum = 0;
	while (1) {
		while (x.size() && x[0] == 0) x.erase(x.begin());
		if (x.size() == 0) return 1;
		if (x[x.size()-1] >= x.size()) return 0;
		int temp = x[x.size()-1];
		x.erase(x.begin()+x.size()-1);
		FOR(i,x.size()-temp,x.size()) x[i]--;
		sort(x.begin(),x.end());
	}
}


int main() {
	ifstream cin ("fcount.in");
	ofstream cout ("fcount.out");
	cin >> N; all.resize(N+1);
	F0R(i,N+1) cin >> all[i];
	vi ans;
	F0R(i,N+1) {
		vi temp = all;
		temp.erase(temp.begin()+i);
		if (test(temp)) ans.pb(i+1);
	}
	cout << ans.size() << "\n";
	for (int i: ans) cout << i << "\n";
}
