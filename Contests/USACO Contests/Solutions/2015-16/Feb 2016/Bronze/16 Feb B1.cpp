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

int posi[1001];

int main() {
	ifstream cin ("pails.in");
	ofstream cout ("pails.out");
	int X,Y,M; cin >> X >> Y >> M;
	F0R(i,M/X+1) posi[i*X] = 1;
	F0R(j,M/Y+1) F0R(i,M) if (posi[i] && i+j*Y <= M) posi[i+j*Y] = 1;
	for (int i = M; i >= 0; --i) if (posi[i]) {
		cout << i;
		return 0;
	}
}
