/*
ID: bqi3431
PROG: cowcycle
LANG: C++11
*/

// #include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;
 
typedef vector<int> vi;

#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)
 
#define mp make_pair
#define pb push_back
#define f first
#define s second

const int MOD = 1000000007;

vi Fa, Ra;
double mn = MOD;

int F,R,F1,F2,R1,R2; 

void solve (vi a, vi b) {
	vector<double> x;
	double ans = 0;
	F0R(i,F) F0R(j,R) x.pb((double)a[i]/b[j]);
	sort(x.begin(),x.end());
	double mean = (x[F*R-1]-x[0])/(F*R-1);
	F0R(i,F*R-1) {
		double dif = x[i+1]-x[i];
		ans += (dif-mean)*(dif-mean);
	}
	if (ans<mn) {
		mn = ans;
		Fa = a;
		Ra = b;
	}
}

int main() {
	ifstream cin ("cowcycle.in");
	ofstream cout ("cowcycle.out");
	
	cin >> F >> R >> F1 >> F2 >> R1 >> R2;
    string FF(F,'1'); FF.resize(F2-F1+1,'0');
    string RR(R,'1'); RR.resize(R2-R1+1,'0'); 
	vector<vi> rposi;
	do {
		vi temp;
		F0R(i,R2-R1+1) if (RR[i] == '1') temp.pb(i+R1);
		rposi.pb(temp);
	} while(prev_permutation(RR.begin(), RR.end())) ;
    mn = MOD, Fa.clear(), Ra.clear();
    do {
    	string RR1 = RR;
    	vi front;
    	F0R(i,F2-F1+1) if (FF[i] == '1') front.pb(i+F1);
    	F0R(i,rposi.size()) {
    		double k = (double)front[F-1]*rposi[i][R-1]/(front[0]*rposi[i][0]);
    		if (k<3) continue;
    		solve(front,rposi[i]);
    	} 
	    RR = RR1;
    } while (prev_permutation(FF.begin(), FF.end()));
    // solve({25,30,31,32,33},{7,8,9,10,11,12,13,14,15,16});
    F0R(i,Fa.size()) {
		cout << Fa[i];
		if (i != F-1) cout << " ";
		else cout << "\n";
	}
	F0R(i,Ra.size()) {
		cout << Ra[i];
		if (i != R-1) cout << " ";
	    else cout << "\n";
	}
}