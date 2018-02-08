import java.util.ArrayList;

import bc.*;

public class structRocket extends Structure {
	static boolean onBoardMars(int x, int y) {
		return x >= 0 && x < O.getWidth() && y >= 0 && y < O.getHeight();
	}

	static void genMarsVal() { // generate value of each spot on mars
		for (int i = 0; i < O.getWidth(); ++i) 
			for (int j = 0; j < O.getHeight(); ++j) {
				int sum = 0;
				for (int x = i-2; x <= i+2; ++x) if (0 <= x && x < O.getWidth()) 
					for (int y = j-2; y <= j+2; ++y) if (0 <= y && y < O.getHeight())  {
						if (x == i && y == j) continue;
						if (compO[x][y] == compO[i][j]) sum += O.initialKarboniteAt(new MapLocation(oPlanet,x,y));
					}
				
				marsVal[i][j] = sum;
			}
	}

	static Unit startRocket(Unit U) {
		if (U.workerHasActed() == 1 || gc.karbonite() < bc.bcUnitTypeBlueprintCost(UnitType.Rocket)) return U;
		if (existsEnemy(U,5) || fastGC.nearbyUnbuilt(U)) return U;
		if(cattack[comp(U)] < maxAtk - 1) return U;

		for (int i = 1; i < 9; ++i) {
			MapLocation cloc = mapLoc(U).add(directions[i]);
			if (gc.canBlueprint(U.id(), UnitType.Rocket, directions[i])) {
				if ((cRound <= 600 || totRocket > 0) && existsStruct(cloc)) continue;
				gc.blueprint(U.id(), UnitType.Rocket, directions[i]);
				karboniteCount[cloc.getX()][cloc.getY()] = 0;
				tmp[cloc.getX()][cloc.getY()] = gc.senseUnitAtLocation(cloc);
				rocket ++; totRocket ++;
				return fastGC.recalc(U);
			}
		}
		
		return U;
	}

	static void prep(Unit U) {
		// System.out.println("Preparing "+U.id());
		R.put(U.id(),cRound);
	}

	static MapLocation randomDestination() {
		ArrayList<MapLocation> A = new ArrayList<>();
		for (int i = 0; i < O.getWidth(); ++i)
			for (int j = 0; j < O.getHeight(); ++j) {
				MapLocation cloc = new MapLocation(Planet.Mars,i,j);
				if (O.isPassableTerrainAt(cloc) == 1) A.add(cloc);
			}

		if (A.size() == 0) return null;
		return A.get(ran.nextInt(A.size()));
	}

	static MapLocation smartDestination() {
		MapLocation bes = null;
		int bestSum = -INF;

		for (int i = 0; i < O.getWidth(); ++i)
			for (int j = 0; j < O.getHeight(); ++j) {
				if (compO[i][j] != 0 && marsVal[i][j] > bestSum) {
					boolean bad = false;
					for (int I = i-2; I <= i+2; ++I) if (0 <= I && I < 50)
						for (int J = j-2; J <= j+2; ++J) if (0 <= J && J < 50)
							if (sentRocket[I][J] == true) {
								bad = true;
								break;
							}
					
					if (!bad) {
						bes = new MapLocation(Planet.Mars,i,j);
						bestSum = marsVal[i][j];
					}
				}
			}

		return bes;
	}

	static MapLocation chooseDestination() {
		MapLocation bes = smartDestination();
		if (bes == null) bes = randomDestination();		
		if (bes != null) sentRocket[bes.getX()][bes.getY()] = true;
		return bes;
	}

	static boolean focusRocket() {
		if (cPlanet == Planet.Mars) return false;
		return re.getLevel(UnitType.Rocket) > 0 || cRound >= 525 || (enemySeen && lastSeen < cRound-50);
	}

	static Unit runRocket(Unit U) {
		if (cPlanet == Planet.Mars) return U;

		Unit u = GET(U,closeRocket);
		if (u != null && u.unitType() != UnitType.Rocket) u = null;

		if (u != null)
			if (cRound < 650 && getDistGround(U,u) > 5) 
				u = null;

		if (u == null) {			
			if (focusRocket() && U.unitType() != UnitType.Worker) U = Movable.retreat(U,null);
			return U;
		}

		if (getDistGround(U,u) > 5) {
			U = Movable.tryMove(U,toPii(u),0);
			return U;
		}

		if (shouldLoad(u,U) && (!R.containsKey(u.id()) || 
								(fastGC.dist(U,u) <= 2 && u.structureGarrison().size() < u.structureMaxCapacity()))) {
			if (fastGC.dist(U,u) > 2) U = Movable.tryMove(U,toPii(u),0);
			if (canLoad(u,U)) {
				fastGC.load(u,U);
				return null;
			}
			return U;
		} 
		return Movable.tryMove(U,toPii(u),1);
	}

	static void launchRocket(Unit U) {
		MapLocation M = nextDestination;
		if (M == null) return;
		
		if (gc.canLaunchRocket(U.id(),M)) {
			nextDestination = structRocket.chooseDestination();
			MapLocation cloc = mapLoc(U);
			tmp[cloc.getX()][cloc.getY()] = null;
			System.out.println("Launching "+U.id()+" "+U.structureGarrison().size()+" "+getNum(U,UnitType.Worker));
			gc.launchRocket(U.id(), M);
			fastGC.recalcSquare(mapLoc(U));
			hasLaunched = true;
		} 
	}

	static boolean shouldLaunch(Unit U) {
		int t = (int)U.structureGarrison().size();
		// if (t == 0) return false;
		if (!hasLaunched) return (t >= 5 || (t >= 1 && cRound > 600));
		return cRound > 740;
		// if (t <= U.structureMaxCapacity()/2) return false;
		// return cRound % 50 == 0;
	}

	static boolean shouldLoad(Unit U, Unit u) {
		if (!hasLaunched) {
			if (u.unitType() == UnitType.Worker && getNum(U,u.unitType()) > 2) return false;
			return true;
		}
		if (u.unitType() == UnitType.Worker && getNum(U,u.unitType()) > 0) return false;
		return true;
	}

	static boolean canLoad(Unit U, Unit u) {
		return shouldLoad(U,u) && gc.canLoad(U.id(), u.id());
	}

	static boolean danger(Unit U) {
		if (U.structureIsBuilt() == 1 && U.health() < U.maxHealth() && U.structureGarrison().size() > 0) {
			launchRocket(U);
			return true;
		}
		return false;
	}

	static void run(Unit U) {
		if (wait.get(U.id()) == null) wait.put(U.id(),cRound);
		if (cPlanet == Planet.Earth) {
			if (danger(U)) return;
			if (cRound > 740) {
				launchRocket(U);
				return;
			}
			if (R.get(U.id()) == null) {
				if (shouldLaunch(U)) prep(U);
			} else if (R.get(U.id()) <= cRound-6) {
				launchRocket(U);
			} 
		} else {
			unload(U);
		}
	}

	static boolean needsRocket() {
		if (re.getLevel(UnitType.Rocket) == 0) return false;
		if (nextDestination == null) return false;
		if (!hasLaunched) return true;
		if (rocket >= 5) return false;
		return true;
	}
}