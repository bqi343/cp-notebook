#include<vector>
#include <fstream>
// #include<iostream>
#include<algorithm>
#include<set>
#include<map>

using namespace std;
 
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pi;
typedef set<int> si;
typedef map<int,int> mii;

#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)
#define FORd(i,a,b) for (int i = b-1; i >= a; i--)
#define F0Rd(i,a) for (int i = a-1; i >= 0; i--)
 
#define mp make_pair
#define pb push_back
#define f first
#define s second
#define lb lower_bound
#define ub upper_bound
 
const int MOD = 1000000007;
double PI = 4*atan(1);

ifstream cin ("triangles.in");
ofstream cout ("triangles.out");

int N, rec[300][300];
vector<pi> points;
vi counts;

ll area(pi x, pi y, pi z) {
    return abs((ll)(y.f-x.f)*(z.s-x.s)-(ll)(y.s-x.s)*(z.f-x.f));
}

bool in(pi a, pi b, pi c, pi d) {
    if(area(a,b,d)+area(a,c,d)+area(b,c,d)>area(a,b,c)) return 0;
    return 1;
}

bool comp(pi a, pi b) {
	if (a.s <= 0 && b.s >= 0) return true;
	if (a.s >= 0 && b.s <= 0) return false;
	if (a.s > 0 || b.s > 0) {
		return ((ll)a.s*b.f<(ll)a.f*b.s);
	} else {
		return ((ll)a.s*b.f<(ll)a.f*b.s);
	}
}

void init() {
	FOR(i,1,N) if (points[i]<points[0]) swap(points[0],points[i]);
	FOR(i,1,N) points[i] = mp(points[i].f-points[0].f,points[i].s-points[0].s);
	points[0] = mp(0,0);
	sort(points.begin()+1,points.end(),comp);
	FOR(i,1,N) FOR(j,i+1,N) {
		FOR(k,1,N) 
			if (k != i && k != j && in(points[0],points[i],points[j],points[k])) 
				rec[i][j]++;
	}
	// F0R(i,N) cout << "hi " << points[i].f << " " << points[i].s << "\n";
}

int query(int a, int b, int c) {
	if (a == 0) return rec[b][c];
	else return max(rec[a][b]+rec[b][c]-rec[a][c],rec[a][c]-rec[a][b]-rec[b][c]-1);
}
int main() {
	cin >> N;
	points.resize(N); counts.resize(N-2);
	F0R(i,N) cin >> points[i].f >> points[i].s;
	init();
	
	F0R(i,N) FOR(j,i+1,N) FOR(k,j+1,N) counts[query(i,j,k)] ++;
	F0R(i,N-2) cout << counts[i] << "\n";
}
