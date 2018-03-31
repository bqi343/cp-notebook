// #include <iostream>
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

int ans = 0,n;
pi mov[100];

void test(vi x) {
	int bet[4][4],cur=0;
	F0R(i,4) F0R(j,4) bet[i][j] = 0;
	bet[x[0]][x[1]] = 1;
	bet[x[1]][x[2]] = 1;
	bet[x[2]][x[0]] = 1;
	F0R(i,n) if (bet[mov[i].f][mov[i].s]) cur++;
	ans = max(ans,cur);
}

int main() {
	ifstream cin ("hps.in");
	ofstream cout ("hps.out");
	cin >> n;
	F0R(i,n) cin >> mov[i].f >> mov[i].s;
	test({1,3,2});
	test({1,2,3});
	test({2,1,3});
	test({2,3,1});
	test({3,2,1});
	test({3,1,2});
	cout << ans;
}
