/*
ID: bqi3431
PROG: prime3
LANG: C++11
*/

//#include<iostream>
#include<fstream>
#include<algorithm>
#include<vector>
#include<set>

using namespace std;
 
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

vi prime[100000], nozero;
int sum, upleft, arr[5][5], ok[100000]; 
set<string> ans;

int getsum(int i) {
	int c = 0;
	while (i) {
		c += (i%10);
		i /= 10;
	}
	return c;
}

bool noz (int i) {
	if (i/10000 != upleft) return 0;
	while (i) {
		if ((i%10) == 0) return 0;
		i /= 10;
	}
	return 1;
}

void gen() {
	FOR(i,10000,100000) if (getsum(i) == sum) {
		bool p = 1;
		for (int j = 2;;++j) {
			if ((i%j) == 0) {
				p = 0;
				break;
			}
			if (j*j>i) break;
		}
		if (p) {
			if (noz(i)) nozero.pb(i);
			int i1 = i;
			while (i1) {
				prime[i1].pb(i);
				ok[i1] = 1;
				i1 /= 10;
			}
		}
	}
}

void prin(int k) {
	string z = "", z1 = "";
	F0R(i,5) {
		F0R(j,5) z += char('0'+arr[i][j]), z1 += char('0'+arr[j][i]);
		z += "\n";
		z1 += "\n";
	}
	if (k == 0) ans.insert(z);
	else ans.insert(z1);
}

void solve(int cur, int todo) { // alternate row, column
	int cur1 = (cur-1)/2, todo1 = todo;
	if (cur != 0) {
		if (cur % 2 == 1) { // row
			FORd(i,cur1,5) { // change these indices
				arr[cur1][i] = todo % 10; todo /= 10;
				int temp = 0;
				F0R(j,cur1+1) temp = 10*temp+arr[j][i];
				if (!ok[temp]) return;
			}
		} else { // column
			FORd(i,cur1+1,5) { // change these indices
				arr[i][cur1] = todo % 10; todo /= 10;
				int temp = 0;
				F0R(j,cur1+1) temp = 10*temp+arr[i][j];
				if (!ok[temp]) return;
			}
		}
	}
	if (cur&1) {
		int cprime = 0;
		F0R(i,cur1+1) cprime = 10*cprime+arr[i][i];
		if (cur1 >= 0) if (!ok[cprime]) return;
	}
	if (cur == 0) {
		for (int i: nozero) solve(cur+1,i);
		return;
	} else if (cur == 1) {
		for (int i: nozero) if (i >= todo1) solve(cur+1,i);
		return;
	}
	if (cur == 10) {
		int cprime = 0, cprime1 = 0;
		F0R(j,5) cprime = 10*cprime+arr[4-j][j];
		F0Rd(j,5) cprime1 = 10*cprime1+arr[4-j][j];
		if (ok[cprime]) prin(0);
		if (ok[cprime1]) prin(1);
		return;
	}
	int cprime = 0;
	if (cur % 2 == 1) F0R(i,cur1+1) cprime = 10*cprime+arr[i][cur1];
	else F0R(i,cur1+1) cprime = 10*cprime+arr[cur1+1][i];
	for (int i: prime[cprime]) solve(cur+1,i);
}

int main() {
	ifstream cin ("prime3.in");
	ofstream cout ("prime3.out");
	cin >> sum >> upleft;
	gen();
	solve(0,0);
	if (!ans.size()) cout << "NONE\n";
	else {
		auto it = ans.begin();
		while (it != ans.end()) {
			cout << *it;
			if (next(it) != ans.end()) cout << "\n";
			it = next(it);
		}
	}
}
