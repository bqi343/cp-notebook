#include<fstream>
#include<vector>
#include<cstring>
// #include<iostream>

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

// N^3 suffices
int N, cum[301][301];
int ans = -1;
short lst[300][300][300], fst[300][300][300];
int best[300][300];
char grid[300][300];

int get(int ind, int i, int j) {
    return cum[ind][j+1]-cum[ind][i];    
}

int get(int ind) {
    memset(best,0,sizeof best);
    int res = -1;
    FOR(i,3,N+1) F0R(j,N+1-i) {
        best[j][i] = max(best[j+1][i-1], best[j][i-1]);
        if (fst[ind][j][j+i-1] < ind-1) best[j][i] = max(best[j][i],(ind-fst[ind][j][j+i-1]-1)*(i-2));
        if (get(ind,j,j+i-1) > 0) continue;
        if (lst[ind][j][j+i-1] > ind+1 && best[j][i] > 0) 
            res = max(res,(i-2)*(lst[ind][j][j+i-1]-ind-1)*best[j][i]);
    }
    return res;
}

void genfst() {
    F0R(ind,N) {
        F0R(i,N) FOR(j,i+1,N) {
            fst[ind][i][j] = 500;
            if (ind > 0 && grid[ind][i] == '.' && grid[ind][j] == '.') fst[ind][i][j] = fst[ind-1][i][j];
            if (get(ind,i,j) == 0) fst[ind][i][j] = min(fst[ind][i][j],(short)ind);
        }
    }
}

void genlst() {
    F0Rd(ind,N) {
        F0R(i,N) FOR(j,i+1,N) {
            lst[ind][i][j] = -500;
            if (ind < N-1 && grid[ind][i] == '.' && grid[ind][j] == '.') lst[ind][i][j] = lst[ind+1][i][j];
            if (get(ind,i,j) == 0) lst[ind][i][j] = max(lst[ind][i][j],(short)ind);
        }
    }
}

int main() {
    ifstream cin ("eight.in");
    ofstream cout ("eight.out");
    
	cin >> N;
	F0R(i,N) F0R(j,N) {
	    cin >> grid[i][j];
	    cum[i][j+1] = cum[i][j] + (grid[i][j] == '*' ? 1 : 0);
	}
	genfst();
	genlst();
	F0R(i,N) ans = max(ans,get(i));
	cout << ans;
}
