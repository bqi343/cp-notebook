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

int main() {
	ifstream cin ("diamond.in");
	ofstream cout ("diamond.out");
	int N,K,ans=0; cin >> N >> K;
	vi x(N); F0R(i,N) cin >> x[i];
	sort(x.begin(),x.end());
	F0R(i,N) {
		FOR(j,i,N) {
			if (x[j]-x[i] <= K) ans = max(ans,j-i+1);
			else break;
		}
	}
	cout << ans;
}
