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
//#include <ext/pb_ds/assoc_container.hpp> 
//#include <ext/pb_ds/tree_policy.hpp>

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

vi best = {-1},a,b, ok[100001];
int posi[100001];

int main() {
	ifstream cin ("nocross.in");
	ofstream cout ("nocross.out");
	int N; cin >> N; a.resize(N), b.resize(N);
	F0R(i,N) {
		cin >> a[i];
		posi[a[i]] = i;
	}
	F0R(i,N) {
		cin >> b[i];
		FOR(j,b[i]-4,b[i]+5) 
			if (1 <= j && j <= N) 
				ok[posi[j]].pb(i);
	}
	F0R(i,N) sort(ok[i].begin(),ok[i].end());
	
	F0R(i,N) {
		// modify best
		F0Rd(j,best.size()) {
			if (ok[i][ok[i].size()-1] <= best[j]) continue;
			int co = ok[i].size()-1;
			while (co && ok[i][co-1] > best[j]) co--;
			if (j != best.size()-1) best[j+1] = min(best[j+1],ok[i][co]);
			else best.pb(ok[i][co]);
		}
	}
	cout << best.size()-1;
}
