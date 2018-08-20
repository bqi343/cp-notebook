// #include<iostream>
#include<fstream>
#include<set>
#include<unordered_map>
#include<map>
#include<algorithm>
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

const int MOD = 1000000007;

ifstream cin ("art2.in");
ofstream cout ("art2.out");

int N;
pi oc[100001];
vi cur, rec;
vector<pair<pi,int>> todo;

int main() {
	cin >> N; rec.resize(N); 
	FOR(i,1,N+1) oc[i] = {N,-1};
	F0R(i,N) {
		cin >> rec[i];
		int x = rec[i];
		if (x) {
			oc[x].f = min(oc[x].f,i);
			oc[x].s = max(oc[x].s,i);
		}
	}
	FOR(i,1,N+1) if (oc[i].f != N) {
		todo.pb({{oc[i].f,0},i});
		todo.pb({{oc[i].s,1},i});
	}
	sort(todo.begin(),todo.end());
	int it = 0, mx = 0;
	F0R(i,N) {
		if (it < todo.size() && todo[it].f.f == i && todo[it].f.s == 0) {
			cur.pb(todo[it++].s);
			mx = max(mx,(int)cur.size());
		}
		if (cur.size()) {
			if (cur[cur.size()-1] != rec[i]) {
				cout << -1;
				return 0;
			}
		} else if (rec[i] != 0) {
			cout << -1;
			return 0;
		}
		if (it < todo.size() && todo[it].f.f == i && todo[it].f.s == 1) {
			cur.erase(cur.end()-1);
			it++;
		}
	}
	cout << mx;
}
