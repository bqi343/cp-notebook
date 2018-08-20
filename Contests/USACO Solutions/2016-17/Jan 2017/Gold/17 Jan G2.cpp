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

int b1[3][21][100000], n, k, ans=0; 
vector<char> x;

bool beat(int o1, char o2) {
	if (o1 == 0) { // H,P,S
		if (o2 == 'S') return 1;
		return 0;
	}
	if (o1 == 1) {
		if (o2 == 'H') return 1;
		return 0;
	}
	if (o2 == 'P') return 1;
	return 0;
}

int main() {
	ifstream cin ("hps.in");
	ofstream cout ("hps.out");
	cin >> n >> k; x.resize(n);
	F0R(i,n) cin >> x[i];
	F0R (i1,k+1) F0R(i2,n) {
		if (i2) {
			b1[0][i1][i2] = max(b1[0][i1][i2],b1[0][i1][i2-1]);
			if (i1) {
				b1[0][i1][i2] = max(b1[0][i1][i2],b1[1][i1-1][i2-1]);
				b1[0][i1][i2] = max(b1[0][i1][i2],b1[2][i1-1][i2-1]);
			}
		}
		b1[0][i1][i2] += beat(0,x[i2]);
		if (i2) {
			b1[1][i1][i2] = max(b1[1][i1][i2],b1[1][i1][i2-1]);
			if (i1) {
				b1[1][i1][i2] = max(b1[1][i1][i2],b1[0][i1-1][i2-1]);
				b1[1][i1][i2] = max(b1[1][i1][i2],b1[2][i1-1][i2-1]);
			}
		}
		b1[1][i1][i2] += beat(1,x[i2]);
		if (i2) {
			b1[2][i1][i2] = max(b1[2][i1][i2],b1[2][i1][i2-1]);
			if (i1) {
				b1[2][i1][i2] = max(b1[2][i1][i2],b1[0][i1-1][i2-1]);
				b1[2][i1][i2] = max(b1[2][i1][i2],b1[1][i1-1][i2-1]);
			}
		}
		b1[2][i1][i2] += beat(2,x[i2]);
		ans = max(ans,max(max(b1[1][i1][i2],b1[2][i1][i2]),b1[0][i1][i2]));
	}
	cout << ans;
}
