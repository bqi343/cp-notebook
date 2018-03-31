/*
ID: bqi3431
PROG: calfflac
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;
 
typedef long long ll;
typedef pair <int, int> pi;
typedef vector<int> vi;

#define mp make_pair
#define pb push_back

#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)
#define F0Rd(i, a) for (int i=(a)-1; i>=0; i--)
 
#define f first
#define s second
 
// ifstream cin ("calfflac.in");
// ofstream cout ("calfflac.out");

int key[20000], a = -1, b = -1;
vector<vector<bool>> works;
vector<char> des;
string act;

int main() {
	char c; 
	int co = 0;
	while (cin >> noskipws >> c) {
		act += c;
		c = tolower(c);
		if ('a' <= c && c <= 'z') {
			key[des.size()] = co;
			des.pb(c);
		}
		co++;
	}
	works.resize(min((int)des.size()+1,2001));
	FOR(j,1,min(2001,(int)des.size()+1)) {
		works[j].resize(20000);
		F0Rd(i,des.size()-j+1) { 
			if (j <= 2) {
				if (des[i] == des[i+j-1]) {
					works[j][i] = 1;
					a = i, b = i+j-1;
				}
			} else {
				if (des[i] == des[i+j-1] && works[j-2][i+1]) {
					works[j][i] = 1;
					a = i, b = i+j-1;
				}
			}
		}
		if (j-2>0) works[j-2].clear();
	}
	cout << (b-a+1) << "\n" << act.substr(key[a],key[b]-key[a]+1) << "\n";
}
