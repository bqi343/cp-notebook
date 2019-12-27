import bc.*;

public class pii extends Globals implements Comparable<pii> {
	static int distanceSquaredTo(Unit a, pii b) {
		return toPii(a).distanceSquaredTo(b);
	}
	
	public int f, s;
	pii(int F, int S) {
		f = F;
		s = S;
	}
	int distanceSquaredTo(pii b) {
		if (b == null) return INF;
		return (f-b.f)*(f-b.f)+(s-b.s)*(s-b.s);
	}
	pii add(int d) {
		return new pii (f+xdir[d],s+ydir[d]);
	}
	
	public boolean equals(pii x) {
		if (x == null) return false;
		return f == x.f && s == x.s;
	}
	
	public int compareTo(pii x) {
		if (f != x.f) return Integer.valueOf(f).compareTo(x.f);
		return Integer.valueOf(s).compareTo(x.s);
	}
	
	/*public int compareTo(pii x) {
		if (f != x.f) {
			if (f < x.f) return -1;
			if (f > x.f) return 1;
			return 0;
		}
		if (s < x.s) return -1;
		if (s > x.s) return 1;
		return 0;
		if (karboniteCount[f][s] < karboniteCount[x.f][x.s]) return -1;
		if (karboniteCount[f][s] > karboniteCount[x.f][x.s]) return 1;
		return 0;
	}*/
}
