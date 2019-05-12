import java.util.ArrayList;
import java.util.Collections;

import bc.*;

public class Structure extends Player {
	static int getNum(Unit U, UnitType u) {
		VecUnitID V = U.structureGarrison();
		int num = 0;
		for (int i = 0; i < V.size(); ++i) 
			if (gc.unit(V.get(i)).unitType() == u) num ++;
		return num;
	}


	static void unload(Unit U) {
		int x = (int)U.structureGarrison().size();
		for (int d = 1; d < 9 && x > 0; ++d)
			if (gc.canUnload(U.id(), directions[d])) {
				fastGC.unload(U,d);
				x --;
			}
	}
	
	static boolean yourStruct(Unit U) {
		return U != null && U.team() == cteam && fastGC.isStructure(U);
	}
	
	static boolean existsStruct(MapLocation M) {
		for (int i = 1; i < 9; i ++) {
			int x = M.getX()+xdir[i], y = M.getY()+ydir[i];
			if (!fastGC.onBoard(x,y)) continue;
			MapLocation cloc = new MapLocation(cPlanet,x,y);
			if (yourStruct(tmp[cloc.getX()][cloc.getY()])) return true;
		}
		return false;
	}
	
	static Unit extreme(Unit u) {
		if (totRocket == 0 && re.getLevel(UnitType.Rocket) > 0 && structRocket.focusRocket()) {
			MapLocation M = mapLoc(u);
			for (int i = 1; i < 9; i ++) {
				int x = M.getX()+xdir[i], y = M.getY()+ydir[i];
				if (fastGC.isEmpty(new pii(x,y))) {
					structRocket.startRocket(u);
					return null;
				}
			}
			for (int i = 1; i < 9; i ++) {
				int x = M.getX()+xdir[i], y = M.getY()+ydir[i];
				if (fastGC.valid(x,y) && tmp[x][y] != null && tmp[x][y].team() == cteam) {
					fastGC.disintegrateUnit(tmp[x][y]);
					return structRocket.startRocket(u);
				}
			}
		}
		return u;
	}
	
	static void tryMake() {
		ArrayList<Unit> unitWork = new ArrayList<>();
		for (int i = 0; i < UNITS.size(); ++i) {
			Unit u = UNITS.get(i);
			if (u.unitType() == UnitType.Worker) unitWork.add(u);
		}
		Collections.sort(unitWork,new WorkerComparator());
		for (Unit u: unitWork) {
			u = fastGC.upd(u); if (u == null) continue;
			u = extreme(u); if (u == null) continue;
			u = structFactory.startFac(u); if (u == null) continue;
			if (structRocket.needsRocket()) structRocket.startRocket(u);
		}
	}
}
