/*
ID: bqi3431
PROG: prefix
LANG: C++11
*/

#include<iostream>
#include<fstream>
#include<vector>

using namespace std;
 
#define FOR(i, a, b) for (int i=a; i<b; i++)
#define pb push_back

//ifstream cin ("prefix.in");
//ofstream cout ("prefix.out");

int dp[200001], ans = 0;
vector<string> p;

int main() {
	string s,s1;
	while (cin >> s1) {
		if (s1 == ".") break;
		p.pb(s1);
	}
	while (cin >> s1) s += s1;
	dp[0] = 1;
	FOR(i,1,s.length()+1) for (string k: p) if (k.length() <= i) 
		if (dp[i-k.length()] && s.substr(i-k.length(),k.length()) == k) {
			dp[i] = 1;
			ans = i;
			break;
		}
	cout << ans << "\n";
}