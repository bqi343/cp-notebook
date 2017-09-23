// http://www.geeksforgeeks.org/aho-corasick-algorithm-pattern-searching/

#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;
 
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
template <class T> using Tree = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;

#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)

#define sz(x) (int)(x).size()
#define mp make_pair
#define pb push_back
#define f first
#define s second
#define lb lower_bound
#define ub upper_bound

const int MOD = 1000000007;

string arr[200];
int val[200], states = 1;

const int MAXS = 201;
const int MAXC = 26;
 
int n, out[MAXS], f[MAXS], g[MAXS][MAXC];

int buildMatchingMachine() {
    memset(out, 0, sizeof out);
    memset(g, -1, sizeof g);
    
    F0R(i,n) {
        string word = arr[i];
        int currentState = 0;
 
        F0R(j,word.size()) {
            int ch = word[j] - 'a';
            if (g[currentState][ch] == -1) g[currentState][ch] = states++;
            currentState = g[currentState][ch];
        }
 
        out[currentState] += val[i];
    }
 
    F0R(ch,MAXC) if (g[0][ch] == -1) g[0][ch] = 0;
    memset(f, -1, sizeof f);
    queue<int> q;
 
    F0R(ch,MAXC) 
        if (g[0][ch] != 0) {
            f[g[0][ch]] = 0; 
            q.push(g[0][ch]);
        }
 
    while (q.size()) {
        int state = q.front();
        q.pop();
 
        F0R(ch,MAXC) {
            if (g[state][ch] != -1) {
                int failure = f[state];
                while (g[failure][ch] == -1) failure = f[failure];
 
                failure = g[failure][ch];
                f[g[state][ch]] = failure;

                out[g[state][ch]] += out[failure];
 
                q.push(g[state][ch]);
            }
        }
    }
 
    return states;
}
 
int findNextState(int currentState, char nextInput) {
    int answer = currentState;
    int ch = nextInput - 'a';

    while (g[answer][ch] == -1) answer = f[answer];
    return g[answer][ch];
}

int main() {

}