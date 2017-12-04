/*
ID: bqi3431
LANG: C++11
PROG: vans
*/

#include<fstream>
#include<vector>

#define FOR(i,a,b) for (int i = a; i < b; ++i)
#define F0R(i,a) for (int i = 0; i < a; ++i)
#define vi vector<int>

using namespace std;

ifstream cin ("vans.in");
ofstream cout ("vans.out");
	
vi a[1001], b[1001], c[1001];

vi make() {
	vi k(500);
	return k;
}

vi sum(vi x, vi y) {
	vi z = make();
	F0R(i,500) {
		z[i] += x[i]+y[i];
		if (z[i] > 9) {
			z[i] -= 10;
			z[i+1] ++;
		}
	}
	return z;
}

void print(vi x) {
	bool f = 0;
	for (int i = 499; i >= 0; --i) {
		if (x[i] == 0) {
			if (f) cout << 0;
		} else {
			f = 1;
			cout << x[i];
		}
	}
	if (f == 0) cout << 0;
	cout << endl;
}

int main() {
	F0R(i,3) {
		a[i] = make();
		b[i] = make();
		c[i] = make();
	}
	b[2][0] = 2;
	FOR(i,3,1001) {
		a[i] = sum(sum(a[i-1],b[i-1]),c[i-1]);
		vi temp = sum(sum(a[i-2],b[i-2]),c[i-2]);
		b[i] = sum(sum(temp,temp),b[i-1]);
		c[i] = sum(b[i-2],c[i-2]);
	}
	int N; cin >> N;
	print(sum(sum(a[N],b[N]),c[N]));
}