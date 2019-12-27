import bc.*;
import java.util.*;

public class UnitComparator extends Globals implements Comparator<Unit> {
	public static int getHeat(Unit U) {
		if (U.unitType() == UnitType.Factory) return INF;
		if (U.unitType() == UnitType.Rocket) return -INF;
		
		int t = (int)(U.attackHeat()+U.movementHeat()+U.abilityHeat());
		if (U.unitType() == UnitType.Worker) t *= 100;
		return t;
	}
	
	public static int getVal(Unit u) {
		if (u.unitType() == UnitType.Rocket) {
			if (cPlanet == Planet.Earth || u.structureGarrison().size() > 0) return -INF;
			return INF;
		}
		
		int t = toPii(u).distanceSquaredTo(get(u,closeEnemyEuclid));
		
		if (u.unitType() == UnitType.Worker) {
			if (structRocket.needsRocket() || cRound > 600) t -= INF;
			else t += INF;
		} else if (cPlanet == Planet.Mars) t -= INF;
		if (u.unitType() == UnitType.Mage) t -= INF;
		if (u.unitType() == UnitType.Factory) return -INF-1000;
		return t;
	}
	
	public static int distTaxi(Unit a, Unit b) {
		if (a == null || b == null) return INF;
		return (int)mapLoc(a).distanceSquaredTo(mapLoc(b));
	}
	
	public int compare(Unit c1, Unit c2) {
		 return Integer.valueOf(getVal(c1)).compareTo(getVal(c2));
    }
}
