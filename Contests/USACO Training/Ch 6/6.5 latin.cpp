/*
ID: bqi3431
PROG: latin
LANG: C++11
*/

//#include<iostream>
#include<fstream>
#include<set>
#include<map>
#include<cmath>
#include<cstring>
#include<string>
#include<bitset>
#include<algorithm>
#include<vector>

using namespace std;
 
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pi;

#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)

int N;
ll ans = 0;
bool z[7][7];

void dfs(int todo, int crow, int num) {
	if (crow == todo) {
		if (todo == N-1) ans++;
		else dfs(todo,crow+1,num);
		return;
	}
	FOR(i,1,N) if (i != todo && z[crow][i] == 0 && (num & (1<<i)) == 0) {
		z[crow][i] = 1;
		if (crow == N-1) dfs(todo+1,1,0);
		else dfs(todo,crow+1,num|(1<<i));
		z[crow][i] = 0;
	}
}

int main() {
	ifstream cin ("latin.in");
	ofstream cout ("latin.out");
	cin >> N;
	F0R(i,N) z[i][0] = z[0][i] = 1;
	if (N <= 2) ans = 1;
	else if ( N <= 6) dfs(1,2,0);
	else {
		ll ans1 = 0;
		
		z[2][2] = z[3][3] = z[4][4] = z[5][5] = z[6][6] = 1; // 11111 --> 1
		dfs(2,1,0);
		ans1 += ans; ans = 0;
		z[2][2] = z[3][3] = z[4][4] = z[5][5] = z[6][6] = 0;
		
		z[2][3] = z[3][2] = z[4][4] = z[5][5] = z[6][6] = 1; // 2111 --> 10
		dfs(2,1,0);
		ans1 += 10*ans; ans = 0;
		z[2][3] = z[3][2] = z[4][4] = z[5][5] = z[6][6] = 0;
		
		z[2][3] = z[3][2] = z[4][5] = z[5][4] = z[6][6] = 1; // 221 --> 15
		dfs(2,1,0);
		ans1 += 15*ans; ans = 0;
		z[2][3] = z[3][2] = z[4][5] = z[5][4] = z[6][6] = 0;
		
		z[2][3] = z[3][4] = z[4][2] = z[5][6] = z[6][5] = 1; // 32 --> 20
		dfs(2,1,0);
		ans1 += 20*ans; ans = 0;
		z[2][3] = z[3][4] = z[4][2] = z[5][6] = z[6][5] = 0;
		
		z[2][3] = z[3][4] = z[4][2] = z[5][5] = z[6][6] = 1; // 311 --> 20
		dfs(2,1,0);
		ans1 += 20*ans; ans = 0;
		z[2][3] = z[3][4] = z[4][2] = z[5][5] = z[6][6] = 0;
		
		z[2][3] = z[3][4] = z[4][5] = z[5][2] = z[6][6] = 1; // 41 --> 30
		dfs(2,1,0);
		ans1 += 30*ans; ans = 0;
		z[2][3] = z[3][4] = z[4][5] = z[5][2] = z[6][6] = 0;
		
		z[2][3] = z[3][4] = z[4][5] = z[5][6] = z[6][2] = 1; // 5 --> 24
		dfs(2,1,0);
		ans1 += 24*ans; ans = 0;
		z[2][3] = z[3][4] = z[4][5] = z[5][6] = z[6][2] = 0;
		ans = ans1;
	}
	FOR(i,1,N) ans *= i;
	cout << ans << "\n";
}
