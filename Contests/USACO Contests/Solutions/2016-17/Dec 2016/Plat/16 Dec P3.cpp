#include<vector>
#include<fstream>
#include<iostream>
#include<algorithm>
#include<set>

using namespace std;

typedef long long ll;

#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)
#define pb push_back

// ifstream cin ("roboherd.in");
// ofstream cout ("roboherd.out");

ll N,K, sum, mx=0;
ll model[100000][10], M[100000];

void input() {
	cin >> N >> K;
	F0R(i,N) {
	    cin >> M[i];
	    F0R(j,M[i]) cin >> model[i][j];
	    sort (model[i], model[i]+M[i]);
	    ll temp = model[i][0];
	    F0R(j,M[i]) model[i][j] -= temp;
	    sum += K*temp;
	    mx += model[i][M[i]-1];
	}
}

bool bash(ll n) {
	multiset<ll> cur; cur.insert(0);
	F0R(i,N) {
		vector<ll> cur1;
		FOR(j,1,M[i]) {
			for (ll k: cur) {
				if (k+model[i][j] <= n) cur1.pb(k+model[i][j]);
				else break;
			}
			if (cur.size()+cur1.size() > K) return 1;
		}
		for (int j: cur1) cur.insert(j);
	}
	return 0;
}

void solve(ll n) {
	multiset<ll> cur;
	cur.insert(0);
	F0R(i,N) {
		vector<ll> cur1;
		FOR(j,1,M[i]) {
			for (int k: cur) {
				if (k+model[i][j] <= n) cur1.pb(k+model[i][j]);
				else break;
			}
		}
		for (int j: cur1) cur.insert(j);
	}
	for (auto i: cur) sum += i;
	sum += (K-cur.size())*(n+1);
}

int main() {
	input();
	ll l = -1, u = mx;
	while (l<u) {
		ll mid = (l+u+1)/2;
		if (bash(mid)) u = mid-1; // find the last one which is less than or equal
		else l = mid; 
	}
	solve(l);
	cout << sum;
}