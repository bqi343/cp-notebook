#include<fstream>
#include<iostream>
#include<map>
 
using namespace std;

#define F0R(i, a) for (int i=0; i<a; i++)
  
#define f first
#define s second

map<pair<string,string>,int> times;
 
int main() {
    // ifstream cin ("citystate.in");
    // ofstream cout ("citystate.out");
    int N; cin >> N;
    F0R(i,N) {
        string a,b; cin >> a >> b;
        a = a.substr(0,2);
        if (a != b) times[{a,b}]++;
    }
    long long ans = 0;
    for (auto a: times) ans += a.s*times[{a.f.s,a.f.f}];
    cout << ans/2;
}