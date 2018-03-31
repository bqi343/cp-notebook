#include<iostream>
#include<fstream>
#include<vector>
#include<set>
#include<algorithm>

using namespace std;
 
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pi;

#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)
 
#define mp make_pair
#define pb push_back
#define f first
#define s second

vector<pair<ll,ll>> cows, cows1;
int N;
ll inf = 1000000000;
ll ans = inf*inf, best, lowx, highx, lowy, highy;

void solve() {
	sort(cows.begin(),cows.end());
	multiset<int> y11, y2;
	lowx = cows[0].f, highx = cows[N-1].f;
	for (auto a: cows) y2.insert(a.s);
	F0R(i,N) {
		while (1) {
			y11.insert(cows[i].s);
			y2.erase(y2.find(cows[i].s));
			if (i < N-1 && cows[i].f == cows[i+1].f) i++;
			else break;
		}
		ll cur = 0;
		cur += (cows[i].f-lowx)*(*prev(y11.end())-*y11.begin());
		if (i != N-1) cur += (highx-cows[i+1].f)*(*prev(y2.end())-*y2.begin());
		ans = min(ans,cur);
	}
	F0R(i,N) swap(cows[i].f,cows[i].s);
}

void init() {
	ifstream cin ("split.in");
	cin >> N; cows.resize(N), cows1.resize(N);
	F0R(i,N) {
		cin >> cows[i].f >> cows[i].s;
		cows1[i] = mp(cows[i].s,cows[i].f);
	}
}

int main() {
	init();
	ofstream cout ("split.out");
	solve();
	solve();
	lowx = inf, highx = 0, lowy = inf, highy = 0;
	for (auto a: cows) {
		lowx = min(lowx,a.f);
		highx = max(highx,a.f);
		lowy = min(lowy,a.s);
		highy = max(highy,a.s);
	}
	cout << (highy-lowy)*(highx-lowx)-ans;
}
