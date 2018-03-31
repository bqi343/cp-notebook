//#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>

using namespace std;

typedef vector<int> vi;
typedef pair<int, int> pi;

#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)
#define f first
#define s second

int cx = 1000, cy = 1000, lastvisit[2001][2001], ans = 1000000007, cur = 0;

void test() {
	if (lastvisit[cx][cy] != -1) ans = min(ans,cur-lastvisit[cx][cy]);
	lastvisit[cx][cy] = cur;
}

int main() {
	ifstream cin ("mowing.in");
	ofstream cout ("mowing.out");
	int N; cin >> N;
	F0R(i,2001) F0R(j,2001) lastvisit[i][j] = -1;
	lastvisit[cx][cy] = 0;
	
	F0R(i,N) {
		char dir; int num; cin >> dir >> num;
		if (dir == 'N') {
			F0R(j,num) {
				cy++, cur++;
				test();
			}
		}
		else if (dir == 'E') {
			F0R(j,num) {
				cx++, cur++;
				test();
			}
		}
		else if (dir == 'S') {
			F0R(j,num) {
				cy--, cur++;
				test();
			}
		}
		else if (dir == 'W') {
			F0R(j,num) {
				cx--, cur++;
				test();
			}
		}
	}
	if (ans == 1000000007) ans = -1;
	cout << ans;
}
