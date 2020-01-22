import java.io.*;
import java.util.*;
 
public class threesum {
	public static void main(String[] args) throws IOException {
		BufferedReader in = new BufferedReader(new FileReader("threesum.in"));
		PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("threesum.out")));
		String[] line = in.readLine().split(" ");
		int N = Integer.parseInt(line[0]);
		int Q = Integer.parseInt(line[1]);
		line = in.readLine().split(" ");
		int[] A = new int[N]; 
		long[][] ans = new long[N][N];
		for (int i = 0; i < N; ++i) A[i] = Integer.parseInt(line[i]);
		int[] z = new int[2000001];
		for (int i = N-1; i >= 0; --i) {
			for (int j = i+1; j < N; ++j) {
				int ind = 1000000-A[i]-A[j];
				if (ind >= 0 && ind <= 2000000) ans[i][j] = z[ind];
				z[1000000+A[j]] ++;
			}
			for (int j = i+1; j < N; ++j) {
				z[1000000+A[j]] --;
			}
		}
		for (int i = N-1; i >= 0; --i) 
			for (int j = i+1; j < N; ++j)
				ans[i][j] += ans[i+1][j]+ans[i][j-1]-ans[i+1][j-1];
		for (int i = 0; i < Q; ++i) {
			line = in.readLine().split(" ");
			int a = Integer.parseInt(line[0]);
			int b = Integer.parseInt(line[1]);
			out.println(ans[a-1][b-1]);
		}
		out.close();
	}
}