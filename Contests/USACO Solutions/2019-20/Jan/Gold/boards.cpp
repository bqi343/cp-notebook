#include <bits/stdc++.h>
using namespace std;

#define f first
#define s second

void setIO(string name) {
	ios_base::sync_with_stdio(0); cin.tie(0);
	freopen((name+".in").c_str(),"r",stdin);
	freopen((name+".out").c_str(),"w",stdout);
}

const int MX = 1e5+5;

int N,P;
map<int,int> m;
int ans[MX];
 
void ins(int y, int v) {
	auto it = prev(m.upper_bound(y));
	if (it->s <= v) return;
	it ++;
	while (it != end(m) && it->s > v) m.erase(it++);
	m[y] = v;
}
 
int main() {
	setIO("boards");
	cin >> N >> P; m[0] = 0;
	vector<pair<pair<int,int>,pair<int,int>>> ev;
	for (int i = 0; i < P; ++i) {
		pair<int,int> a,b; 
		cin >> a.f >> a.s >> b.f >> b.s;
		ev.push_back({a,{i,-1}}); // start point
		ev.push_back({b,{i,1}}); // end point
	}
	sort(begin(ev),end(ev));
	for (auto& t: ev) {
		if (t.s.s == -1) {
			ans[t.s.f] = t.f.f+t.f.s+prev(m.upper_bound(t.f.s))->s;
		} else {
			ins(t.f.s,ans[t.s.f]-t.f.f-t.f.s);
		}
	}
	cout << m.rbegin()->s+2*N;
}