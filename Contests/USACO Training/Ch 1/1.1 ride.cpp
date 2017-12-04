/*
ID: bqi3431
PROG: ride
LANG: C++11
*/
 
#include <fstream>
 
using namespace std;
 
int main() {
	ifstream cin ("ride.in");
	ofstream cout ("ride.out");
    string a,b; cin >> a >> b;
    int n1=1,n2=1;
    for (char a1: a) n1 = (n1*(a1-'A'+1)) % 47;
    for (char b1: b) n2 = (n2*(b1-'A'+1)) % 47;
    if (n1 == n2) cout << "GO";
    else cout << "STAY";
    cout << "\n";
}