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

ifstream cin ("cownomics.in");
ofstream cout ("cownomics.out");

int N,M, ans=999999; 
vector<string> v1, v2;

bool test(int low, int high) {
	set<string> s1;
	for (string x: v1) s1.insert(x.substr(low,high-low+1));
	for (string x: v2) if (s1.find(x.substr(low,high-low+1)) != s1.end()) return 0;
	return 1;
}

int main() {
	cin >> N >> M;
	F0R(i,N) {
		string x; cin >> x;
		v1.pb(x);
	}
	F0R(i,N) {
		string x; cin >> x;
		v2.pb(x);
	}
	int low = 0, high = 0;
	while (low<M) {
		high = max(high,low);
		while (high < M && !test(low,high)) high++;
		if (high == M) break;
		ans = min(ans,high-low+1);
		low++;
	}
	cout << ans;
}
