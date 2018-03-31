/*
ID: bqi3431
PROG: gift1
LANG: C++11
*/

//#include <iostream>
#include <fstream>
#include <vector>
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;
 
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pi;
typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;

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

map<string,int> mon;
map<int,string> inp;

int main() {
	ifstream cin ("gift1.in");
	ofstream cout ("gift1.out");
	int nP; cin >> nP;
	F0R(i,nP) {
		string s; cin >> s;
		inp[i] = s;
	}
	F0R(i,nP) {
		string s; cin >> s;
		int m,n; cin >> m >> n;
		F0R(j,n) {
			string z; cin >> z;
			mon[z] += m/n;
		}
		mon[s] -= m;
		if (n != 0) mon[s] += (m%n);
	}
	F0R(i,nP) cout << inp[i] << " " << mon[inp[i]] << "\n";
}
