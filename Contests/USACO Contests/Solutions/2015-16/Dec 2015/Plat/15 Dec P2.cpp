// #include <iostream>
#include <fstream>
#include <vector>
using namespace std;
 
#define pb push_back
#define vi vector<int>

#define F0R(i, a) for (int i=0; i<a; i++)
 
int high[1 << 18][3], low[1 << 18][3], N,ans=0; // bessie, elsie, total
bool used[100001];
vi b,e;

void modh(int ind, int L, int R, int des, bool elsie, int num) { // high card wins
	if (des<L || des>R) return;
	if (L == R) high[ind][elsie] += num;
	else {
		modh(2*ind,L,(L+R)/2,des,elsie,num), modh(2*ind+1,(L+R)/2+1,R,des,elsie,num);
		if (high[2*ind+1][0] >= high[2*ind][1]) {
			high[ind][2] = high[2*ind][1]+high[2*ind][2]+high[2*ind+1][2];
			high[ind][1] = high[2*ind+1][1], high[ind][0] = high[2*ind+1][0]+high[2*ind][0]-high[2*ind][1];
		} else {
			high[ind][2] = high[2*ind+1][0]+high[2*ind][2]+high[2*ind+1][2];
			high[ind][1] = high[2*ind+1][1]+high[2*ind][1]-high[2*ind+1][0], high[ind][0] = high[2*ind][0];
		}
	}
}

void modl(int ind, int L, int R, int des, bool elsie, int num) { // low card wins
	if (des<L || des>R) return;
	if (L == R) low[ind][elsie] += num;
	else {
		modl(2*ind,L,(L+R)/2,des,elsie,num), modl(2*ind+1,(L+R)/2+1,R,des,elsie,num);
		if (low[2*ind][0] >= low[2*ind+1][1]) {
			low[ind][2] = low[2*ind+1][1]+low[2*ind][2]+low[2*ind+1][2];
			low[ind][1] = low[2*ind][1], low[ind][0] = low[2*ind+1][0]+low[2*ind][0]-low[2*ind+1][1];
		} else {
			low[ind][2] = low[2*ind][0]+low[2*ind][2]+low[2*ind+1][2];
			low[ind][1] = low[2*ind+1][1]+low[2*ind][1]-low[2*ind][0], low[ind][0] = low[2*ind+1][0];
		}
	}
}

int main() {
	ifstream cin("cardgame.in");
	ofstream cout("cardgame.out");
	ios_base::sync_with_stdio(0), cin >> N;
	F0R(i,N) {
		int x; cin >> x;
		used[x] = 1, e.pb(x);
	}
	for (int i = 2*N; i > 0; --i) if (!used[i]) b.pb(i);
	F0R(i,N) modh(1,1,2*N,e[i],1,1), modh(1,1,2*N,b[i],0,1);
	ans = max(ans,high[1][2]+low[1][2]);
	for (int i = N-1; i >= 0; --i) {
		modh(1,1,2*N,e[i],1,-1), modh(1,1,2*N,b[i],0,-1);
		modl(1,1,2*N,e[i],1,1), modl(1,1,2*N,b[i],0,1);
		ans = max(ans,high[1][2]+low[1][2]);
	}
	cout << ans;
}