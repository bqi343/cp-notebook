// #include <iostream>
#include <utility>
#include <fstream>
#include <algorithm>
#include <string>
#include <set>
#include <vector>
#include <queue>

using namespace std;

#define mp make_pair
#define pi pair <int, int>

#define F0R(i, a) for (int i=0; i<a; i++)
 
#define f first
#define s second
 
ifstream cin ("dream.in");
ofstream cout ("dream.out");

int grid[1000][1000], xdir[4] = {0,1,0,-1}, ydir[4] = {1,0,-1,0},N,M,des;
bool visit[10000000];
queue<pi> q;

int main() {
    cin >> N >> M;
    bool test = 0;
    F0R(i,N) F0R(j,M) cin >> grid[j][i];
	q.push(mp(0,0)), des = (M-1)*1000+N-1, visit[0] = 1;
	while (!q.empty()) {
		int o=0,d=0,xc=0,yc=0,x1,y1,z;
		pi x = q.front();
		q.pop();
		if (x.f == des || x.f == des+5000000) {cout << x.s;test = 1;break;}
		o = x.f/5000000, x.f -= o*5000000;
		d = x.f/1000000, x.f -= d*1000000;
		xc = x.f/1000, yc = x.f % 1000;
		// cout << xc << " " << yc << " " << o << " " << d << " " << x.s << endl;
		if (d) {
			x1 = xc+xdir[d-1], y1 = yc+ydir[d-1];
			if (x1<0 || x1>=M || y1<0 || y1>=N || grid[x1][y1] == 0 || grid[x1][y1] == 3) {
				z = 1000*xc+yc;
				if (visit[z] == 0) q.push(mp(z,x.s)), visit[z] = 1;
			} else if (grid[x1][y1] == 1) {
				z = 1000*x1+y1;
				if (visit[z] == 0) q.push(mp(z,x.s+1)), visit[z] = 1;
			} else if (grid[x1][y1] == 2) {
				z = 5000000+1000*x1+y1;
				if (visit[z] == 0) q.push(mp(z,x.s+1)), visit[z] = 1;
			} else {
				z = d*1000000+1000*x1+y1;
				if (visit[z] == 0) q.push(mp(z,x.s+1)), visit[z] = 1;
			}
		} else {
			F0R(i,4) {
				int x1 = xc+xdir[i], y1 = yc+ydir[i];
				if (x1<0 || x1>=M || y1<0 || y1>=N || grid[x1][y1] == 0) continue;
				else if (grid[x1][y1] == 1) {
					int z = 5000000*o+1000*x1+y1;
					if (!visit[z]) q.push(mp(z,x.s+1)), visit[z] = 1;
				} else if (grid[x1][y1] == 2) {
					int z = 5000000+1000*x1+y1;
					if (!visit[z]) q.push(mp(z,x.s+1)), visit[z] = 1;
				} else if (grid[x1][y1] == 3) {
					if (o == 1) {
						int z = 5000000+1000*x1+y1;
						if (!visit[z]) q.push(mp(z,x.s+1)), visit[z] = 1;
					}
				} else {
					int z = (i+1)*1000000+1000*x1+y1;
					if (!visit[z]) q.push(mp(z,x.s+1)), visit[z] = 1;
				} 
			}
		}
	}
	if (!test) cout << -1;
}
