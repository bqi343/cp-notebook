#include <iostream>
// #include <fstream>
 
using namespace std;

#define ll long long
#define mp make_pair
#define pb push_back
#define pi pair <int, int>
#define vi vector<int>

#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)
 
#define f first
#define s second
#define lb lower_bound
#define ub upper_bound
 
// ifstream cin ("gates.in");
// ofstream cout ("gates.out");
 
int N, components;
bool visit[2001][2001], hor[2000][2001], vor[2000][2001];
int xs[4] = {-1,0,1,0}, ys[4] = {0,1,0,-1}; // W, N, E,S
 
int ok (int x, int y) {
	if (x < 0 || x > 2000 || y < 0 || y > 2000) return 0;
	if (visit[x][y]) return 0;
	return 1;
}
 
int ne(int a, int b, int dir) {
	if (dir == 0) { // W
		if (vor[a-1][b] == 1) return 0;
	} else if (dir == 1) { // N
		if (hor[a][b] == 1) return 0;
	} else if (dir == 2) { // E
		if (vor[a][b] == 1) return 0;
	} else { // S
		if (hor[a][b-1] == 1) return 0;
	}
	return 1;
}
 
void start (int x, int y) {
	visit[x][y] = 1;
	F0R(i,4) if (ok(x+xs[i],y+ys[i]) && ne(x,y,i)) start(x+xs[i], y+ys[i]);
}
 
int main() {
	ios_base::sync_with_stdio(0), cin >> N;
	int curx = 1000, cury = 1000;
	
	F0R(i,N) {
		char x;
		cin >> x;
		if (x == 'N') {
			vor[curx][cury+1] = 1;
			cury++;
		} else if (x == 'W') {
			hor[curx][cury] = 1;
			curx--;
		} else if (x == 'E') {
			hor[curx+1][cury] = 1;
			curx++;
		} else {
			vor[curx][cury] = 1;
			cury--;
		}
	}
	
    F0R(i,2001) F0R(j,2001) if (!visit[i][j]) {
		start(i,j);
		components++;
	}
 
	cout << components-1;
}
