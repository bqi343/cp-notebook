#include <bits/stdc++.h>

using namespace std;


//custom comparator for pairs. sorts by increasing order of first, and decreasing order of second if firsts are equal
bool compair(pair<int,int> p1, pair<int,int> p2){
   if(p1.first == p2.first) 
      return p1.second > p2.second;
   return p1.first < p2.first;
}



int main(){
   ios::sync_with_stdio(false);
   cin.tie(0);
   
   ifstream fin ("mountains.in");
   ofstream fout ("mountains.out");
   
   int n;
   fin >> n;
   
   vector<pair<int,int>> array;
   
   for(int k = 0; k < n; k++){
      int a,b;
      fin >> a >> b;
      
      //make pairs with the left and right coordinate of the baseline of the mountain.
      array.push_back(make_pair(a-b,a+b));
   }
   
   //sort the array based on the custom comparator
   sort(array.begin(),array.end(),compair);
   
   pair<int,int> cur = array[0];
   
   int count = 1;
   
   //used to check if a mountain is surrounded by another mountain.
   int thresh = cur.second;
   
   //for every pair, if second is <= thresh, it is surrounded by another mountain. If second > thresh, it can be seen so increment count and update thresh.
   for(int k = 1; k < n; k++){   
      if(array[k].second > thresh){
         count++;
         thresh = array[k].second;
      }
   }
   
   cout << count;
   fout << count;

   return 0;
}