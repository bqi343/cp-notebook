//#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<set>

using namespace std;

typedef vector<int> vi;
typedef pair<int, int> pi;

#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)
#define f first
#define s second
#define pb push_back

int ans = 1000000000,N,B;
vector<pi> cow;

void test(int x, int y) {
	int n1=0,n2=0,n3=0,n4=0;
	F0R(i,N) if (cow[i].f>x) {
		if (cow[i].s>y) {
			n1++;
		} else {
			n2++;
		}
	} else {
		if (cow[i].s>y) {
			n3++;
		} else {
			n4++;
		}
	}
	//cout << n1 << " " << n2 << " " << n3 << " " << n4 << "\n";
	ans = min(ans,max(max(n1,n2),max(n3,n4)));
}

int main() {
	ifstream cin ("balancing.in");
	ofstream cout ("balancing.out");
	cin >> N >> B; cow.resize(N);
	F0R(i,N) cin >> cow[i].f >> cow[i].s;
	F0R(i,N) F0R(j,N) {
		test(cow[i].f+1,cow[j].s+1);
	}
	cout << ans;
}
