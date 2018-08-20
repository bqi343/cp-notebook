//#include<iostream>
#include<fstream>
#include<set>
#include<map>
#include<algorithm>
#include<vector>

using namespace std;

typedef pair<int, int> pi;
typedef vector<int> vi;

#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)
#define pb push_back
#define f first
#define s second

ifstream cin ("where.in");
ofstream cout ("where.out");

int N;
char grid[20][20];
int comp[20][20], temp=1;
int x1, x2, y11, y2;
int xdir[4] = {1,0,-1,0}, ydir[4] = {0,1,0,-1};
vector<pair<pi,pi>> ans;

void run(int i, int j) {
	comp[i][j] = temp;
	F0R(it,4) {
		int nx = i+xdir[it], ny = j+ydir[it];
		if (x1 <= nx && nx <= x2 && y11 <= ny && ny <= y2) 
			if (comp[nx][ny] == 0 && grid[nx][ny] == grid[i][j]) run(nx,ny);
	}
	temp++;
}

bool flood() {
	set<char> c;
	map<char,int> ncomp;
	FOR(i,x1,x2+1) FOR(j,y11,y2+1) {
		comp[i][j] = 0;
		c.insert(grid[i][j]);
		if (c.size() > 2) return 0;
	}
	if (c.size() == 1) return 0;
	//cout << c.size() << " " << x1 << " " << x2 << " " << y11 << " " << y2 << "\n";
	FOR(i,x1,x2+1) FOR(j,y11,y2+1) {
		if (comp[i][j] == 0) {
			run(i,j);
			ncomp[grid[i][j]] ++;
		}
	}
	vi z;
	for (auto a: ncomp) z.pb(a.s);
	if (z[0]>z[1]) swap(z[0],z[1]);
	if (z[0] > 1) return 0;
	if (z[1] == 1) return 0;
	return 1;
}

bool ok() {
	for (auto z: ans) {
		if (z.f.f <= x1 && x2 <= z.f.s) 
		if (y11 >= z.s.f && z.s.s >= y2) return 0;
	}
	return 1;
}

int main() {
	cin >> N;
	for (int j = N-1; j >= 0; --j) F0R(i,N) cin >> grid[i][j];
	for (int a = N; a >= 1; --a) for (int b = N; b >= 1; -- b) F0R(c,N-a+1) F0R(d,N-b+1) {
		x1 = c, x2 = c+a-1, y11 = d, y2 = d+b-1;
		if (flood() && ok())  {
			ans.pb({{x1,x2},{y11,y2}});
		}
	}
	cout << ans.size();
}
