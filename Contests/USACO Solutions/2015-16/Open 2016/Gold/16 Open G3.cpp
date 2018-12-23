#include<fstream>
#include<algorithm>

using namespace std;
 
#define ll long long
#define mp make_pair
#define pb push_back
#define pi pair <int, int>
#define vi vector<int>

#define FOR(i, a, b) for (int i=a; i<b; i++)
#define FORd(i, a, b) for (int i=a-1; i>=b; i--)
#define F0Rd(i, a) for (int i=a-1; i>=0; i--)
#define F0R(i, a) for (int i=0; i<a; i++)
 
#define f first
#define s second
#define b begin
#define e end
#define lb lower_bound
#define ub upper_bound

int main() {
	ifstream cin ("248.in");
	ofstream cout ("248.out");
	int n, ans = 0;
	vector<pi> sequence[60];
	cin >> n;
	F0R(i,n) {
		int x; cin >> x;
		sequence[x].pb(mp(i,i+1));
	}
	
	FOR(i,1,59) {
		int it = 0;
		if (sequence[i].size()) ans = i;
		sort(sequence[i].b(),sequence[i].e());
		F0R(j,sequence[i].size()) {
			while (sequence[i][it].f < sequence[i][j].s && it<sequence[i].size()) it++;
			if (it == sequence[i].size()) break;
			if (sequence[i][it].f == sequence[i][j].s) 
				sequence[i+1].pb(mp(sequence[i][j].f,sequence[i][it].s));
		}
	}
	
	cout << ans;
}
