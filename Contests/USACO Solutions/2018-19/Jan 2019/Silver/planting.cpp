#include <bits/stdc++.h>

using namespace std;


//answer is the (maximum number of neighbors a vertex has) + 1

int main(){
   ios::sync_with_stdio(false);
   cin.tie(0);
   
   ifstream fin ("planting.in");
   ofstream fout ("planting.out");
   
   int n;
   fin >> n;
   
   vector<vector<int>> adj(n+1);
   
   for(int k = 0; k < n-1; k++){
      int a,b;
      fin >> a >> b;
      
      adj[a].push_back(b);
      adj[b].push_back(a);
   }
   
   int answer = 0;
   for(int k = 1; k <= n; k++){  
      answer = max(answer,static_cast<int>(adj[k].size()));
   }
   
   cout << answer+1;
   fout << answer+1;
   
   
   
   
   
   
   return 0;
}