/*
ID: bqi3431
PROG: friday
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

int day = 1, mo = 1, year = 1900, w = 2, co[7];

int getdays() {
	if (mo == 2) {
		if (year % 4 == 0) {
			if (year % 100 == 0) {
				if (year % 400 == 0) return 29;
				return 28;
			}
			return 29;
		}
		return 28;
	}
	if (mo == 4 || mo == 6 || mo == 9 || mo == 11) return 30;
	return 31;
}

void advance() {
	day++;
	if (day>getdays()) {
		day = 1;
		mo++;
	}
	if (mo>12) {
		mo = 1;
		year++;
	}
	w = (w+1) % 7;
}

int main() {
	//ifstream cin ("friday.in");
	//ofstream cout ("friday.out");
	int N; cin >> N;
	while (year<1900+N) {
		if (day == 13) co[w] ++;
		advance();
	}
	F0R(i,7) cout << co[i] << " ";
}
