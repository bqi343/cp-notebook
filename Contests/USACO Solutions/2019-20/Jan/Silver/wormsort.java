import java.io.*; // from Nick Wu
import java.util.*;
public class wormsort {
  public static void main(String[] args) throws IOException{
    BufferedReader br = new BufferedReader(new FileReader("wormsort.in"));
    StringTokenizer st = new StringTokenizer(br.readLine());
    int n = Integer.parseInt(st.nextToken());
    int m = Integer.parseInt(st.nextToken());
    loc = new int[n];
    component = new int[n];
    edges = new LinkedList[n];
    for(int i = 0; i < n; i++) edges[i] = new LinkedList<>();
    lhs = new int[m];
    rhs = new int[m];
    weight = new int[m];
    st = new StringTokenizer(br.readLine());
    for(int i = 0; i < n; i++) loc[i] = Integer.parseInt(st.nextToken())-1;
    for(int i = 0; i < m; i++) {
      st = new StringTokenizer(br.readLine());
      lhs[i] = Integer.parseInt(st.nextToken())-1;
      rhs[i] = Integer.parseInt(st.nextToken())-1;
      weight[i] = Integer.parseInt(st.nextToken());
    }
    br.close();
    int minW = 0;
    int maxW = 1000000001;
    while(minW != maxW) {
      int mid = (minW + maxW + 1) / 2;
      if(valid(mid)) minW = mid;
      else maxW = mid-1;
    }
    if(minW > 1e9) minW = -1;
    PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("wormsort.out")));
    pw.println(minW);
    pw.close();
  }
  static int[] loc, lhs, rhs, weight;
  static LinkedList<Integer>[] edges;
  static int[] component;
  private static void dfs(int curr, int label) {
    if(component[curr] == label) return;
    component[curr] = label;
    for(int child: edges[curr]) dfs(child, label);
  }
  private static boolean valid(int minW) {
    Arrays.fill(component, -1);
    for(int i = 0; i < edges.length; i++) edges[i].clear();
    for(int i = 0; i < lhs.length; i++) {
      if(weight[i] >= minW) {
        edges[lhs[i]].add(rhs[i]);
        edges[rhs[i]].add(lhs[i]);
      }
    }
    int numcomps = 0;
    for(int i = 0; i < component.length; i++) {
      if(component[i] < 0) {
        dfs(i, numcomps++);
      }
    }
    for(int i = 0; i < loc.length; i++) {
      if(component[i] != component[loc[i]]) return false;
    }
    return true;
  }
}