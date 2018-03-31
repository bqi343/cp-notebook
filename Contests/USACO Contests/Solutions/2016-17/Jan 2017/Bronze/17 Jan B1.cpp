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

map<string,int> cur;
vector<pair<int,string>> k;

int main() {
	ifstream cin ("notlast.in");
	ofstream cout ("notlast.out");
	int n; cin >> n;
	cur["Bessie"] = cur["Maggie"] = cur["Elsie"] = cur["Henrietta"] = cur["Gertie"] = cur["Daisy"] = cur["Annabelle"] = 0;
	F0R(i,n) {
		string s; int num; cin >> s >> num;
		cur[s] += num;
	}
	for (auto a: cur) k.pb(mp(a.s,a.f));
	sort(k.begin(),k.end());
	int ind = 0;
	while (ind<7 && k[ind].f == k[0].f) ind++;
	if (ind == 7 || (ind<6 && k[ind+1].f == k[ind].f)) {
		cout << "Tie";
		return 0;
	}
	cout << k[ind].s;
}
