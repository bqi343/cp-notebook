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
 
typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pi;

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

ifstream cin ("hillwalk.in");
ofstream cout ("hillwalk.out");

vector<pair<pi,pi>> hill;
int chill, ind, N, ans=1;
ll cx;
vector<pair<pi,int>> change;

double get(int a) {
	return double((cx-hill[a].f.f)*hill[a].s.s+(hill[a].s.f-cx)*hill[a].f.s)/(hill[a].s.f-hill[a].f.f);
}

struct cmp {
	bool operator()(int a, int b) {
		return (get(a)<get(b));
	}	
};

set<int,cmp> seg;

int main() {
	cin >> N; hill.resize(N);
	F0R(i,N) {
		cin >> hill[i].f.f >> hill[i].f.s >> hill[i].s.f >> hill[i].s.s;
		change.pb({{hill[i].f.f,1},i});
		change.pb({{hill[i].s.f,-1},i});
	}
	sort(change.begin(),change.end());
	
	while (1) {
		set<int> ad;
		while (ind < change.size() && change[ind].f.f <= hill[chill].s.f){
			if (change[ind].f.s == -1) {
				if (seg.find(change[ind].s) != seg.end()) seg.erase(change[ind].s);
				else ad.erase(change[ind].s);
			} else ad.insert(change[ind].s);
			ind ++;
		}
		cx = hill[chill].s.f;
		for (int i: ad) seg.insert(i);
		if (seg.size() == 0) break;
		auto a = seg.lb(chill); 
		if (a == seg.begin()) break;
		chill = *prev(a); ans++;
	}
	cout << ans;
}
