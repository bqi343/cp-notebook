#include<iostream>
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

//ifstream cin ("photo.in");
//ofstream cout ("photo.out");

map<int,int> po[5], co;
int N, ans[20000];

bool comp(int a, int b) {
	int cur = 0;
	F0R(i,5) if (po[i][a]<po[i][b]) cur++;
	return (cur/3);
}

int main() {
	cin >> N;
	vi ans;
	F0R(i,5) {
		F0R(j,N) {
			int k; cin >> k;
			po[i][k] = j;
			if (i == 0) ans.pb(k);
		}
	}
	sort(ans.begin(),ans.end(),comp);
	for (int i: ans) cout << i << "\n";
}
