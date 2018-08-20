// #include<iostream>
#include<fstream>
#include<vector>

using namespace std;
//using namespace __gnu_pbds;
 
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pi;
//typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;

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

ifstream cin ("shufflegold.in");
ofstream cout ("shufflegold.out");

int N,M,Q;
int nex[100001]; // position of card after the Bessie shuffle
int pre[100001]; // reverse of nex
pi pos[100001]; 
vi cyc[100001];

int main() {
	cin >> N >> M >> Q;
	FOR(i,1,M+1) {
		cin >> nex[i]; nex[i] --;
		pre[nex[i]] = i; 
	}
	int cur = 0, co = 0;
	while (1) {
		cyc[0].pb(cur);
		pos[cur].s = co++;
		if (cur == M) break;
		cur = pre[cur];
	}
	FOR(i,1,M+1) if (pos[i].f == 0 && pos[i].s == 0) { 
		int cur = i, co = 0;
		while (1) {
			cyc[i].pb(cur); // store the cycles
			pos[cur] = {i,co++};
			cur = nex[cur];
			if (cur == i) break;
		}
	}

	// some cards keep cycling around until Bessie has less than M cards left
	F0R(i,Q) {
		int q; cin >> q; q = N+1-q;
		if (q <= N-M+1) {
			if (q >= cyc[0].size()) cout << cyc[0][cyc[0].size()-1]+q-(cyc[0].size()-1);
			else cout << cyc[0][q];
		} else {
			int cur = q-(N-M+1); 
			if (pos[cur].f == 0) {
				int c = pos[cur].s+N-M+1; 
				if (c < cyc[0].size()) cout << cyc[0][c];
				else cout << cyc[0][cyc[0].size()-1]+c-(cyc[0].size()-1);
			} else {
				int c = pos[cur].f;
				int ind = (pos[cur].s-(N-M+1)) % (int)cyc[c].size();
				while (ind<0) ind += cyc[c].size();
				cout << cyc[c][ind];
			}
		}
		cout << "\n";
	}
}
