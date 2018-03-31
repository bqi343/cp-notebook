// #include<iostream>
#include<fstream>
#include<set>
#include<map>
#include<unordered_map>
#include<cmath>
#include<cstring>
#include<string>
#include<bitset>
#include<algorithm>
#include<vector>

using namespace std;
//using namespace __gnu_pbds;
 
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pi;
//typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;

#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
 
#define mp make_pair
#define pb push_back
#define f first
#define s second
#define lb lower_bound
#define ub upper_bound

const int MOD = 1000000007;
double PI = 4*atan(1);

int N;
vector<pi> bale;
set<pi> bale1, bad;

void add(int st, int en) {
	// check if smth else contains
	auto x = bad.ub({st,MOD});
	if (bad.size() && x != bad.begin()) {
		x = prev(x);
		if ((*x).f <= st && en <= (*x).s) return;
	}
	bad.insert({st,en});
}

int main() {
	ifstream cin ("trapped.in");
	ofstream cout ("trapped.out");
	
	cin >> N; bale.resize(N);
	F0R(i,N) cin >> bale[i].f >> bale[i].s;
	sort(bale.begin(),bale.end());
	reverse(bale.begin(),bale.end());
	
	for (auto a: bale) { 
		pi a1 = {a.s,a.f}; // pos, weight
		auto x = bale1.ub(a1);
		if (x != bale1.end()) {
			auto b = *x;
			if (min(a1.s,b.s) >= (b.f-a1.f)) add(a1.f,b.f);
		}
		if (bale1.size() && x != bale1.begin()) {
			auto b = *prev(x);
			if (min(a1.s,b.s) >= a1.f-b.f) add(b.f,a1.f);
		}
		bale1.insert(a1);
	}
	int ans = 0;
	for (auto a: bad) ans += (a.s-a.f);
	cout << ans;
}
