#include <bits/stdc++.h>
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
 
const int MOD = 1000000007;

void print(vector<pi> a) {
	F0R(i,a.size()) {
		cout << a[i].f << " " << a[i].s << "  ";
	}
	cout << endl;
}

int main() {
	// freopen("262144.in", "r", stdin);
  	// freopen("262144.out", "w", stdout);
	int n, ans = 0;
	vector<pi> seq[60];
	scanf("%d",&n);
	F0R(i,n) {
		int x;
		scanf("%d",&x);
		seq[x].pb(mp(i,i+1));
	}
	
	FOR(i,1,59) {
		int it = 0;
		if (seq[i].size()) ans = i;
		sort(seq[i].b(),seq[i].e());
		F0R(j,seq[i].size()) {
			while (seq[i][it].f < seq[i][j].s && it<seq[i].size()) it++;
			if (it == seq[i].sz()) break;
			if (seq[i][it].f == seq[i][j].s) {
				seq[i+1].pb(mp(seq[i][j].f,seq[i][it].s));
			}
		}
	}
	printf("%d",ans);
	return 0;
}
