//if you have questions, you can pm me on codeforces (username: golions)
/*
TASK: poetry
LANG: JAVA
*/

import java.io.*;
import java.util.*;

class poetry{
   
   public static long MOD = 1000000007L;
   
   public static void main(String[] args) throws IOException{
      BufferedReader f = new BufferedReader(new FileReader("poetry.in"));
      PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("poetry.out")));
      
      StringTokenizer st = new StringTokenizer(f.readLine());
      
      int n = Integer.parseInt(st.nextToken());
      int m = Integer.parseInt(st.nextToken());
      int s = Integer.parseInt(st.nextToken());
      
      Word[] words = new Word[n];
      
      for(int k = 0; k < n; k++){
         
         st = new StringTokenizer(f.readLine());
      
         int sy = Integer.parseInt(st.nextToken());
         int rh = Integer.parseInt(st.nextToken());
      
         words[k] = new Word(sy,rh);
      }
      
      
      //Calculate frequencies of every rhyme (Order of rhymes doesn't matter)
      HashMap<Character,Integer> hmap = new HashMap<Character,Integer>();
      
      
      for(int k = 0; k < m; k++){
         char c = f.readLine().charAt(0);
         if(hmap.containsKey(c)){
            hmap.put(c,hmap.get(c)+1);
         } else {
            hmap.put(c,1);
         }
      }
      
      //dp[x] = the number of ways to make a line with x syllables.
      long[] dp = new long[s+1];
      dp[0] = 1L;
      
      //r[x] = the number of ways to form a full line that ends with rhyme scheme x
      long[] r = new long[n+1];
      
      for(int k = 0; k <= s; k++){
         
         for(int j = 0; j < n; j++){
            if(words[j].s + k > s) continue;
            if(words[j].s + k == s){
               r[words[j].r] = (r[words[j].r] + dp[k] + MOD) % MOD;                 //if you are at the end of the line, update r
            }
            dp[words[j].s + k] = (dp[words[j].s + k] + dp[k] + MOD) % MOD;          //knapsack dp
         }
      }      
      
      
      long answer = 1L;
      for(char c : hmap.keySet()){
         //use counting/probability to calculate the answer. For every grouping of a rhyme, multiple the answer by r[1]^freq, r[2]^freq, etc.
         //For instance, the answer for the sample case is (8^2 + 4^2) * (8^1 + 4^1). r[1] = 8 and r[2] = 4, and the are 2 As and 1 B.
      
         int freq = hmap.get(c);
         long sum = 0L;
         for(int k = 0; k < r.length; k++){
            if(r[k] == 0) continue;
            sum = (sum + exp(r[k],freq) + MOD) % MOD;
         }
      
         answer = (answer * sum + MOD) % MOD;
      }
      
      System.out.println(answer);
      out.println(answer);
      
         
      
      
      
        
      out.close();
   }
   
   
   //fast exponentiation - for more information, see https://www.geeksforgeeks.org/exponential-squaring-fast-modulo-multiplication/
   public static long exp(long base, int power){
      if(power == 0) return 1;
      if(power == 1) return (base + MOD) % MOD;
      long ans = exp(base,power/2);
      ans = (ans*ans + MOD) % MOD;
      if(power%2 == 1) ans = (ans*base + MOD) % MOD;
      return (ans + MOD) % MOD;
   }
   
   public static class Word{
      int s;                     //syllables
      int r;                     //rhyme
      public Word(int a, int b){
         s = a;
         r = b;
      }
   }
         
      
}