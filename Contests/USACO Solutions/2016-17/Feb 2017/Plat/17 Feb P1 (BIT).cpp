// #include<iostream>
#include<fstream>
#include<vector>

using namespace std;
 
typedef long long ll;
typedef vector<int> vi;

#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)

ll ans = (ll)1000000000000000, N, cur = 0;
vi b,x,y;
int bit[100001], m[100001];

void update(int k) {
	while (k <= N) {
		bit[k] ++;
		k += (k & -k);
	}
}

int query(int k) {
	int temp = 0;
	while (k) {
		temp += bit[k];
		k -= (k & -k);
	}
	return temp;
}

void solve() {
	b.resize(N);
	F0R(i,100001) bit[i] = 0;
	FOR(i,1,N+1) {
		int a = x[i-1];
		m[a] = i;
	}
	cur = N*(N-1)/2;
	F0R(i,N) {
		b[i] = m[y[i]];
		cur -= query(b[i]);
		update(b[i]);
	}
	F0Rd(i,N) {
		ans = min(ans,cur);
		cur += (2*b[i]-1-N);
	}
	ans = min(ans,cur);
}

int main() {
	ifstream cin ("mincross.in");
	ofstream cout ("mincross.out");
	cin >> N; x.resize(N), y.resize(N);
	F0R(i,N) cin >> x[i];
	F0R(i,N) cin >> y[i];
	solve();
	swap(x,y);
	solve();
	cout << ans;
}