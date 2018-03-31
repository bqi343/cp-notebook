/*
ID: bqi3431
PROG: fence4
LANG: C++11
*/

//#include<iostream>
#include<fstream>
#include<algorithm>
#include<vector>
	
using namespace std;
 
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pi;
typedef pair<double,double> pdd;

#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
 
#define mp make_pair
#define pb push_back
#define f first
#define s second

const int MOD = 1000000007;
double PI = 4*atan(1);

vector<pi> points;
vector<pair<pi,pi>> seg;
vector<pdd> angles;
int x,y,N;

int signa(pi a, pi b, pi c) {
	c.f -= a.f, c.s -= a.s, b.f -= a.f, b.s -= a.s;
	return (b.f*c.s-b.s*c.f);
}

bool intersect(pair<pi,pi> a, pair<pi,pi> b) {
	ll s1 = signa(a.f,a.s,b.f), s2 = signa(a.f,a.s,b.s); // what if the areas are zero?
	if (s1*s2 > 0) return 0;
	ll s3 = signa(b.f,b.s,a.f), s4 = signa(b.f,b.s,a.s);
	if (s3*s4 > 0) return 0;
	if ((s1 == 0 && s2 != 0) || (s1 != 0 && s2 == 0)) return 0;
	if ((s3 == 0 && s4 != 0) || (s3 != 0 && s4 == 0)) return 0;
	if (s1 == 0 && s2 == 0) {
		if (a.f > a.s) swap(a.f,a.s);
		if (b.f > b.s) swap(b.f,b.s);
		if (b.f >= a.s) return 0;
		if (a.f >= b.s) return 0;
		return 1;
	}
	return 1;
}

double dist(pi a, pi b) {
	b.f -= a.f, b.s -= a.s;
	return sqrt(double(b.f)*b.f+b.s*b.s);
}

bool closer(pair<pi,pi> a, pair<pi,pi> b) { // 0 if first one, 1 if second one
	if (intersect(mp(mp(x,y),b.f),a)) return 0;
	if (intersect(mp(mp(x,y),b.s),a)) return 0;
	if (intersect(mp(mp(x,y),a.f),b)) return 1;
	if (intersect(mp(mp(x,y),a.s),b)) return 1;
	//cout << "ASDF";
	double a1 = signa(a.f,a.s,b.f);
	double a2 = signa(a.f,a.s,mp(x,y));
	double a3 = signa(a.f,a.s,b.s);
	if (a1*a2<0 || a2*a3<0 || a1*a3<0) return 0;
	return 1;
}

bool ok(int i) {
	double low = angles[i].f, high = angles[i].s;
	if (low == high) return 0;
	
	//cout << "HI " << i << " " << low << " " << high << "\n";
	//cout << seg[i].f.f << " " << seg[i].f.s << " " << seg[i].s.f << " " << seg[i].s.s << "\n";
	
	vector<pdd> x;
	F0R(i1,N) if (i != i1) {
		double a1 = angles[i1].f, a2 = angles[i1].s;
		while (a1<low) a1 += 360, a2 += 360;
		while (a1-360 >= low) a1 -= 360, a2 -= 360;
		if (a1 < high) if (closer(seg[i],seg[i1])) {
			//cout << "a " << seg[i1].f.f << " " << seg[i1].f.s << " " << seg[i1].s.f << " " << seg[i1].s.s <<  " " << a1 << " " << a2 << "\n";
			x.pb(mp(max(low,a1),min(high,a2)));
		}
		a1 -= 360, a2 -= 360;
		if (a2 > low) if (closer(seg[i],seg[i1])) {
			//cout << "b " << seg[i1].f.f << " " << seg[i1].f.s << " " << seg[i1].s.f << " " << seg[i1].s.s << " " << a1 << " " << a2 << "\n";
			x.pb(mp(max(a1,low),min(high,a2)));
		}
	}
	sort(x.begin(),x.end());
	//for (auto a: x) cout << a.f << " " << a.s << "\n";
	//cout << "\n";
	double lb = low;
	F0R(i,x.size()) {
		if (x[i].f>lb+0.00000001) return 1;
		lb = max(lb,x[i].s);
	}
	if (lb+0.00000001<high) return 1;
	return 0;
}

void input() {
	ifstream cin ("fence4.in");
	cin >> N >> x >> y; points.resize(N); seg.resize(N); angles.resize(N);
	F0R(i,N) {
		cin >> points[i].f >> points[i].s;
		if (i == 0) seg[0].f = points[0], seg[N-2].f = points[0];
		else if (i == N-1) seg[i].s = points[i], seg[i-1].s = points[i];
		else if (i == N-2) seg[N-1].f = points[i], seg[N-3].s = points[i];
		else seg[i-1].s = points[i], seg[i].f = points[i];
	}
}

int main() {
	input();
	ofstream cout ("fence4.out");
	//cout << closer(mp(mp(1,3),mp(0,3)),mp(mp(0,98),mp(-1,1))) << "\n";
	F0R(i,N) FOR(j,i+1,N) if (intersect(seg[i],seg[j])) {
		cout << "NOFENCE\n";
		return 0;
	}
	F0R(i,N) {
		double a1 = 180/PI*atan2(seg[i].f.s-y,seg[i].f.f-x);
		double a2 = 180/PI*atan2(seg[i].s.s-y,seg[i].s.f-x);
		while (a2 <= a1) a2 += 360;
		while (abs(a1-a2) >= 180) a1 += 360;
		if (a1 > a2) swap(a1,a2);
		while (a1<0 || a2<0) a1 += 360, a2 += 360;
		while (a1>=360 && a2>=360) a1 -= 360, a2 -= 360;
		angles[i] = mp(a1,a2);
	}
	vector<string> ans;
	F0R(i,N) if (ok(i)) {
		string s = to_string(seg[i].f.f) + " "
		 + to_string(seg[i].f.s) + " "
		 + to_string(seg[i].s.f) + " "
		 + to_string(seg[i].s.s);
		ans.pb(s);
	}
	cout << ans.size() << "\n";
	for (string s: ans) cout << s << "\n";
}
