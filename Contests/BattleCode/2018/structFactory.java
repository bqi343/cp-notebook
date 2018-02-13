import bc.*;

public class structFactory extends Structure {
	static void tryAttacker(Unit U) {
		// if (cRound <= 450) return;
		if (gc.canProduceRobot(U.id(),UnitType.Ranger)) {
			cNum[comp(U)] ++;
			
			pii M = toPii(U); pii M2 = fastGC.closeFactory(U, oteam);
			int dist = getDistGround(M, M2);
			
			if (!mageSeen && cRound <= Math.min(100, 150-5*dist)) { 
				if (ran.nextInt(3) <= 1) gc.produceRobot(U.id(), UnitType.Knight);
				else gc.produceRobot(U.id(), UnitType.Mage);
			} else {
				if (cRound > 225 && Math.random() < .25) {
					System.out.println("Mage!");
					gc.produceRobot(U.id(),UnitType.Mage);
					mage ++;
				} else if (ranger < 3 || 3*healer >= 2*ranger) { 
					System.out.println("Ranger!");
					gc.produceRobot(U.id(),UnitType.Ranger);
					ranger ++;
				} else {
					System.out.println("Healer!");
					gc.produceRobot(U.id(),UnitType.Healer);
					healer ++;
				}
				attack ++;
			}
		}
	}

	static void tryWorker(Unit U) {
		if (gc.canProduceRobot(U.id(),UnitType.Worker)) {
			gc.produceRobot(U.id(),UnitType.Worker);
			System.out.println("Factory produced worker!");
			work[comp(U)] ++; cNum[comp(U)] ++; workerCost += 50;
		}
	}
	
	static void produce(Unit U) {
		if (UNITS.size() >= MAXLIMIT || cRound >= 700) return;
		
		int c = comp(U);
		if (cPlanet == Planet.Earth && sz[c] <= 3*cNum[c]/2) return;
		
		pii u = get(U,closeEnemyEuclid);
		
		double t = botWorker.needsWorker(U);
		if (t == 2) {
			tryWorker(U);
		} else if ((toPii(U).distanceSquaredTo(u) <= 64 && cRound < 525) || attack < 1.5*fac[c]) {
			tryAttacker(U);
		} else { 
			if (fac[c] >= Math.min(minFac[c],3) || cRound > 150) 
				if ((!structRocket.needsRocket() && cRound < 525) || gc.karbonite() > 250)  {
					if (t == 1) tryWorker(U);
					else tryAttacker(U);
				}
		} 
	}
	
	// sort them by their distance to existing factory
	
	static Unit startFac(Unit U) {
		if (U.workerHasActed() == 1 || gc.karbonite() < bc.bcUnitTypeBlueprintCost(UnitType.Factory)) return U;
		if (fastGC.nearbyUnbuilt(U)) return U;
		
		int c = comp(U);
		if (work[c] <= 2*fac[c] || work[c] < Math.min(3,sz[c]-1) || fac[c] >= 25) return U;

		if (cRound >= 600) return U;
		if (cRound >= 150 && 2*fac[c] >= minFac[c] && gc.karbonite() < 200) return U;
		
		if (fac[c] > 0 && existsEnemy(U,7)) {
			if (cRound <= 50 && 1.5*fac[comp(U)] <= minFac[comp(U)]) {
				
			} else {
				return U;
			}
		}
		
		for (int i = 1; i < 9; ++i) {
			MapLocation cloc = mapLoc(U).add(directions[i]);
			if (gc.canBlueprint(U.id(), UnitType.Factory, directions[i])) {
				if (existsStruct(cloc)) continue;
				
				int garrisonSize = 0;
				for(int j = 1; j < 9; j++) if (fastGC.valid(cloc.add(directions[j]))) garrisonSize++;
				if (garrisonSize < 2) continue;
				
				gc.blueprint(U.id(), UnitType.Factory, directions[i]);
				tmp[cloc.getX()][cloc.getY()] = gc.senseUnitAtLocation(cloc);
				karboniteCount[cloc.getX()][cloc.getY()] = 0;
				fac[comp(U)] ++; factory ++;
				lastCollect.put(U.id(),cRound);
				
				return fastGC.recalc(U);
			}
		}
		
		return U;
	}
	
	static void run(Unit U) {
		unload(U);
		produce(U);
	}
}	
