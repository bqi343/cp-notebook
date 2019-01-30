//if you have any questions, you can pm me on codeforces (username: golions)
/*
TASK: shortcut
LANG: JAVA
*/

import java.io.*;
import java.util.*;

class shortcut{
   
   public static int[] par;
   
   public static void main(String[] args) throws IOException{
      BufferedReader f = new BufferedReader(new FileReader("shortcut.in"));
      PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("shortcut.out")));
      
      
      StringTokenizer st = new StringTokenizer(f.readLine());
      
      int n = Integer.parseInt(st.nextToken());
      int m = Integer.parseInt(st.nextToken());
      int t = Integer.parseInt(st.nextToken());
      
      long[] c = new long[n+1];
      
      st = new StringTokenizer(f.readLine());
      
      for(int k = 1; k <= n; k++){
         c[k] = Long.parseLong(st.nextToken());
      }
      
      //build edge list for every vertex
      ArrayList<ArrayList<Edge>> adj = new ArrayList<ArrayList<Edge>>(n+1);
      
      for(int k = 0; k <= n; k++) adj.add(new ArrayList<Edge>());
      
      for(int k = 0; k < m; k++){
         st = new StringTokenizer(f.readLine());
      
         int a = Integer.parseInt(st.nextToken());
         int b = Integer.parseInt(st.nextToken());
         long w = Long.parseLong(st.nextToken());
         
         adj.get(a).add(new Edge(b,w));
         adj.get(b).add(new Edge(a,w));
      }
      
      
      //basic djikstra's algorithm while storing parents
      long[] djik = new long[n+1];
      par = new int[n+1];
      
      Arrays.fill(djik,Long.MAX_VALUE);
      djik[1] = 0L;  
      Arrays.fill(par,-1);
      
      PriorityQueue<State> pq = new PriorityQueue<State>();
      
      pq.add(new State(1,0));
      
      HashSet<Integer> seen = new HashSet<Integer>();
      
      seen.add(1);
      
      while(!pq.isEmpty()){
         State cur = pq.poll();
         int u = cur.v;
         
         seen.add(u);
         
         for(Edge e : adj.get(u)){
            int v = e.to;
            if(seen.contains(v)) continue;
            long newdis = djik[u] + e.w;
            if(newdis < djik[v]){
               djik[v] = newdis;
               par[v] = u;
               pq.add(new State(v,newdis));
            } else if(newdis == djik[v]){                            //ensures lexicographically shortest path
               if(u < par[v]){
                  djik[v] = newdis;
                  par[v] = u;
                  pq.add(new State(v,newdis));
               }
            }
         }
      }
      
      
      long[] nums = new long[n+1];                  //number of cows that pass through that vertex
      for(int k = 1; k <= n; k++){
         //backtrack to fill nums
         int i = k;
         while(i != -1){
            nums[i] += c[k];
            i = par[i];
         }
      }
      
      long max = 0L;
      for(int k = 1; k <= n; k++){
         System.out.println(nums[k] + " " + djik[k]);
         //nums[k] * (djik[k] - t) is the distance saved
         max = Math.max(max,nums[k]*(djik[k]-t));
      }
      
      System.out.println(max);
      out.println(max);
      
      
      
      
      
      
      
      out.close();
   }
   
   public static class State implements Comparable<State>{
      int v;                  //vertex
      long w;                 //current distance
      public State(int a, long b){
         v = a;
         w = b;
      }
      public int compareTo(State s){
         if(w > s.w) return 1;
         if(w < s.w) return -1;
         return 0;
         
      }
   }
   
   public static class Edge{
      int to;                 //other edge
      long w;                 //weight
      public Edge(int a, long b){
         to = a;
         w = b;
      }
   }
      
}