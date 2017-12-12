import java.util.*;
import java.lang.*;
import java.io.*;

class Main {
    public static int[] par = new int[100];
    public static int[] hei = new int[100];
    public static ArrayList<ArrayList<Integer>> edge = new ArrayList<>();
    
    public static int get(int x) { // path compression
        if (par[x] != x) par[x] = get(par[x]);
        return par[x];
    }

    public static boolean unite(int x, int y) { // union-by-rank
        x = get(x); y = get(y);
        if (x == y) return false;
        if (hei[x] < hei[y]) {
            int t = x;
            x = y;
            y = t;
        }
        hei[x] = Math.max(hei[x],hei[y]+1);
        par[y] = x;
        return true;
    }

    public static void main (String[] args) throws java.lang.Exception {
        for (int i = 0; i < 100; ++i) {
            par[i] = i; 
            hei[i] = 1;
        }
        for (int i = 0; i < 100; ++i) 
            for (int j = i+1; j < 100; ++j)
                if ((int)(5*Math.random()) == 0) {
                    ArrayList<Integer> t = new ArrayList<>();
                    t.add((int)(100*Math.random())+1);
                    t.add(i);
                    t.add(j);
                    edge.add(t);
                }
                
        Collections.sort(edge, new Comparator<ArrayList<Integer>>() {
            public int compare(ArrayList<Integer> one, ArrayList<Integer> two) {
                return one.get(0).compareTo(two.get(0));
            }
        });
        
        int ans = 0;
        for (ArrayList<Integer> a: edge) if (unite(a.get(1),a.get(2)) == true) ans += a.get(0);
        System.out.println(ans);
    }
}
