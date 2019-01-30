//if you have any questions, you can pm me on codeforces (username: golions)
#include <bits/stdc++.h>

using namespace std;

#define MAXN 100005



int n;
int bits[MAXN];                           //for fenwick tree - stores number of already sorted numbers.

//fenwick tree methods
void update(int i, int x){
   for(; i <= n; i += i&-i){
      bits[i] += x;
   }
}

int psum(int i){
   int sum = 0;
   for(; i > 0; i -= i&-i){
      sum += bits[i];
   }
   return sum;
}


int main(){
   ios::sync_with_stdio(false);
   cin.tie(0);
   
   ifstream fin ("sleepy.in");
   ofstream fout ("sleepy.out");
   
   fin >> n;
   
   int array[n];
   
   for(int k = 0; k < n; k++){
      fin >> array[k];
   }
   
   //find longest sorted suffix. You will need to move every number in front of this suffix.
   int t = n-1;
   update(array[t],1);
   while(t >= 1 && array[t] > array[t-1]){
      t--;
      update(array[t],1);
   }
   
   
   //t is length of numbers that need to be moved
   fout << t << endl;
   
   for(int k = 0; k < t; k++){
      //the formula for the distance is t - k - 1 + (number of already sorted numbers before that number)
      int ans = t - k - 1 + psum(array[k]);
      fout << ans;
      if(k < t-1) fout << " ";                     //annoying output format
      
      //array[k] has been sorted, so update the fenwick tree
      update(array[k],1);
   }
   
   fout << endl;
   
   return 0;
}

