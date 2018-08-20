#include<algorithm>
#include<fstream>
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
#define sz size
 
const int MOD = 1000000007;

bool comp(pi a, pi b) {
	if (a.s<b.s) return true;
	else if (a.s == b.s) return a.f<b.f;
	return false;
}

int main() {
	ifstream cin ("reduce.in");
	ofstream cout ("reduce.out");
	int N, ans = 2*MOD;
	cin >> N;
	vector<pi> x, y, pos;
	
	F0R(i,N) {
		pi k;
		cin >> k.f >> k.s;
		x.pb(k), y.pb(k);
	}
	
	sort(x.b(),x.e());
	sort(y.b(), y.e(), comp);
	
	F0R(i,3) {
		pos.pb(x[i]);
		pos.pb(x[N-1-i]);
		pos.pb(y[i]);
		pos.pb(y[N-1-i]);
	}
	
	F0R(i,pos.size()) {
		FOR(j,i+1,pos.size()) {
			FOR(k,j+1,pos.size()) {
				if (pos[i] != pos[j] && pos[j] != pos[k] && pos[i] != pos[k]) {
					int vertl = 0;
					while (y[vertl] == pos[i] || y[vertl] == pos[j] || y[vertl] == pos[k]) vertl ++;
					int verth = N-1;
					while (y[verth] == pos[i] || y[verth] == pos[j] || y[verth] == pos[k]) verth --;
					int horl = 0;
					while (x[horl] == pos[i] || x[horl] == pos[j] || x[horl] == pos[k]) horl ++;
					int horh = N-1;
					while (x[horh] == pos[i] || x[horh] == pos[j] || x[horh] == pos[k]) horh --;
					ans = min(ans, (x[horh].f-x[horl].f)*(y[verth].s-y[vertl].s));
					// cout << horh << " " << horl << " " << verth << " " << vertl << endl;
				}
			}
		}
	}
	cout << ans;
	return 0;
}
