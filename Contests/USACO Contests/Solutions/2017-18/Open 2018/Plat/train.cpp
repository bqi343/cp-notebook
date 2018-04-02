#include "grader.h"
#include <vector>
#include <utility>
#include <iostream>
#include <cassert>

using namespace std;
 
typedef pair<int, int> pi;

typedef vector<int> vi;
typedef vector<pi> vpi;

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
#define all(x) x.begin(), x.end()

int N,K, carIndex, passIndex;
int L,R, nex, outputs;
pi mn;

/*int num, sec[5500];
vi ans;

int get(int index) { num ++; return sec[index]; }
void set(int index, int value) { num ++; sec[index] = value; }
void shoutMinimum(int output) { 
    ans.pb(output);
}*/

const int INF = 2000000000;

/*int getTrainLength() { return N; }
int getWindowLength() { return K; }
int getCurrentCarIndex() { return carIndex; }
int getCurrentPassIndex() { return passIndex; }*/

namespace Deque {
    void clear() { L = R = 0; }
    void pop_back() { R = (R+4100-2)%4100; }
    void pop_front() { L = (L+2)%4100; }
    void push_back(pi x) {
        set(R,x.f), set(R+1,x.s);
        R = (R+2)%4100;
    }
    
    int front(int ind) { 
        return L == R ? INF : get(L+ind); 
    } 
    int back(int ind) { return L == R ? -1 : get((R+4100-2+ind)%4100); }
    
    void ad(pi x) {
        while (back(0) > x.f) pop_back();
        push_back(x);
    }
    
    void truncate(int mn) { while (front(1) < mn) pop_front(); }
}

void initVariable() {
    N = getTrainLength();
    K = getWindowLength();
    carIndex = getCurrentCarIndex();
    passIndex = getCurrentPassIndex();
}

void solve0(int ID) {
    // get the index for 0 to K-1, 1000 to 1000+K-1, 2000 to 2000+K-1
    
    if (carIndex == 0) mn = {INF,INF};
    else mn = {get(5496),get(5497)};
    
    mn = min(mn,{ID,carIndex});
    if (carIndex % 1000 == (K-1) % 1000) {
        L = get(5498), R = get(5499);
        Deque::ad(mn); mn = {INF,INF};
        Deque::truncate(carIndex-K+1);
        if (carIndex >= K-1) set((carIndex-K+1)/1000+4100,Deque::front(1));
        set(5498,L), set(5499,R);
    } else if (carIndex % 1000 == 999) {
        L = get(5498), R = get(5499);
        Deque::ad(mn); mn = {INF,INF};
        set(5498,L), set(5499,R);
    }
    
    set(5496,mn.f), set(5497,mn.s);
}

void setVariable() {
    set(5498,L), set(5499,R);
    set(5494,nex); set(5493, outputs);
}

void getVariable() {
    L = get(5498), R = get(5499);
    nex = get(5494), outputs = get(5493);
}

void output() {
    Deque::truncate(outputs);
    shoutMinimum(min(get(5495),Deque::front(0)));
    outputs++;
}

void solve1(int ID) {
    if (carIndex == 0) {
        set(5495,INF);
        set(5498,0);
        set(5499,0);
    }
    if (carIndex < get(4100)) return;
    
    getVariable();
    
    if (carIndex < 1000+1000*nex) Deque::ad({ID,carIndex});
    else set(5495,min(get(5495),ID));
    if (outputs+K-1 == carIndex) output();
    
    while (1000*nex+K-1 < N && get(4100+nex) == carIndex) { // mostly editorial code :/
        while(outputs <= 1000*nex) output();
        nex ++; set(5495,INF);
        Deque::clear(); Deque::pb({ID,carIndex});
    }
    
    setVariable();
}

void helpBessie(int ID) { 
    initVariable();
    if (passIndex == 0) solve0(ID);
    else solve1(ID);
}

/*int A[1000000];

int main() {
    F0R(z,1) {
        ans.clear();
        F0R(i,5500) sec[i] = 0;
        N = 5993;
        K = 2016;
        F0R(i,N) {
            A[i] = i;
            // cin >> A[i];
        }
        F0R(j,2) F0R(i,N) {
            carIndex = i, passIndex = j;
            helpBessie(A[i]);
        }
        F0R(i,sz(ans)) {
            int j = INF; FOR(k,i,i+K) j = min(j,A[k]);
            if (ans[i] != j) cout << "OOPS " << z << " " << i << " " << ans[i] << " " << j << "\n";
        }
    }
}*/

// read the question correctly (is y a vowel?)
// look out for SPECIAL CASES (n=1?) and overflow (ll vs int?)