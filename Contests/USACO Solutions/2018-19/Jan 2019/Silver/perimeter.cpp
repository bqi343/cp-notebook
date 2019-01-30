#include <bits/stdc++.h>

using namespace std;

#define MAXN 1005

bool seen[MAXN][MAXN];
int size = 0;
int peri = 0;
string board[MAXN];
int n;

bool in(int x, int y, int n){
   return x >= 0 && y >= 0 && x < n && y < n;
}

//basic floodfill
void dfs(int x, int y){
   seen[x][y] = true;
   
   size++;
   
   if(!in(x+1,y,n) || board[x+1][y] == '.') peri++;
   if(!in(x-1,y,n) || board[x-1][y] == '.') peri++;
   if(!in(x,y+1,n) || board[x][y+1] == '.') peri++;
   if(!in(x,y-1,n) || board[x][y-1] == '.') peri++;
   
   if(in(x+1,y,n) && board[x+1][y] == '#' && !seen[x+1][y]) dfs(x+1,y);
   if(in(x-1,y,n) && board[x-1][y] == '#' && !seen[x-1][y]) dfs(x-1,y);
   if(in(x,y+1,n) && board[x][y+1] == '#' && !seen[x][y+1]) dfs(x,y+1);
   if(in(x,y-1,n) && board[x][y-1] == '#' && !seen[x][y-1]) dfs(x,y-1);
}

int main(){
   ios::sync_with_stdio(false);
   cin.tie(0);
   
   ifstream fin ("perimeter.in");
   ofstream fout ("perimeter.out");
   
   fin >> n;
   
   for(int k = 0; k < n; k++){
      fin >> board[k];
   }      
   
   int maxsize = 0;
   int maxperi = 0;
   
   for(int k = 0; k < n; k++){
      for(int j = 0; j < n; j++){
         if(seen[k][j] || board[k][j] == '.') continue;
         size = 0;
         peri = 0;
         dfs(k,j);
         if(size > maxsize){
            maxsize = size;
            maxperi = peri;
         } else if(size == maxsize && peri < maxperi){
            maxperi = peri;
         }
      }
   }
   
   
   
   cout << maxsize << " " << maxperi;
   fout << maxsize << " " << maxperi;
   
   
   
   
   
   return 0;
}