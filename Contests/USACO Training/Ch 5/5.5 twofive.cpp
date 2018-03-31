/*
ID: bqi3431
PROG: twofive
LANG: C++11
*/

#include<vector>
#include<fstream>
#include<map>

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

struct state {
    int todo;
    pair<int,char> row[5];
    pair<int,char> col[5];
    
    state() {
        todo = (1<<25)-1;
        F0R(i,5) row[i] = col[i] = {0,'.'};
    }
    
    bool operator<(const state& rhs) const {
        if (todo != rhs.todo) return (todo < rhs.todo);
        F0R(i,5) {
            if (row[i].f != rhs.row[i].f) return (row[i].f < rhs.row[i].f);
            if (row[i].s != rhs.row[i].s) return (row[i].s < rhs.row[i].s);
        }
        F0R(i,5) {
            if (col[i].f != rhs.col[i].f) return (row[i].f < rhs.col[i].f);
            if (col[i].s != rhs.col[i].s) return (row[i].s < rhs.col[i].s);
        }
        return false;
    }
};

state cur;
map<state,int> rec;

int get(state c) {
    if (c.todo == 0) return 1;
    
    int nex = __builtin_ctz(c.todo);
    F0R(i,5) {
        if (c.row[i].s < ('A'+nex)) c.row[i].s = '.';
        if (c.col[i].s < ('A'+nex)) c.col[i].s = '.';
    }
    
    if (rec.find(c) != rec.end()) return rec[c];
    
    int ret = 0;
    F0R(i,5) {
        if (i == 0 && c.row[i].f == 5) continue;
        if (c.row[i].f == c.row[i-1].f) continue;
        if (c.row[i].s > ('A'+nex)) continue;
        if (c.col[c.row[i].f].s > ('A'+nex)) continue;
        
        state c1 = c;
        c1.col[c1.row[i].f].s = ('A'+nex);
        c1.col[c1.row[i].f].f ++;
        c1.row[i].s = ('A'+nex);
        c1.row[i].f ++;
        c1.todo ^= (1<<nex);
        
        ret += get(c1);
    }
    return rec[c] = ret;
}

string solve1(int M) {
    int ans = 0;
    string ret;
    
    F0R(i,25) {
        FOR(j,max(0,max(cur.row[i/5].s-'A',cur.col[i%5].s-'A')+1),25) 
            if (cur.todo & (1<<j))  {
                state cur1 = cur;
                cur1.row[i/5].f ++;
                cur1.col[i%5].f ++;
                cur1.row[i/5].s = ('A'+j);
                cur1.col[i%5].s = ('A'+j);
                cur1.todo ^= (1<<j);
                ans += get(cur1);
                
                if (ans >= M) {
                    ans -= get(cur1);
                    ret += ('A'+j);
                    cur.row[i/5].f ++;
                    cur.col[i%5].f ++;
                    cur.row[i/5].s = ('A'+j);
                    cur.col[i%5].s = ('A'+j);
                    cur.todo ^= (1<<j);
                    break;
                }
            }
    }
    
    return ret;
}

int solve2(string W) {
    int ans = 1;
    F0R(i,25) {
        FOR(j,max(0,max(cur.row[i/5].s-'A',cur.col[i%5].s-'A')+1),W[i]-'A') 
            if (cur.todo & (1<<j)) {
                state cur1 = cur;
                cur1.row[i/5].f ++;
                cur1.col[i%5].f ++;
                cur1.row[i/5].s = ('A'+j);
                cur1.col[i%5].s = ('A'+j);
                cur1.todo ^= (1<<j);
                ans += get(cur1);
            }
        
        cur.row[i/5].f ++;
        cur.col[i%5].f ++;
        cur.row[i/5].s = W[i];
        cur.col[i%5].s = W[i];
        cur.todo ^= (1<<(W[i]-'A'));
    }
    return ans;
}

int main() {
    ifstream cin ("twofive.in");
    ofstream cout ("twofive.out");
	char type; cin >> type;
	if (type == 'N') {
	    int M; cin >> M;
	    cout << solve1(M) << "\n";
	} else {
	    string W; cin >> W;
	    cout << solve2(W) << "\n";
	}
}
