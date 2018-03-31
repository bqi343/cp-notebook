/*
ID: bqi3431
PROG: namenum
LANG: C++11
*/

#include <iostream>
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

int d[26] = {2,2,2,3,3,3,4,4,4,5,5,5,6,6,6,7,7,7,7,8,8,8,9,9,9,9};

string con(string s) {
	string t = "";
	F0R(i,s.length()) t += char(d[s[i]-'A']+'0');
	return t;
}

int main() {
	cout << con("KRISTOPHER");
	/*ifstream cin ("namenum.in");
	ifstream fin ("dict.txt");
	ofstream cout ("namenum.out");
	int c = 0;
	string s,s1; cin >> s;
	while (fin >> s1) if (con(s1) == s) cout << s1 << "\n", c++;
	if (c == 0) cout << "NONE\n";*/
}
