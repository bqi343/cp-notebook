import bc.*;
import java.util.*;

public class MapLocationComparator extends Globals implements Comparator<MapLocation> {
	public int compare(MapLocation A, MapLocation B) {
		int a = karboniteCount[A.getX()][A.getY()];
		int b = karboniteCount[B.getX()][B.getY()];
		if (a < b) return -1;
		if (a > b) return 1;
		return 0;
	}
}
