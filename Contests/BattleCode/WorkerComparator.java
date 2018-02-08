import bc.*;
import java.util.*;

public class WorkerComparator extends Globals implements Comparator<Unit> {
	int getVal(Unit U) {
		if(C.getWidth() * C.getHeight() <= 900) {
			return -toPii(U).distanceSquaredTo(get(U,closeStructure));
		}
		return toPii(U).distanceSquaredTo(get(U,closeStructure));
	}
	
	public int compare(Unit c1, Unit c2) {
		 return Integer.valueOf(getVal(c1)).compareTo(getVal(c2));
    }
}
