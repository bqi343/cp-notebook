/**
* Description: Uses gaussian elimination to solve a system of linear equations
* Usage: https://open.kattis.com/problems/equationsolverplus
*/

typedef long double ld;
typedef vector<vector<ld>> mat;

ld EPS = 1e-10;
int n;

void elim(mat& a, int i, int j, int k) {
    ld t = a[k][i];
    F0R(ind,n+1) a[k][ind] -= t*a[j][ind];
}

void prin(mat& a) {
    F0R(i,n) {
        F0R(j,n+1) cout << a[i][j] << " ";
        cout << "\n";
    }
    cout << "----\n";
}

void solve() {
    mat a(n); F0R(i,n) a[i].resize(n+1);
    F0R(i,n) F0R(j,n) cin >> a[i][j];
    F0R(i,n) cin >> a[i][n];
    int done[n]; F0R(i,n) done[i] = -1;

    F0R(i,n) {
        F0R(j,n) if (done[j] == -1 && abs(a[j][i]) > EPS) {
            ld t = a[j][i];
            F0R(k,n+1) a[j][k] /= t;
            
            F0R(k,n) if (j != k) elim(a,i,j,k);
            done[j] = i; break;
        }
    }
    
    int num = 0;
    F0R(i,n) if (done[i] == -1) {
        num ++;
        if (abs(a[i][n]) > EPS) {
            cout << "inconsistent\n";
            return;
        }
    }
    ld ans[n]; F0R(i,n) ans[i] = numeric_limits<double>::max();
    F0R(i,n) if (done[i] != -1) {
        bool bad = 0;
        F0R(j,n) if (j != done[i] && abs(a[i][j]) > EPS) {
            bad = 1;
            break;
        }
        if (!bad) ans[done[i]] = a[i][n];
    }
    F0R(i,n) {
        if (ans[i] != numeric_limits<double>::max()) cout << ans[i];
        else cout << "?";
        cout << " ";
    }
    cout << "\n";
}
