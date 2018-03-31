// #include<iostream>
#include<fstream>
#include<set>
#include<map>
#include<unordered_map>
#include<cmath>
#include<cstring>
#include<string>
#include<bitset>
#include<algorithm>
#include<vector>

using namespace std;
//using namespace __gnu_pbds;
 
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
double PI = 4*atan(1);

int N,Q, segsum[200000], segmax[200000];
vector<pi> loc;

int dist(pi a, pi b) {
	b.f -= a.f, b.s -= a.s;
	return abs(b.f) + abs(b.s);
}

void modifysum(int p, int value) {  // set value at position p
  for (segsum[p += 100000] = value; p > 1; p >>= 1) segsum[p>>1] = segsum[p] + segsum[p^1];
}

void modifymax(int p, int value) {  // set value at position p
  for (segmax[p += 100000] = value; p > 1; p >>= 1) segmax[p>>1] = max(segmax[p],segmax[p^1]);
}

int qsum(int l, int r) {  // sum on interval [l, r)
  int res = 0;
  for (l += 100000, r += 100000; l < r; l >>= 1, r >>= 1) {
    if (l&1) res += segsum[l++];
    if (r&1) res += segsum[--r];
  }
  return res;
}

int qmax(int l, int r) {  
  int res = 0;
  for (l += 100000, r += 100000; l < r; l >>= 1, r >>= 1) {
    if (l&1) res = max(res,segmax[l++]);
    if (r&1) res = max(res,segmax[--r]);
  }
  return res;
}

int main() {
	ifstream cin ("marathon.in");
	ofstream cout ("marathon.out");
	
	cin >> N >> Q; loc.resize(N);
	F0R(i,N) cin >> loc[i].f >> loc[i].s;
	F0R(i,N-1) modifysum(i,dist(loc[i],loc[i+1]));
	F0R(i,N-2) modifymax(i,dist(loc[i],loc[i+1])+dist(loc[i+1],loc[i+2])-dist(loc[i],loc[i+2]));
	
	F0R(i,Q) {
		char c; cin >> c;
		if (c == 'U') {
			int node,x,y; cin >> node >> x >> y;
			node--; loc[node] = {x,y};
			
			if (node<N-1) modifysum(node,dist(loc[node],loc[node+1]));
			if (node>0) modifysum(node-1,dist(loc[node-1],loc[node]));
			if (node>1) 
				modifymax(node-2,dist(loc[node-2],loc[node-1])+dist(loc[node-1],loc[node])-dist(loc[node-2],loc[node]));
			if (node>0 && node<N-1)
				modifymax(node-1,dist(loc[node-1],loc[node])+dist(loc[node],loc[node+1])-dist(loc[node-1],loc[node+1]));
			if (node<N-2)
				modifymax(node,dist(loc[node],loc[node+1])+dist(loc[node+1],loc[node+2])-dist(loc[node],loc[node+2]));
		} else {
			int start, end; cin >> start >> end;
			start --, end--;
			cout << qsum(start,end)-qmax(start,end-1) << "\n";
		}
	}
}
