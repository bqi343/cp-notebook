/*
ID: bqi3431
PROG: fence3
LANG: C++11
*/

//#include<iostream>
#include<fstream>
#include<set>
#include<algorithm>
#include<vector>
#include<iomanip>

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

vector<pair<pi,pi>> fence;
pdd cur = mp(50,50);

double getdist(pdd a, pdd b) {
	return sqrt((a.f-b.f)*(a.f-b.f)+(a.s-b.s)*(a.s-b.s));
}

double eval(pdd p, pair<pi,pi> a) {
	if (a.f.f == a.s.f) { // vertical
		if (a.f.s <= p.s && a.s.s >= p.s) return abs(a.f.f-p.f);
	} else {
		if (a.f.f <= p.f && a.s.f >= p.f) return abs(a.f.s-p.s);
	}
	return min(getdist(p,a.f),getdist(p,a.s));
}

double getall (pdd p) {
	double z = 0;
	for (auto a: fence) z += eval(p,a);
	return z;
}

double xt(double y) {
	double lb = 0, ub = 100;
	while (ub-lb>0.00000001) {
		double lb1 = (2*lb+ub)/3;
		double ub1 = (lb+2*ub)/3;
		if (getall(mp(lb1,y))>getall(mp(ub1,y))) lb = lb1;
		else ub = ub1;
	}
	return lb;
}

double yt(double x) {
	double lb = 0, ub = 100;
	while (ub-lb>0.00000001) {
		double lb1 = (2*lb+ub)/3;
		double ub1 = (lb+2*ub)/3;
		if (getall(mp(x,lb1))>getall(mp(x,ub1))) lb = lb1;
		else ub = ub1;
	}
	return lb;
}

int main() {
	ifstream cin ("fence3.in");
	ofstream cout ("fence3.out");
	int F; cin >> F; fence.resize(F);
	F0R(i,F) {
		cin >> fence[i].f.f >> fence[i].f.s >> fence[i].s.f >> fence[i].s.s;
		if (fence[i].f>fence[i].s) swap (fence[i].f,fence[i].s);
	}
	F0R(i,50) {
		cur.f = xt(cur.s);
		cur.s = yt(cur.f);
	}
	cout << fixed << setprecision(1);
	cout << cur.f << " " << cur.s << " " << getall(cur) << "\n";
}
