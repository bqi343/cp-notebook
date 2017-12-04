/*
ID: bqi3431
PROG: betsy
LANG: C++11
*/

//#include<iostream>
#include<fstream>

using namespace std;

#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)
 
#define mp make_pair
#define pb push_back
#define f first
#define s second

bool cur[7][7];
int N, xdir[4] = {0,1,0,-1}, ydir[4] = {1,0,-1,0}, ans = 0;

void search(int x, int y, int csum) {
	if (x == 0 && y == N-1) {
		if (csum == N*N) ans++;
		return;
	}
 	if (N == 7 && x == 0 && y == 3 && csum<25) return;
 	int nx[4], ny[4], ok[4], sum = 0;
	F0R(i,4) {
		nx[i] = x+xdir[i], ny[i] = y+ydir[i];
		if (nx[i] >= N || nx[i] < 0 || ny[i] >= N || ny[i] < 0 || cur[nx[i]][ny[i]]) ok[i] = 0;
		else ok[i] = 1, sum++;
	}
	
	if (sum == 0) return;
	if (sum == 2) if ((ok[0] & ok[2]) || (ok[1] & ok[3])) return;
	
	F0R(i,4) if (ok[i]) {
		cur[nx[i]][ny[i]] = 1;
		search(nx[i],ny[i],csum+1);
		cur[nx[i]][ny[i]] = 0;
	}
}

int main() {
	ifstream cin ("betsy.in");
	ofstream cout ("betsy.out");
	cin >> N;
	cur[0][0] = 1;
	search(0,0,1);
	if (N == 7) ans *= 2;
	cout << ans << "\n";
}