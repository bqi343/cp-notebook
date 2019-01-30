//if you have questions, pm me on codeforces (username: golions)
/*
TASK: sleepy
LANG: JAVA
*/

import java.io.*;
import java.util.*;

class sleepy{
   
   public static int[] bits;                 //for fenwick tree - stores number of already sorted numbers.
   public static int n;
   
   public static void main(String[] args) throws IOException{
      BufferedReader f = new BufferedReader(new FileReader("sleepy.in"));
      PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("sleepy.out")));
      
      
      n = Integer.parseInt(f.readLine());
      
      StringTokenizer st = new StringTokenizer(f.readLine());
      
      int[] array = new int[n];
      
      for(int k = 0; k < n; k++){
         array[k] = Integer.parseInt(st.nextToken());
      }
      
      bits = new int[n+1];
      
      //find longest sorted suffix. You will need to move every number in front of this suffix.
      int t = n-1;
      update(array[t],1);
      while(t >= 1 && array[t] > array[t-1]){
         t--;
         update(array[t],1);
      }
      
      
      
      
      //t is length of numbers that need to be moved
      System.out.println(t);
      out.println(t);
      for(int k = 0; k < t; k++){
         //the formula for the distance is t - k - 1 + (number of already sorted numbers before that number)
         int ans = t - k - 1 + psum(array[k]);
         System.out.print(ans + " ");
         out.print(ans);
         if(k < t-1) out.print(" ");
         
         //array[k] has been sorted, so update the fenwick tree
         update(array[k],1);
      }
      
      out.println();
      out.close();
   }
   
   //fenwick tree methods
   public static void update(int i, int x){
      for(; i <= n; i += i&-i){
         bits[i]+=x;
      }
   
   }
   
   public static int psum(int i){
      int sum = 0;
      for(; i > 0; i -= i&-i){
         sum += bits[i];
      }
      return sum;
   
   }
   
   
      
}