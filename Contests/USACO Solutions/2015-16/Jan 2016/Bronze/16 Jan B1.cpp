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

int main() {
	ifstream cin ("promote.in");
	ofstream cout ("promote.out");
	pi a,b,c,d;
	cin >> a.f >> a.s >> b.f >> b.s >> c.f >> c.s >> d.f >> d.s;
	int a1,a2,a3;
	a3 = d.s-d.f;
	c.s += a3;
	a2 = c.s-c.f;
	b.s += a2;
	a1 = b.s-b.f;
	cout << a1 << "\n" << a2 << "\n" << a3;
}
