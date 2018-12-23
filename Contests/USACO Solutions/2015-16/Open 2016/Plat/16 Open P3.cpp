#include <bits/stdc++.h>

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

const int MOD = 1000000007;
double PI = 4*atan(1);

ll N,X,Y,Z,co = 1000000;
ll ans = 0;
vector<pair<char,int>> flo[2000001];

ll pres[1000002], prel[1000002], cu[1000002];
ll sufs[1000002], sufl[1000002], p[1000002];

ll cum(int a, int b) {
	if (b < 0) return 0;
	return cu[b]-cu[a-1];
}

void genpre(vector<pair<char,int>>& v) {
	FOR(i,1,v.size()) {
		cu[i] = abs(v[i].s-v[i-1].s);
		if (i > 1) cu[i] += cu[i-2];
	}
	
	FOR(i,1,v.size()+1) {
		pres[i] = prel[i] = 1e18;
		if (i > 1) pres[i] = min(pres[i],min(pres[i-2],prel[i-2])+Z*abs(v[i-1].s-v[i-2].s));
		if (i > 3) prel[i] = min(prel[i],prel[i-2]+Z*abs(v[i-2].s-v[i-3].s));
		
		//cout << i << " " << pres[i] << " " << prel[i] << "\n";
		if (i >= 2) p[i] = p[i-2];
		else p[i] = 0;
		
		while (Z*abs(v[i-1].s-v[p[i]].s) > X+Y) {
			if ((i-1-p[i]) % 2 == 1) 
				prel[i] = min(prel[i],min(pres[p[i]],prel[p[i]])+X+Y+Z*cum(p[i]+1,i-2));
			p[i] ++;
		}
		//cout << i << " " << pres[i] << " " << prel[i] << "\n";
	}
}

void gensuf(vector<pair<char,int>>& v1) {
	vector<pair<char,int>> v = v1;
	reverse(v.begin(),v.end());
	
	FOR(i,2,v.size()) {
		cu[i] = abs(v[i].s-v[i-1].s);
		if (i > 1) cu[i] += cu[i-2];
	}
	
	FOR(i,1,v.size()+1) {
		sufs[i] = sufl[i] = 1e18;
		if (i > 1) sufs[i] = min(sufs[i],min(sufs[i-2],sufl[i-2])+Z*abs(v[i-1].s-v[i-2].s));
		if (i > 3) sufl[i] = min(sufl[i],sufl[i-2]+Z*abs(v[i-2].s-v[i-3].s));
		
		if (i >= 2) p[i] = p[i-2];
		else p[i] = 0;
		
		while (Z*abs(v[i-1].s-v[p[i]].s) > X+Y) {
			if ((i-1-p[i]) % 2 == 1) 
				sufl[i] = min(sufl[i],min(sufs[p[i]],sufl[p[i]])+X+Y+Z*cum(p[i]+1,i-2));
			p[i] ++;
		}
	}
}

ll test(vector<pair<char,int>>& v) {
	genpre(v);
	if (v.size() % 2 == 0) return min(pres[v.size()],prel[v.size()]);
	//F0R(i,v.size()+1) cout << i << " " << min(pres[i],prel[i]) << "\n";
	gensuf(v);
	
	ll mn = 1e18;
	F0R(i,v.size()/2+1) 
		mn = min(mn,min(prel[2*i],pres[2*i])+min(sufs[v.size()-1-2*i],sufl[v.size()-1-2*i])+((v[0].f == 'A') ? Y : X));

	return mn;
}

char lst = '.';

int main() {
	ifstream cin ("landscape.in");
	ofstream cout ("landscape.out");
	cin >> N >> X >> Y >> Z; // answer 1026
	F0R(i,N) {
		int A,B; cin >> A >> B;
		while (A>B) {
			if (lst == 'A') co++;
			flo[co].pb({'A',i}); // extra
			lst = 'A';
			A--;
		}
		while (A<B) {
			if (lst == 'B') co--;
			flo[co].pb({'B',i}); // need
			lst = 'B';
			B--;
		}
	}
	F0R(i,2000001) {
		ans += test(flo[i]);
	}
	cout << ans;
}
