//#include <iostream>
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

int N,T; 
vi dance;

int ok (int k) {
	int cind = 0, ctime = 0;
	multiset<int> cur;
	F0R(i,N) {
		if (cur.size() == k) {
			ctime = *cur.begin();
			cur.erase(cur.begin());
		} 
		cur.insert(dance[i]+ctime);
	}
	return *prev(cur.end());
}

int main() {
	ifstream cin ("cowdance.in");
	ofstream cout ("cowdance.out");
	cin >> N >> T;
	dance.resize(N);
	F0R(i,N) cin >> dance[i];
	int low = 1, high = N;
	while (low<high) {
		int mid = (low+high)/2;
		if (ok(mid) <= T) high = mid;
		else low = mid+1;
	}
	cout << low;
}
