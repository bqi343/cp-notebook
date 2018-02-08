import bc.*;
import java.util.*;

public class HealthComparator extends Globals implements Comparator<Unit> {
	public static int getHeat(Unit U) {
		if (fastGC.isStructure(U)) return INF;
		return (int)U.health();
	}
	public int compare(Unit c1, Unit c2) {
		 int a = getHeat(c1);
		 int b = getHeat(c2);
		 if (a < b) return -1;
		 if (a > b) return 1;
		 return 0;
    }
}