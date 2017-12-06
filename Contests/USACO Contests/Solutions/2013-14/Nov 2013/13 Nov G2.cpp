// #include<iostream>
#include<fstream>
#include<algorithm>
#include<vector>
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;
 
typedef long long ll;
typedef pair<double,double> pdd;
typedef tree<double,null_type,less<double>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;

#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)
 
#define mp make_pair
#define pb push_back
#define f first
#define s second

double PI = 4*atan(1);

ifstream cin ("sight.in");
ofstream cout ("sight.out");

int N,R; 
vector<pdd> arcs;

int main() {
	cin >> N >> R;
	F0R(i,N) {
		ll x,y; cin >> x >> y;
		double arg = atan2(y,x), dif = acos(R/sqrt(x*x+y*y));
		pdd temp = {arg-dif,arg+dif};
		while (temp.f<0) {
			temp.f += 2*PI;
			temp.s += 2*PI;
		}
		arcs.pb(temp);
	}
	ll ans = 0;
	sort(arcs.begin(),arcs.end());
	ordered_set s;
	for (auto a: arcs) s.insert(a.s-2*PI);
	for (auto a: arcs) {
		ans += s.size()-s.order_of_key(a.f);
		s.erase(a.s-2*PI);
		s.insert(a.s);
	}
	cout << ans;
}