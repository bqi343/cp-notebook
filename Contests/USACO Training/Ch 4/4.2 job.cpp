/*
ID: bqi3431
PROG: job
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

vi A,B, times;
int N,M1,M2; 

bool posi(int mid) {
	bool done[1000];
	F0R(i,N) done[i] = 0;
	for (int i: B) {
		int last = mid-i, c = times.size()-1;
		while (c >= 0) {
			while (c >= 0 && (times[c]>last || done[c])) c--;
			if (c < 0) break;
			done[c] = 1;
			last -= i;
		}
	}
	F0R(i,N) if (done[i] == 0) return 0;
	return 1;
}

int main() {
	ifstream cin ("job.in");
	ofstream cout ("job.out");
	cin >> N >> M1 >> M2;
	A.resize(M1), B.resize(M2);
	
	F0R(i,M1) cin >> A[i];
	F0R(i,M2) cin >> B[i];
	sort(B.begin(),B.end());
	
	int lb = 1, ub = 20000;
	while (lb<ub) {
		int mid = (lb+ub)/2;
		int cur = 0;
		for (int i: A) cur += mid/i;
		if (cur >= N) ub = mid;
		else lb = mid+1;
	}
	cout << lb << " ";
	
	F0R(i,M1) FOR(j,1,lb/A[i]+1) times.pb(j*A[i]);
	sort(times.begin(),times.end());
	while (times.size()>N) times.erase(times.end()-1);
	
	lb = 1, ub = 40000;
	while (lb<ub) {
		int mid = (lb+ub)/2;
		// cout << mid << " " << posi(mid) << "\n";
		if (posi(mid)) ub = mid;
		else lb = mid+1;
	}
	cout << lb << "\n";
}
