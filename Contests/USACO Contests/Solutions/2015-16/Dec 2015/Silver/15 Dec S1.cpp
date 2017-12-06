// #include <iostream>
#include <utility>
#include <fstream>
#include <algorithm>
#include <string>

using namespace std;

struct switchs {
    int posx,posy,newx,newy;
    int used = 0;
};

ifstream cin ("lightson.in");
ofstream cout ("lightson.out");

int grid[102][102], reachable[102][102];
switchs a[20000];

int main () {
    int N, M, ans = 0;
    cin >> N >> M;
    reachable[1][1] = 1;
    reachable[1][2] = 1;
    reachable[2][1] = 1;
    grid[1][1] = 1;
    for (int i = 0; i < M; ++i) {
        cin >> a[i].posx >> a[i].posy >> a[i].newx >> a[i].newy;
    }
    
    bool check = true;
    while (check == true) {
        check = false;
        for (int i = 1; i <= N; ++i) {
            for (int j = 1; j <= N; ++j) {
                if (grid[i][j] && reachable[i][j]) {
                    if (reachable[i][j+1] == 0) {
                        reachable[i][j+1] = 1;
                        check = true;
                    }
                    if (reachable[i][j-1] == 0) {
                        reachable[i][j-1] = 1;
                        check = true;
                    }
                    if (reachable[i+1][j] == 0) {
                        reachable[i+1][j] = 1;
                        check = true;
                    }
                    if (reachable[i-1][j] == 0) {
                        reachable[i-1][j] = 1;
                        check = true;
                    }
                }
            }
        }
        
        for (int i = 0; i < M; ++i) {
            if (a[i].used == 0 && grid[a[i].posx][a[i].posy] && reachable[a[i].posx][a[i].posy]) {
                grid[a[i].newx][a[i].newy] = 1;
                a[i].used = 1;
                check = true;
            }
        }
    }
    
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            if (grid[i][j]) {
                ans ++;
            }
        }
    }
    cout << ans;
}
