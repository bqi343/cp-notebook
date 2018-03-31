//#include<iostream>
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

pi points[200];
int N, lengths[200], dis[200], angle[200], total = 0, ans=0;

int dist(int a, int b) {
	a %= N, b %= N;
	return abs(points[a].f-points[b].f)+abs(points[a].s-points[b].s);
}

bool is (int vert) {
	int a = (vert+N-1)%N, b = vert%N, c = (vert+1)%N;
	pi p1 = mp(points[a].f-points[b].f,points[a].s-points[b].s);
	pi p2 = mp(points[c].f-points[b].f,points[c].s-points[b].s);
	p1 = mp(-p1.s,p1.f); 
	if ((ll)p1.f*p2.f<0 || (ll)p1.s*p2.s<0) return 1;
	return 0;
}

int fin (int v1, int v2) {
	vi a1, b1, a2, b2;
	b1.pb(angle[v1]), b2.pb(angle[v2]);
	if (b1[0] != b2[0]) return 0;
	int cur = 0;
	while (1) {
		if (v1+cur+1 == N || v2+cur+1 == N) return cur+1;
		a1.pb(lengths[v1+cur]); b1.pb(angle[v1+cur+1]);
		a2.pb(lengths[v2+cur]); b2.pb(angle[v2+cur+1]);
		if (a1[a1.size()-1] != a2[a2.size()-1]) return cur+1;
		if (b1[b1.size()-1] != b2[b2.size()-1]) return cur+1;
		cur++;
	}
}

void test(int vert) {
	int mx = 0, cur = 0;
	FOR(i,1,N) if (i != vert) mx = max(fin(vert,i),mx);
	
	//cout << vert << " " << mx << "\n";
	if (vert+mx == N) {
		cur = total-dis[vert];
		cur -= min(dis[vert],total-dis[vert]);
	} else {
		cur = dis[vert+mx]-dis[vert]+min(dis[vert+mx],total-dis[vert+mx]);
		cur -= min(dis[vert],total-dis[vert]);
	}
	ans = max(ans,cur);
}

void init() {
	ifstream cin ("lightsout.in");
	cin >> N; 
	F0R(i,N) cin >> points[i].f >> points[i].s;
	F0R(i,N) {
		lengths[i] = dist(i,i+1);
		if (i != N-1) dis[i+1] = dis[i]+lengths[i];
		else total = dis[i]+lengths[i];
		//cout << dis[i] << "\n";
	}
	F0R(i,N) if (is(i)) angle[i] = 1;
}

int main() {
	ofstream cout ("lightsout.out");
	init();
	FOR(i,1,N) test(i);
	cout << ans;
}
