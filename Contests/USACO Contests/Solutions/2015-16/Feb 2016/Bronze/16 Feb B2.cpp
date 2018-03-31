//#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>

using namespace std;

typedef vector<int> vi;
typedef pair<int, int> pi;

#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)
#define f first
#define s second
#define pb push_back

int main() {
	ifstream cin ("cbarn.in");
	ofstream cout ("cbarn.out");
	int n, f = 1000000000; cin >> n;
	vi r(n); F0R(i,n) cin >> r[i];
	F0R(i,n) {
		int ans = 0;
		F0R(j,n) ans += j*r[j];
		r.pb(r[0]);
		r.erase(r.begin());
		f = min(f,ans);
	}
	cout << f;
}
