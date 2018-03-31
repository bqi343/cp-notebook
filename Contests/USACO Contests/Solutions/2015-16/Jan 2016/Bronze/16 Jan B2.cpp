// #include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>

using namespace std;
typedef vector<int> vi;
typedef pair<int, int> pi;

#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)

int ans = 0,N;

vi x;

void test(int i) {
	int c = i, c1, rad = 1;
	while (1) {
		c1 = c;
		while (c<N-1 && x[c+1]-x[c1] <= rad) c++;
		if (c == c1) break;
		rad++;
	}
	int d = i, d1;
	rad = 1;
	while (1) {
		d1 = d;
		while (d>0 && x[d1]-x[d-1] <= rad) d--;
		if (d == d1) break;
		rad++;
	}
	ans = max(ans,c-d+1);
}

int main() {
	ifstream cin ("angry.in");
	ofstream cout ("angry.out");
	cin >> N; x.resize(N);
	F0R(i,N) cin >> x[i];
	sort(x.begin(),x.end());
	F0R(i,N) test(i);
	cout << ans;
}
