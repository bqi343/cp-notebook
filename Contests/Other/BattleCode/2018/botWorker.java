import java.util.*;
import bc.*;

public class botWorker extends Movable {
	static boolean spamTime() {
		if (cPlanet != Planet.Mars) return false;
		if (gc.karbonite() > 300) return true;
		if (cRound > 700 || gc.getTeamArray(oPlanet).get(0) == 1) return true;
		return false;
	}

	static double needsWorker(Unit U) {	
		if (spamTime()) return 2;
		int c = comp(U);
		
		if (cPlanet == Planet.Earth) {
			if (fac[c] == 0 && cRound > Math.min(25,rushRounds) && work[c] >= 3) return 0;
			if (work[c] > 75) return 0;
			if (UNITS.size() >= MAXLIMIT) return 0;
		}
		
		if (cRound > 600 && work[c] > 5) return 0;
		if (work[c] > 50) return 0;
		if (sz[c] <= 3*cNum[c]/2) return 0;
		if ((cRound >= 300 && work[c] >= 3 && !structRocket.needsRocket())) return 0;
		
		int des = minWork[c];
		if (getCollectedKarbonite(cRound-20,cRound) <= workerCost && cRound > rushRounds) {
			if (structRocket.needsRocket() || rocket > 0) des = (int)Math.ceil(0.25*des);
			else des = (int)Math.ceil(des/6.0);

			if (work[c] < 2.0/3*des) return 2;
			if (work[c] < des) return 1;
			return 0;
		} else {
			if (work[c] < 2.0/3*des) return 2;
			if (work[c] < des) return 1;
			return 0.5;
		}
	}

	static Unit repli(Unit U, pii u) {
		double t = needsWorker(U); if (t == 0) return U;

		if (u != null && toPii(U).distanceSquaredTo(u) > 81) u = null;

		shuffleArray(dir);
		if ((cRound <= 50 && t == 2) || u == null) {
			U = gc.unit(U.id());
			for (int d = 0; d < 9; ++d) {
				Direction D = directions[dir[d]];
				if (fastGC.canReplicate(U,D)) {
					fastGC.replicate(U,D);
					return fastGC.recalc(U);
				}
			}
		}

		return U;
	}

	static Unit harvest(Unit U) {
		if (U.workerHasActed() == 1) return U;
		for (int i = 0; i < 9; ++i) {
			if (fastGC.canHarvest(U, directions[i])) {
				fastGC.harvest(U, i);

				U = fastGC.recalc(U);
				pii cur = toPii(U), bes = toPii(U);

				ArrayList<pii> close = new ArrayList<>();
				for(int x = cur.f-2; x <= cur.f+2; x++) {
					for(int y = cur.s-2; y <= cur.s+2; y++) {
						close.add(new pii(x, y));
					}
				}

				Collections.shuffle(close);
				for(i = 0; i < close.size(); i++) {
					pii x = close.get(i);
					if (fastGC.passable(x.f,x.s) && karboniteCount[x.f][x.s] > karboniteCount[bes.f][bes.s]) 
						bes = x;
				}

				return tryMove(U, bes, 0);
			}
		}

		return U;
	}

	static Unit needHeal(Unit U) {
		Unit u = GET(U,closeDamageStructure);
		int d = getDistGround(toPii(U),toPii(u));
		if (re.getLevel(UnitType.Rocket) > 0) {
			if (d > 20) return U;
		} else {
			if (d > 5) return U;
		}
		
		if (d > 1) U = tryMove(U,toPii(u),0);
		if (d <= 1) {
			if (gc.canRepair(U.id(),u.id())) {
				gc.repair(U.id(),u.id());
				collectedKarbonite[cRound] += 3;
				return null;
			}
			if (gc.canBuild(U.id(),u.id())) {
				gc.build(U.id(),u.id());
				collectedKarbonite[cRound] += 3;
				return null;
			}
		}
		return U;
	}

	static Unit moveEmpty(Unit U) {
		MapLocation cloc = mapLoc(U);
		if (karboniteCount[cloc.getX()][cloc.getY()] == 0) {
			if (bfsFrom[cloc.getX()][cloc.getY()] != null) return tryMove(U,bfsFrom[cloc.getX()][cloc.getY()]);
			else return moveRandom(U);
		}
		return U;
	}

	static void runRush(Unit V) {
		V = gc.unit(V.id());
		MapLocation M = mapLoc(V);
		
		V = harvest(V); 
		V = tryMove(V,bfsFrom[M.getX()][M.getY()]);

		if (needsWorker(V) == 0) { harvest(V); return; }

		M = mapLoc(V);
		Unit r = null;

		if (gc.canReplicate(V.id(), bfsFrom[M.getX()][M.getY()])) {
			r = fastGC.replicate(V,bfsFrom[M.getX()][M.getY()]);
			V = fastGC.recalc(V);
		} else {
			shuffleArray(dir);
			for(int d = 0; d < 9; d++) {
				Direction D = directions[dir[d]];
				if (gc.canReplicate(V.id(), D)) {
					r = fastGC.replicate(V, D);
					V = fastGC.recalc(V);
					break;
				}
			}
		}

		V = harvest(V);
		if (r != null) {
			r = harvest(r);
			MapLocation Mr = mapLoc(r);
			r = tryMove(r,bfsFrom[Mr.getX()][Mr.getY()]);
			r = harvest(r);
		}
	}

	static void rush(Unit U) {
		if (coolvariable) {
			coolvariable = false;
			int mn = (cPlanet == Planet.Earth) ? 2 : Math.min(15, 1+worker/5);
			for (int i = 0; i < Math.min(mn, closestWorkers.size()); i++) runRush(closestWorkers.get(i));
			U = gc.unit(U.id());
		} 

		U = needHeal(U); if (U == null) return;
		U = harvest(U); U = moveEmpty(U); U = harvest(U);
		if (cPlanet == Planet.Mars) U = repli(U,null);
	}

	static boolean noUnfinished(Unit U) {
		pii cloc = toPii(U);
		for (int i = 1; i < 9; ++i) {
			pii CLOC = cloc.add(i);
			if (fastGC.onBoard(CLOC.f,CLOC.s) && fastGC.yourStructure(tmp[cloc.f][cloc.s])) return false;
		}
		return true;
	}
	static void moveTowardAttacker(Unit U) {
		pii M = toPii(U);
		
		for(int x = M.f-2; x <= M.f+2; x++) {
			for(int y = M.s-2; y <= M.s+2; y++) {
				if (U.movementHeat() >= 10) break;
				if (fastGC.valid(x, y) && tmp[x][y] != null 
					&& (fastGC.isAttacker(tmp[x][y]) || tmp[x][y].unitType() == UnitType.Healer)) {
					if (lastSeen <= cRound-50 && cPlanet == Planet.Earth) {
						U = tryMove(U, new pii(x,y), 0);
					} else {
						U = tryMove(U, new pii(x,y), 1);
					}
				}
			}
		}
	}
	
	static void run(Unit U) {
		U = needHeal(U); if (U == null) return;
		if (noUnfinished(U)) {
			U = structRocket.runRocket(U); 
			if (U == null) return;
		}

		if (closestWorkers.size() != 0) { rush(U); return; }

		pii u = getPri(U); U = repli(U,u);
		if (u != null) U = retreat(U,u);

		U = harvest(U);
		if (cRound <= 525 || cPlanet == Planet.Mars) U = moveEmpty(U);
		else U = retreat(U,null);
		
		U = harvest(U);
		U = avoidFac(U); 
	}
}