/*
ID: bqi3431
PROG: clocks
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

using namespace std;
 
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pi;

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

vi ans;

int add[9][9] = {
	{1,1,0,1,1,0,0,0,0},
	{1,1,1,0,0,0,0,0,0},
	{0,1,1,0,1,1,0,0,0},
	{1,0,0,1,0,0,1,0,0},
	{0,1,0,1,1,1,0,1,0},
	{0,0,1,0,0,1,0,0,1},
	{0,0,0,1,1,0,1,1,0},
	{0,0,0,0,0,0,1,1,1},
	{0,0,0,0,1,1,0,1,1}
};

int ori1[9], cur[9];

void search(int temp) {
	if (temp<9) {
		F0R(i,4) {
			search(temp+1);
			cur[temp] ++;
		}
		cur[temp] = 0;
		return;
	}	
	int sum = 0, sum1 = 0, ori[9];
	F0R(i,9) ori[i] = ori1[i];
	F0R(i,9) F0R(k,9) {
		ori[k] += cur[i]*add[i][k];
		ori[k] %= 4;
	}
	F0R(i,9) {
		sum += ori[i];
		sum1 += cur[i];
	}
	/*if (sum == 0) {
		F0R(i,9) cout << ori[i] << " ";
		cout << sum1 << " " << sum1 << "\n";
	}*/
	if (sum == 0) {
		if (sum1<ans.size()) {
			vi z;
			F0R(i,9) F0R(j,cur[i]) z.pb(i+1);
			ans = z;
		} else if (sum1 == ans.size()) {
			vi z;
			F0R(i,9) F0R(j,cur[i]) z.pb(i+1);
			if (z<ans) ans = z;
		}
	}
}

int main() {
	ifstream cin ("clocks.in");
	ofstream cout ("clocks.out");
	F0R(i,36) ans.pb(i);
	F0R(i,9) {
		int k; cin >> k;
		ori1[i] = (k/3) % 4;
	}
	search(0);
	F0R(i,ans.size()) {
		cout << ans[i];
		if (i != ans.size()-1) cout << " ";
	}
	cout << "\n";
}
