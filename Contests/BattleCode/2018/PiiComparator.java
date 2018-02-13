import java.util.*;

public class PiiComparator extends Globals implements Comparator<pii> {
	public int compare(pii A, pii B) {
		int a = karboniteCount[A.f][A.s];
		int b = karboniteCount[B.f][B.s];
		if (a < b) return -1;
		if (a > b) return 1;
		return 0;
	}
}
