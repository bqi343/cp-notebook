/*
ID: bqi3431
PROG: sprime
LANG: C++11
*/

//#include <iostream>
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

vi ans,primes;
int n;
	ifstream cin ("sprime.in");
	ofstream cout ("sprime.out");

void genprimes() {
	FOR(i,2,100001) {
		bool f = 1;
		for (int j: primes) {
			if (i%j == 0) {
				f = 0;
				break;
			}
			if (j*j>i) break;
		}
		if (f) primes.pb(i);
	}
}

int isprime(int k) {
	if (k <= 1) return 0;
	for (int i: primes) {
		if (k % i == 0 && k != i) return 0;
		if (i*i>k) return 1;
	}
	return 1;
}

void search(int cur, int len) {
	if (len == n) {
		cout << cur << "\n";
		return;
	}
	F0R(i,10) {
		int cur1 = 10*cur+i;
		if (isprime(cur1)) search(cur1,len+1);
	}
}

int main() {
	cin >> n;
	genprimes();
	search(0,0);
}
