//if you have questions, you can pm me on codeforces (username: golions)
#include <bits/stdc++.h>

#define MAXN 5005
#define MAXM 100005
#define MAXS 5005


using namespace std;

long long MOD = 1000000007;

//fast exponentiation - for more information, see https://www.geeksforgeeks.org/exponential-squaring-fast-modulo-multiplication/
long long exp(int base, int power){
   if(power == 0) return 1;
   if(power == 1) return (base + MOD) % MOD;
   long long ans = exp(base,power/2);
   ans = (ans * ans + MOD) % MOD;
   if(power%2 == 1) ans = (ans*base + MOD) % MOD;
   return (ans + MOD) % MOD;
}

int n,m,s;
long long dp[MAXS];                       //dp[x] = the number of ways to make a line with x syllables.
long long r[MAXN];                        //r[x] = the number of ways to form a full line that ends with rhyme scheme x

unordered_map<char,int> umap;

int main(){
   ios::sync_with_stdio(false);
   cin.tie(0);
   
   ifstream fin ("poetry.in");
   ofstream fout ("poetry.out");
   
   int n,m,s;
   fin >> n >> m >> s;
   
   pair<int,int> words[n];          //first is syllables, second is rhyme
   
   for(int k = 0; k < n; k++){
      int a,b;
      fin >> a >> b;
      words[k] = make_pair(a,b);
   }
   
   //Calculate frequencies of every rhyme (Order of rhymes doesn't matter)
   for(int k = 0; k < m; k++){
      char c;
      fin >> c;
      if(umap.find(c) == umap.end()){
         umap[c] = 1;
      } else{
         umap[c]++;
      }
   }
   
   
   dp[0] = 1;
   
   for(int k = 0; k <= s; k++){
      
      for(int j = 0; j < n; j++){
         if(words[j].first + k > s) continue;
         if(words[j].first + k == s){
            r[words[j].second] = (r[words[j].second] + dp[k] + MOD) % MOD;                      //if you are at the end of the line, update r
         } else {
            dp[words[j].first + k] = (dp[words[j].first + k] + dp[k] + MOD) % MOD;              //knapsack dp
         }
      }
   }
   
   long long answer = 1;
   for(auto a : umap){
      //use counting/probability to calculate the answer. For every grouping of a rhyme, multiple the answer by r[1]^freq, r[2]^freq, etc.
      //For instance, the answer for the sample case is (8^2 + 4^2) * (8^1 + 4^1). r[1] = 8 and r[2] = 4, and the are 2 As and 1 B.
      
   
      int freq = a.second;
      long long sum = 0;
      for(int k = 0; k <= n; k++){
         if(r[k] == 0) continue;
         sum = (sum + exp(r[k],freq) + MOD) % MOD;
      }
      answer = (answer * sum + MOD) % MOD;
   }
   
   cout << answer;
   fout << answer;
         
   
   
   
   return 0;
}