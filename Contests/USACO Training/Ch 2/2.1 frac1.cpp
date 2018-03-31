/*
ID: bqi3431
PROG: frac1
LANG: C++11
*/

//#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
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

ifstream cin ("frac1.in");
ofstream cout ("frac1.out");

bool comp(pi a, pi b) {
	return (a.f*b.s<a.s*b.f);	
}

vector<pi> k;

int main() {
	int N; cin >> N;
	F0R(i,N+1) FOR(j,i,N+1) if (__gcd(i,j) == 1) k.pb({i,j});
	sort(k.begin(),k.end(),comp);
	for (auto a: k) cout << a.f << "/" << a.s << "\n";
}
