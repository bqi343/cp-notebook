/*
ID: bqi3431
PROG: palsquare
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

int b;

bool ispal (string s) {
	F0R(i,s.length()/2) if (s[i] != s[s.length()-1-i]) return 0;
	return 1;
}

string con(int num) {
	string ans = "";
	while (num) {
		int rem = (num%b);
		if (rem<10) ans += char(rem+'0');
		else ans += char(rem-10+'A');
		num /= b;
	}
	reverse(ans.begin(),ans.end());
	return ans;
}	

int main() {
	//ifstream cin ("palsquare.in");
	//ofstream cout ("palsquare.out");
	cin >> b;
	FOR(i,1,301) if (ispal(con(i*i))) {
		cout << con(i) << " " << con(i*i) << "\n";
	}
}
