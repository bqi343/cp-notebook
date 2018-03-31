/*
ID: bqi3431
PROG: milk4
LANG: C++11
*/

//#include<iostream>
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

int Q,P, best = MOD;
vi pail, emp, best1;

void dfs(int num, vi cr, bitset<20001> cur) {
	if (cr.size() >= best) return;
	/*cout << num << " " << cr.size() << "\n";
	for (int i: cr) cout << i << " ";
	cout << "\n\n";*/
	
	if (num == 0) cur[0] = 1;
	else {
		int pw = 1;
		for( ; (pail[num] * pw) <= Q; pw <<= 1) cur |= cur << (pail[num] * pw);
	}
	
	if (cur[Q] == 1) {
		best = cr.size();
		best1 = cr;
	} else {
		FOR(i,num+1,P+1) {
			vi cr1 = cr;
			bitset<20001> cur1 = cur;
			cr1.pb(pail[i]);
			dfs(i,cr1,cur1);
		}
	}
}

int main() {
	ifstream cin("milk4.in");
	ofstream cout ("milk4.out");
	cin >> Q >> P; pail.resize(P+1);
	FOR(i,1,P+1) cin >> pail[i];
	sort(pail.begin(),pail.end());
	
	bitset<20001> z;
	dfs(0,emp,z);
	cout << best;
	for (int i: best1) cout << " " << i;
	cout << "\n";
}
