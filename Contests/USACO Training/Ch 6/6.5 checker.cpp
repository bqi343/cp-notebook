/*
ID: bqi3431
PROG: checker
LANG: C++11
*/

//#include<iostream>
#include<fstream>
#include<vector>

using namespace std;
 
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pi;

#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
 
#define mp make_pair
#define pb push_back
#define f first
#define s second
#define lb lower_bound
#define ub upper_bound

ll tot = 0;
bool diag1[25], diag2[25], col[13];
vector<string> ans;
vi csol;
int N;

void search(int crow) {
	//for (int i: csol) cout << i << " ";
	//cout << "\n";
	if (crow == N) {
		if (ans.size()<3) {
			string c = "";
			F0R(i,N) {
				c += to_string(csol[i]);
				if (i != N-1) c += " ";
			}
			ans.pb(c);
		}
		tot++;
		return;
	}
	F0R(i,N) if (!col[i] && !diag1[i+crow] && !diag2[i-crow+12]) {
		col[i] = 1;
		diag1[i+crow] = 1;
		diag2[i-crow+12] = 1;
		csol.pb(i+1);
		search(crow+1);
		col[i] = 0;
		diag1[i+crow] = 0;
		diag2[i-crow+12] = 0;
		csol.erase(csol.end()-1);
	}
}

int main() {
	ifstream cin ("checker.in");
	ofstream cout ("checker.out");
	cin >> N;
	search(0);
	for (string s: ans) {
		cout << s;
		cout << "\n";
	}
	cout << tot << "\n";
}
