/**
 * Author: Andrew He
 * Description: Basic template/info for Java
 */

import java.util.*;
import java.math.*;
import java.io.*;
public class Main {
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		PrintStream out = System.out;
		StringTokenizer st = new StringTokenizer(br.readLine());
		assert st.hasMoreTokens(); // enable with java -ea main
		out.println("v=" + Integer.parseInt(st.nextToken()));
		ArrayList<Integer> a = new ArrayList<>();
		a.add(1234); a.get(0); a.remove(a.size()-1); a.clear();
	}
}