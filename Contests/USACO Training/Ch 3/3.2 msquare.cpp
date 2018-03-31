/*
ID: bqi3431
PROG: msquare
LANG: C++11
*/

//#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;
 
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pi;
typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;

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

const int MOD = 1000000007;
double PI = 4*atan(1);

ifstream cin ("msquare.in");
ofstream cout ("msquare.out");

queue<vi> todo;
map<vi,int> rec;
map<vi,pair<vi,char>> pre;

vi ori = {1,2,3,4,5,6,7,8};

vi A(vi a) {
	reverse(a.begin(),a.end());
	return a;
}

vi B(vi a) {
	rotate(a.begin(),a.begin()+3,a.begin()+4);
	rotate(a.begin()+4,a.begin()+5,a.end());
	return a;
}

vi C(vi c) {
	vi c1 = c;
	c1[1] = c[6];
	c1[2] = c[1];
	c1[5] = c[2];
	c1[6] = c[5];
	return c1;
}

int main() {
	rec[ori] = 1;
	pre[ori] = mp(ori,'D');
	todo.push(ori);
	
	vi des(8);
	F0R(i,8) cin >> des[i];
	
	while (todo.size()) {
		auto a = todo.front();
		todo.pop();
		if (a == des) break;
		if (rec[A(a)] == 0) {
			pre[A(a)] = mp(a,'A');
			rec[A(a)] = rec[a]+1;
			todo.push(A(a));
		}
		if (rec[B(a)] == 0) {
			pre[B(a)] = mp(a,'B');
			rec[B(a)] = rec[a]+1;
			todo.push(B(a));
		}
		if (rec[C(a)] == 0) {
			pre[C(a)] = mp(a,'C');
			rec[C(a)] = rec[a]+1;
			todo.push(C(a));
		}
	}
	cout << rec[des]-1 << "\n";
	string ans = "";
	while (pre[des].s != 'D') {
		ans += pre[des].s;
		des = pre[des].f;
	}
	reverse(ans.begin(),ans.end());
	cout << ans << "\n";
}
