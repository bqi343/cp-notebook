#include <bits/stdc++.h>
 
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
double PI = 4*atan(1);
 
int N,M,K;
string s;
int card[14][8]; // 0 is lose, 1 is win
 
bool gen(int cturn, ll cdist) {
    if (cturn == N) return min(cdist,M-cdist) <= K;
     
    if (rand()&1) {
        if(gen(cturn+1,(cdist*(card[cturn][4]+1)+card[cturn][5]) % M)&&gen(cturn+1,(cdist*(card[cturn][6]+1)+card[cturn][7]) % M)) return 1;
    } else {
        if(gen(cturn+1,(cdist*(card[cturn][6]+1)+card[cturn][7]) % M)&&gen(cturn+1,(cdist*(card[cturn][4]+1)+card[cturn][5]) % M)) return 1;
    }
     
    if (rand()&1) {
        if (gen(cturn+1,(cdist*(card[cturn][0]+1)+card[cturn][1]) % M)&&gen(cturn+1,(cdist*(card[cturn][2]+1)+card[cturn][3]) % M)) return 1;
    } else {
        if (gen(cturn+1,(cdist*(card[cturn][2]+1)+card[cturn][3]) % M)&&gen(cturn+1,(cdist*(card[cturn][0]+1)+card[cturn][1]) % M)) return 1;
    }
     
    return 0;
}
 
void init() {
    srand(38);
    ios_base::sync_with_stdio(0);cin.tie(0);
    cin >> N >> M >> K >> s;
    F0R(i,N) F0R(j,8) cin >> card[i][j];
}
 
int main() {
    init();
    ll cdist = 0;
    string ans;
    F0R(i,N) {
        int cturn = i;
        bool c = gen(cturn+1,(cdist*(card[cturn][4]+1)+card[cturn][5]) % M);
        bool d = gen(cturn+1,(cdist*(card[cturn][6]+1)+card[cturn][7]) % M);
        if (c&d) {
            cout << 'B';
            if (s[i] == 'B') cdist = (cdist*(card[cturn][6]+1)+card[cturn][7]) % M;
            else cdist = (cdist*(card[cturn][4]+1)+card[cturn][5]) % M;
        } else {
            cout << 'T';
            if (s[i] == 'B') cdist = (cdist*(card[cturn][2]+1)+card[cturn][3]) % M;
            else cdist = (cdist*(card[cturn][0]+1)+card[cturn][1]) % M;
        }
    }
}
