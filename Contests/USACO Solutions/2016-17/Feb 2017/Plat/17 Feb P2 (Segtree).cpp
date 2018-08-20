#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;
 
typedef long long ll;
typedef vector<int> vi;

#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)
#define pb push_back

const int MX = 1<<17;
vi ok[100001];
int posi[100001], seg[2*MX], N;

void upd(int ind, int val) {
	ind += MX; seg[ind] = val;
	while (ind > 1) {
		ind /= 2;
		seg[ind] = max(seg[2*ind],seg[2*ind+1]);
	}
}

int query(int high) {
	int low = MX, x = 0; 
	high += MX;
	while (low<high) {
		if (high % 2 == 0) x = max(x,seg[high--]);
		if (low % 2 == 1) x = max(x,seg[low++]);
		low /= 2, high /= 2;
	}
	if (low == high) x = max(x,seg[low]);
	return x;
}

int main() {
	//ifstream cin ("nocross.in");
	//ofstream cout ("nocross.out");
	cin >> N; 
	F0R(i,N) {
		int a; cin >> a;
		posi[a] = i;
	}
	F0R(i,N) {
		int b; cin >> b;
		FOR(j,b-4,b+5) 
			if (1 <= j && j <= N) 
				ok[posi[j]].pb(i);
	}
	F0R(i,N) {
		sort(ok[i].begin(),ok[i].end());
		for (int j = ok[i].size()-1; j >= 0; --j)
			upd(ok[i][j],query(ok[i][j]-1)+1);
	}
	cout << query(N-1);
}