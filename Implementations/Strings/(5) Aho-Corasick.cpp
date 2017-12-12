// http://www.geeksforgeeks.org/aho-corasick-algorithm-pattern-searching/

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