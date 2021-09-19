/**
 * Description: Compute union of two polygons and compute the area 
 	* of the resulting figure with \texttt{java.awt.geom}.
 * Time: Runs quite quickly for two convex polygons with $10^5$ vertices each.
 * Source: Nick Wu
 * Verification: 
 	* https://open.kattis.com/problems/abstractart
 	* https://probgate.org/viewproblem.php?pid=249
 */

import java.awt.geom.*;
import java.io.*;
import java.util.*;
public class AreaIntersect {
	static int nextI(StringTokenizer st) { 
		return Integer.parseInt(st.nextToken()); }
	static double nextD(StringTokenizer st) { 
		return Double.parseDouble(st.nextToken()); }
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter pw = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
		StringTokenizer st = new StringTokenizer(br.readLine());
		int n = nextI(st); int m = nextI(st);
		double[] first = loadPolygon(n, br); 
		double[] second = loadPolygon(m, br);
		Area ret = makeArea(first); ret.add(makeArea(second));
		pw.printf("%.9f\n", computeArea(ret)); pw.close();
	}
	public static double[] loadPolygon(int n, BufferedReader br) throws IOException {
		double[] ret = new double[2*n];
		for(int i = 0; i < n; i++) {
			StringTokenizer st = new StringTokenizer(br.readLine());
			ret[2*i] = nextD(st); ret[2*i+1] = nextD(st);
		}
		return ret;
	}
	public static Area makeArea(double[] pts) {
		Path2D.Double p = new Path2D.Double(); 
		p.moveTo(pts[0],pts[1]);
		for (int i=2;i<pts.length;i+=2) p.lineTo(pts[i],pts[i+1]);
		p.closePath(); return new Area(p);
	}
	public static double computeArea(Area a) {
		PathIterator iter = a.getPathIterator(null);
		double[] buffer = new double[6]; double ret = 0;
		ArrayList<Double> ps = new ArrayList<Double>();
		while (!iter.isDone()) {
			switch (iter.currentSegment(buffer)) {
				case PathIterator.SEG_MOVETO:
				case PathIterator.SEG_LINETO:
					ps.add(buffer[0]); ps.add(buffer[1]);
					break;
				case PathIterator.SEG_CLOSE:
					ps.add(ps.get(0)); ps.add(ps.get(1));
					Double[] qs = ps.toArray(new Double[0]);
					for (int i = 0; i+2 < ps.size(); i += 2) 
						ret -= qs[i]*qs[i+3]-qs[i+1]*qs[i+2];
					ps.clear();
					break;
			}
			iter.next();
		}
		return ret/2;
	}
}