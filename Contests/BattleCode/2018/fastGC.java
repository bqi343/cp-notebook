import java.util.ArrayList;

import bc.*;

public class fastGC extends Globals {
	// MAP
	static boolean onBoard(int x, int y) {
		if (x < 0 || x >= C.getWidth() || y < 0 || y >= C.getHeight()) return false;
		return true;
	}
	
	static boolean onBoardO(int x, int y) {
		if (x < 0 || x >= O.getWidth() || y < 0 || y >= O.getHeight()) return false;
		return true;
	}

	static boolean valid(int X, int Y) { // passable terrain
		return onBoard(X,Y) && comp[X][Y] != 0;
	}

	static boolean valid(MapLocation M) {
		return valid(M.getX(),M.getY());
	}
	
	static boolean valid(pii M) {
		return valid(M.f,M.s);
	}
	
	static boolean VALID(int X, int Y) {
		return valid(X,Y) && lastSense[X][Y] == cRound;
	}
	
	static boolean VALID(MapLocation M) {
		return VALID(M.getX(),M.getY());
	}
	
	static boolean VALID(pii M) {
		return VALID(M.f,M.s);
	}

	
	static boolean passable(int X, int Y) { // square can be passed w/o structure
		return valid(X,Y) && passable[X][Y];
	}
	
	static int dist(Unit a, Unit b) { // distance between two units
		if (a == null || b == null) return INF;
		return (int)toPii(a).distanceSquaredTo(toPii(b));
	}
	
	static boolean isEmpty(pii M) {
		return valid(M) && tmp[M.f][M.s] == null;
	}
	
	static boolean isEmpty(MapLocation M) {
		return isEmpty(new pii(M.getX(),M.getY()));
	}
	
	static boolean isBlocked(Unit U) {
		if (U == null) return false;
		pii M = toPii(U);
		
		int cnt = 0;
		for(int i = 1; i < 9; i++) 
			if (isEmpty(M.add(i))) 
				cnt++;
		
		return cnt < 2;
	}
	
	static boolean surrounded(Unit U) {
		pii M = toPii(U);
		for (int i = 1; i < 9; i++)
			if (isEmpty(M.add(i))) 
				return false;
		return true;
	}
	
	static boolean nearbyUnbuilt(Unit U) {
		pii P = toPii(U);
		for(int i = P.f-2; i <= P.f+2; i++) 
			for(int j = P.s-2; j <= P.s+2; j++) 
				if (fastGC.valid(i, j) && fastGC.yourUnbuiltStructure(tmp[i][j])) 
					return true;
		return false;
	}

	// UNIT IDENTIFICATION

	static boolean isStructure(Unit U) { // is unit a structure
		if (U == null) return false;
		switch (U.unitType()) {
			case Factory:
			case Rocket:
				return true;
			default:
				return false;
		}
	}

	static boolean your(Unit U) {
		return U != null && U.team() == cteam;
	}
	
	static boolean yourStructure(Unit U) {
		return isStructure(U) && U.team() == cteam;
	}
	
	static boolean yourDamageStructure(Unit U) {
		return yourStructure(U) && U.health() < U.maxHealth() && U.structureIsBuilt() == 1;
	}
	
	static boolean yourUnbuiltStructure(Unit U) {
		return yourStructure(U) && U.structureIsBuilt() == 0;
	}   

    static boolean your(Unit U, UnitType u) {
        return U != null && U.team() == cteam && U.unitType() == u;
    }
    
	static boolean activeWorker(Unit u) {
		return your(u,UnitType.Worker) && u.abilityHeat() < 10;
	}
    
	static boolean isAttacker(Unit U) {
		if (U == null) return false;
		switch(U.unitType()) {
			case Ranger:
			case Knight:
			case Mage:
				return true;
			default:
				return false;
		}
	}

	static boolean yourDamagedUnit(Unit U) {
		if (U == null) return false;
		return U.team() == cteam && !isStructure(U) && U.health() < U.maxHealth();
	}
	
	static boolean yourAttacker(Unit U) {
		return isAttacker(U) && U.team() == cteam;
	}
	
	static boolean yourDamagedAttacker(Unit U) {
		return yourAttacker(U) && U.health() < U.maxHealth();
	}

	static boolean opUnit(Unit U) {	
		return U != null && U.team() == oteam;
	}
	
	static boolean opAttacker(Unit U) {
		return isAttacker(U) && U.team() == oteam;
	}

	static boolean isSniping(Unit U) {
		if (U.unitType() != UnitType.Ranger) return false;
		if (U.rangerIsSniping() == 1) return true;
		return false;
	}

	static Unit upd(Unit U) {
		pii x = toPii(U);
		if (tmp[x.f][x.s] == null || tmp[x.f][x.s].id() != U.id()) return null;
		return tmp[x.f][x.s];
	}
	
	// ACTIONS

	static void disintegrateUnit(Unit U) {
		pii p = toPii(U);
		gc.disintegrateUnit(U.id());
		tmp[p.f][p.s] = null;
	}
	
	static Unit attack(Unit U, Unit u) { // attacks 
		if (U.attackHeat() >= 10 || u == null) return U;
		MapLocation cloc = mapLoc(u);
		
		if (U.unitType() == UnitType.Mage && botMage.getValMage(cloc.getX(), cloc.getY()) <= 0) return U;
		if (canAttack(U,u)) {
			gc.attack(U.id(), u.id());
			
			if (U.unitType() == UnitType.Mage) {
				fastGC.recalcSquare(cloc);
			} else {
				if (gc.hasUnitAtLocation(cloc)) tmp[cloc.getX()][cloc.getY()] = gc.senseUnitAtLocation(cloc);
				else tmp[cloc.getX()][cloc.getY()] = null;
			}
			
			return recalc(U);
		}
		
		return U;
	}
	
	static void recalcSquare(MapLocation cloc) {
		for (int i = cloc.getX()-1; i <= cloc.getX()+1; ++i)
			for (int j = cloc.getY()-1; j <= cloc.getY()+1; ++j)
				if (fastGC.VALID(i,j)) {
					MapLocation CLOC = new MapLocation(cPlanet,i,j);
					if (gc.hasUnitAtLocation(CLOC)) tmp[i][j] = gc.senseUnitAtLocation(CLOC);
					else tmp[i][j] = null;
				}
	}
	
	static Unit ad(MapLocation r) {
		if (!fastGC.valid(r)) return null;
		Unit u = gc.senseUnitAtLocation(r);
		UNITS.add(u); tmp[r.getX()][r.getY()] = u;
		if (u.unitType() == UnitType.Knight) knightRushing.put(u.id(), false);
		return u;
	}
	
	static boolean canReplicate(Unit U, Direction D) {
		return gc.canReplicate(U.id(), D);
	}

    static pii closeFactory(Unit U, Team te) {
		pii u = getClosest2(U,te == cteam ? cFac: oFac);
	    return u;
	}
    
	static Unit harvest(Unit U, int d) {
		MapLocation cloc = mapLoc(U).add(directions[d]);
		
		gc.harvest(U.id(), directions[d]); recalc(U);
		int ne = (int)gc.karboniteAt(cloc);
		
		collectedKarbonite[cRound] += karboniteCount[cloc.getX()][cloc.getY()] - ne;
		karboniteCount[cloc.getX()][cloc.getY()] = ne;
		
		return U;
	}
	
	static Unit replicate(Unit U, Direction D) {
		int c = comp(U);
		// System.out.println("Replicated worker!");
		work[c] ++; cNum[c] ++; workerCost += 60; 
		gc.replicate(U.id(),D);
		recalc(U);
		return ad(mapLoc(U).add(D));
	}
	
	static void unload(Unit U, int d) {
		gc.unload(U.id(), directions[d]);
		fastGC.ad(mapLoc(U).add(directions[d]));
	}
	
	static boolean canAttack(Unit U, Unit u) {
		return gc.canAttack(U.id(), u.id());
	}
	
	static boolean isBlinkReady(Unit U) {
		if (re.getLevel(UnitType.Mage) != 4) return false;
		if (U.abilityHeat() >= 10) return false;
		return true;
	}
	
	static Unit blink(Unit U, MapLocation ret) {
		if (tmp[ret.getX()][ret.getY()] != null) return U;
		MapLocation cloc = mapLoc(U);
		tmp[cloc.getX()][cloc.getY()] = null;
		gc.blink(U.id(), ret); 
		return recalc(U);
	}
	
	static boolean opRanger(Unit U) {
		return U != null && U.team() == oteam && U.unitType() == UnitType.Ranger;
	}
	
	static Unit overcharge(Unit A, Unit B) {
		gc.overcharge(A.id(), B.id());
		recalc(B);
		return recalc(A);
	}
	
	static boolean canHeal(Unit U, Unit u) {
		return your(U,UnitType.Healer) && dist(U,u) <= 30;
	}
	
    static boolean canMove(Unit U, Direction D) {
		MapLocation p = mapLoc(U).add(D);
		return isEmpty(new pii(p.getX(),p.getY())) && lastSense[p.getX()][p.getY()] == cRound;
    }
    
    static boolean canMove(Unit U, int D) {
    		return canMove(U,directions[D]);
    }
    
    static Unit move(Unit U, Direction des) {
        MapLocation cloc = mapLoc(U);
        if (!isEmpty(cloc.add(des))) return U;
        
        tmp[cloc.getX()][cloc.getY()] = null;
        gc.moveRobot(U.id(),des);
        return recalc(U);
    }
    
	static Unit load(Unit U, Unit u) {
		// System.out.println("Loaded "+u.id());
		gc.load(U.id(),u.id());
		tmp[mapLoc(u).getX()][mapLoc(u).getY()] = null;
		return recalc(U);
	}

	static boolean canHarvest(Unit U, Direction D) { 
		MapLocation cloc = mapLoc(U).add(D);
		return onBoard(cloc.getX(), cloc.getY()) 
				&& lastSense[cloc.getX()][cloc.getY()] == cRound
				&& karboniteCount[cloc.getX()][cloc.getY()] > 0;
	}
	
	// UTILITY

	static boolean closer(Unit A, Unit B, Unit C) {
		MapLocation cloc = mapLoc(A);
		return cloc.distanceSquaredTo(mapLoc(B)) < cloc.distanceSquaredTo(mapLoc(C));
	}
	
	static Unit getClosest(Unit U, ArrayList<Unit> V) { // closest unit in V to U (Euclidean)
		int ind = -1, dist = INF;
		for (int i = 0; i < V.size(); ++i) {
			if (mapLoc(U).distanceSquaredTo(mapLoc(V.get(i))) < dist) {
				ind = i;
				dist = (int)mapLoc(U).distanceSquaredTo(mapLoc(V.get(i)));
			}
		}
		if (ind == -1) return null;
		return V.get(ind);
	}

	static Unit recalc(Unit U) {
		U = gc.unit(U.id()); 
		pii cloc = toPii(U); 
		return tmp[cloc.f][cloc.s] = U;
	}

	static Unit heal(Unit U, Unit u) { // heals 
		if (U.attackHeat() >= 10 || u == null || !canHeal(U,u)) return U;
		gc.heal(U.id(), u.id());
		recalc(u); 
		return recalc(U);
	}

	static pii getClosest2(Unit U, ArrayList<pii> V) { // same as above
		int ind = -1, dist = INF;
		pii u = toPii(U);
		for (int i = 0; i < V.size(); ++i) {
			if (u.distanceSquaredTo(V.get(i)) < dist) {
				ind = i;
				dist = u.distanceSquaredTo(V.get(i));
			}
		}
		if (ind == -1) return null;
		return V.get(ind);
	}

    static boolean better(int a, int b, int away) {
        if (away == 0) return a < b;
        return a > b;
    }
    
	static Direction getDir(Unit U, pii M, int away) {
		if (U.movementHeat() >= 10) return Direction.Center;
		
	    pii cloc = toPii(U);
	    int mn = cloc.distanceSquaredTo(M), bes = 0;
	
	    for (int i = 1; i < 9; ++i) {
	        int t = dir[i];
	        pii CLOC = cloc.add(t);
	        if (better(CLOC.distanceSquaredTo(M),mn,away) && canMove(U, t)) {
	            bes = t;
	            mn = (int)CLOC.distanceSquaredTo(M);
	        }
	    }
	    
	    if (bes != 0) return directions[bes];
	    
	    for (int i = 1; i < 9; ++i) {
	        int t = dir[i];
	        pii CLOC = cloc.add(t);
	        if (better(CLOC.distanceSquaredTo(M),mn,away) && valid(CLOC)) {
	            bes = t;
	            mn = (int)CLOC.distanceSquaredTo(M);
	        }
	    }
	    
	    if (bes != 0) return directions[bes];
	    return Direction.Center;
	}
}