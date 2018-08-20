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
typedef tree<pi,null_type,less<pi>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;

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

int n, q1[100000], q2[100000];
vi h;
ordered_set s;

int main() {
	ifstream cin ("bphoto.in");
	ofstream cout ("bphoto.out");
	cin >> n; h.resize(n);
	F0R(i,n) cin >> h[i];
	F0R(i,n) {
		q1[i] = i - s.order_of_key({h[i]+1,0});
		s.insert({h[i],i});
	}
	s.clear();
	for (int i = n-1; i >= 0; --i) {
		q2[i] = n-1-i-s.order_of_key({h[i]+1,0});
		s.insert({h[i],i});
	}
	int ans = 0;
	F0R(i,n) if (2*q1[i]<q2[i] || q1[i]>2*q2[i]) ans++;
	cout << ans;
}
