#include <bits/stdc++.h>

using namespace std;





int main(){
   ios::sync_with_stdio(false);
   cin.tie(0);
   
   ifstream fin ("walk.in");
   ofstream fout ("walk.out");
   
   int n,k;
   fin >> n >> k;
   int answer = 2019201997 - 48*n - 84*(k-1);
   fout << answer << endl; 
   
   
   
   
   
   
   
   
   
   return 0;
}