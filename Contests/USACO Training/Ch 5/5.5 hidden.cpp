/*
ID: bqi3431
PROG: hidden
LANG: C++11
*/

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

int main() {
	ifstream cin ("hidden.in");
	ofstream cout ("hidden.out");
	int L; cin >> L;
	string s,t;
	while (cin >> t) s += t;
	s += s;
	bool posi[100000];
	F0R(i,L) posi[i] = 1;
	FOR(i,1,min(L,100)) {
		int cur = 0;
		for (int j = 2*L-1-i; j >= 0; j--) {
			if (s[j] != s[j+i]) cur = 0;
			else cur++;
			if (j+i < L) {
				if (cur+j+i == 2*L) posi[j+i] = 0;
				else if (s[j+cur]>s[j+i+cur]) posi[j] = 0;
				else posi[j+i] = 0;
			}
		}
		/*F0R(i,7) cout << posi[i] << " ";
		cout << "\n";*/
	}
	int cnum = 0;
	string ans = s.substr(0,L);
	FOR(i,1,L) if (posi[i]) {
		string temp = s.substr(i,L-i)+s.substr(0,i);
		if (temp<ans) {
			cnum = i;
			ans = temp;
		}
	}
	cout << cnum << "\n";
}
