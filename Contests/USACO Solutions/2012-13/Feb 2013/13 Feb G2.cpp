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

int N,M;
pi rec[200001];
vector<pi> c1, c2;
vector<ll> temp;

ifstream cin ("taxi.in");
ofstream cout ("taxi.out");

void init() {
	cin >> N >> M;  temp = {0,M};
	
	F0R(i,N) {
		pi cow; cin >> cow.f >> cow.s;
		temp.pb(cow.f); temp.pb(cow.s);
		if (cow.f<cow.s) c1.pb(cow);
		else c2.pb({cow.s,cow.f});
	}
	sort(temp.begin(),temp.end());
	temp.erase(unique(temp.begin(),temp.end()),temp.end());
	sort(c1.begin(),c1.end());
	sort(c2.begin(),c2.end());
}

void gen() {
	multiset<ll> vals;
	int it = 0;
	F0R(i,temp.size()-1) {
		while (it < c1.size() && c1[it].f <= temp[i]) {
			vals.insert(c1[it].s);
			it ++;
		}
		while (vals.size() && (*vals.begin()) <= temp[i]) vals.erase(vals.begin());
		rec[i].s = vals.size();
	}
	vals.clear(); it = 0;
	F0R(i,temp.size()-1) {
		while (it < c2.size() && c2[it].f <= temp[i]) {
			vals.insert(c2[it].s);
			it ++;
		}
		while (vals.size() && (*vals.begin()) <= temp[i]) vals.erase(vals.begin());
		rec[i].f = vals.size();
	}
}

int main() {
	init();
	gen();
	ll ans = 0;
	F0R(i,temp.size()-1) ans += (temp[i+1]-temp[i])*max(2*rec[i].f+1,2*rec[i].s-1);
	cout << ans;
}
