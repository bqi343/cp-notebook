#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<set>

using namespace std;
 
typedef vector<int> vi;
typedef pair<int, int> pi;

#define F0R(i, a) for (int i=0; i<a; i++)
 
#define f first
#define s second

int main() {
	//ifstream cin ("helpcross.in");
	//ofstream cout ("helpcross.out");
	int C,N; cin >> C >> N;
	vi c(C);
	vector<pi> n(N);
	F0R(i,C) cin >> c[i];
	F0R(i,N) cin >> n[i].f >> n[i].s;
	sort(c.begin(),c.end());
	sort(n.begin(),n.end());
	multiset<int> cur;
	int ind = -1, ans = 0;
	for (int i: c) {
		while (ind<(int)n.size()-1 && n[ind+1].f <= i) cur.insert(n[++ind].s);
		while (cur.size() && (*cur.begin())<i) cur.erase(cur.begin());
		if (cur.size()) {
			ans++;
			cur.erase(cur.begin());
		}
	}
	cout << ans;
}
