/*
TASK: snakes
LANG: JAVA
*/

import java.io.*;
import java.util.*;

class snakes{
   
   public static void main(String[] args) throws IOException{
      BufferedReader f = new BufferedReader(new FileReader("snakes.in"));
      PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("snakes.out")));
      
      
      StringTokenizer st = new StringTokenizer(f.readLine());
      
      int n = Integer.parseInt(st.nextToken());
      int m = Integer.parseInt(st.nextToken());
      
      int[] array = new int[n];
      
      st = new StringTokenizer(f.readLine());
      for(int k = 0; k < n; k++){
         array[k] = Integer.parseInt(st.nextToken());
      }
      
      int[][] dp = new int[n+1][m+2];
      for(int k = 0; k <= n; k++){
         Arrays.fill(dp[k],Integer.MAX_VALUE);
      }
      dp[0][0] = 0;
      
      for(int k = 0; k <= n; k++){
         for(int j = 0; j <= m; j++){
            if(dp[k][j] == Integer.MAX_VALUE) continue;
            int sum = 0;
            int max = 0;
            for(int h = k+1; h <= n; h++){
               sum += array[h-1];
               max = Math.max(max,array[h-1]);
               dp[h][j+1] = Math.min(dp[h][j+1],dp[k][j] + max*(h-k) - sum);
            }
         }
      }
      
      int answer = dp[n][m+1];
      System.out.println(answer);
      out.println(answer);
                    
      
        
        
      out.close();
   }
      
}