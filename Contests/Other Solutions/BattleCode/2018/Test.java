import java.util.ArrayList;

import bc.*;

public class Test extends Player {
	static void deleteStuff() {
		for (int i = 0; i < units.size(); ++i) units.get(i).delete();
		units.delete();
		for (int i = 0; i < UNITS.size(); ++i) UNITS.get(i).delete();
		UNITS.clear();
	}

	static void processTime() {
		long cTime = System.nanoTime() - startTime;
		mxTime = Math.max(mxTime, cTime);
		totTime += Math.max(0, cTime-50000000);

		// System.out.println(System.nanoTime() - startTime);
		// System.out.println("Additional time used: "+(double)totTime/1000000000);
	}

	static boolean yourBadAttacker(Unit U) {
		if (U == null) return false;
		return fastGC.isAttacker(U) && U.team() == cteam && U.movementHeat() >= 10 && U.attackHeat() >= 10;
	}

	/*static boolean disintegrate(Unit U) {
		int c = comp(U);
		if (sz[c] == cNum[c]) {
			fastGC.disintegrateUnit(U);
			cNum[c] --;
			return true;
		}
		return false;
	}*/
	
	static boolean isAdjDiagonal(MapLocation A, MapLocation B) {
		if (!fastGC.valid(A) || !fastGC.valid(B)) return false;
		if (A.distanceSquaredTo(B) <= 2) return true;
		return false;
	}
	
    static pii closerLocation(Unit U, pii M) {
    		int bes = INF;
    		pii BES = null;
    		
    		for (int i = -7; i <= 7; i++)
    			for (int j = -7; j <= 7; j++) if (i*i+j*j <= 50) {
    				pii t = new pii(M.f+i,M.s+j);
    				if (!fastGC.valid(t)) continue;
    				if (i*i+j*j < bes && getDistGround(t,M) < INF) {
    					bes = i*i+j*j;
    					BES = t;
    				}
    			}
    		return BES;
    }
    
    public static void testMoveAway() {
        VecUnit units = gc.myUnits();
    		for (int i = 0; i < units.size(); i++) {
            Unit unit = units.get(i);
            Movable.tryMove(unit, new pii(0,0), 1);
    		}
    }

    static void testRetreat() {
        VecUnit units = gc.myUnits();
        for (int i = 0; i < units.size(); i++) Movable.retreat(units.get(i),null);
        gc.nextTurn();
    }
    
    static MapLocation dangerPos(Unit U) { // returns location of danger
		VecUnit nearby = gc.senseNearbyUnitsByTeam(mapLoc(U),1,oteam);
		for(int i = 0; i < nearby.size(); i++) {
			if(nearby.get(i).unitType() == UnitType.Knight) return mapLoc(nearby.get(i));
		}
		nearby = gc.senseNearbyUnitsByTeam(mapLoc(U), 30, oteam);
		for(int i = 0; i < nearby.size(); i++) {
			if(nearby.get(i).unitType() == UnitType.Mage) return mapLoc(nearby.get(i));
		}
		nearby = gc.senseNearbyUnitsByTeam(mapLoc(U), 50, oteam);
		for(int i = 0; i < nearby.size(); i++) {
			if(nearby.get(i).unitType() == UnitType.Ranger) return mapLoc(nearby.get(i));
		}
		return null;
	}
	
	static boolean inDanger(Unit U) { // can U be attacked?
		VecUnit nearby = gc.senseNearbyUnitsByTeam(mapLoc(U),1,oteam);
		for(int i = 0; i < nearby.size(); i++) {
			if(nearby.get(i).unitType() == UnitType.Knight) return true;
		}
		nearby = gc.senseNearbyUnitsByTeam(mapLoc(U), 30, oteam);
		for(int i = 0; i < nearby.size(); i++) {
			if(nearby.get(i).unitType() == UnitType.Mage) return true;
		}
		nearby = gc.senseNearbyUnitsByTeam(mapLoc(U), 50, oteam);
		for(int i = 0; i < nearby.size(); i++) {
			if(nearby.get(i).unitType() == UnitType.Ranger) return true;
		}
		return false;
	}
	
	static void tryLoad(Unit U) {
		if (!U.location().isOnMap()) return;
		VecUnit a = gc.senseNearbyUnitsByTeam(mapLoc(U), 2, cteam);
		for (int i = 0; i < a.size(); ++i) {
			if (gc.canLoad(U.id(), a.get(i).id())) {
				gc.load(U.id(),a.get(i).id());
			} 
		}
	}
	
    static void runDead(Unit U) {
		if (U.unitType() != UnitType.Mage && U.health()*3 <= U.maxHealth()) 
			Movable.retreat(U,null);
    }
    
	static void testEssential(Unit U) {
		if (getNum(U,UnitType.Worker) == work[comp(U)]) {
			VecUnit V = gc.senseNearbyUnitsByTeam(mapLoc(U), 2, cteam);
			if (V.size() == 0) return;
			Unit u = V.get(0);
			gc.disintegrateUnit(u.id());
			
			Direction d = mapLoc(U).directionTo(mapLoc(u));
			System.out.println("HI "+d);
			if (gc.canUnload(U.id(),d)) gc.unload(U.id(),d);
		}
	}
	
	static MapLocation closeUnseen(Unit U) {
		int r = (int)Math.sqrt(169);
		MapLocation cloc = mapLoc(U);
		MapLocation bes = null;
		int lst = INF;
		
		for (int i = -r; i <= r; ++i) 
				for (int j = -r; j <= r; j += 2) 
	                if (i*i+j*j <= 169) {
					    MapLocation CLOC = new MapLocation(cPlanet,cloc.getX()+i,cloc.getY()+j);
					    if (!fastGC.valid(CLOC)) continue;
					    if (lastSense[CLOC.getX()][CLOC.getY()] < lst) {
						     bes = CLOC;
						     lst = lastSense[CLOC.getX()][CLOC.getY()];
					     }
				}
	
		return bes;
	}
	
    static Unit getWeakest(Unit U, ArrayList<Unit> V) {
        int ind = -1, health = INF;
        for (int i = 0; i < V.size(); ++i) {
        		// if (needAttack && !isAttacker(V.get(i))) continue;
            if (V.get(i).health() < health && gc.canAttack(U.id(),V.get(i).id())) {
                ind = i;
                health = (int)V.get(i).health();
            }
        }
        if (ind != -1) return V.get(ind);
        return null;
    }
    
    static Unit closeStructure(Unit U) {
    		ArrayList<Unit> V = genStructure(U,25);
        ArrayList<Unit> A = new ArrayList<>();
        for (int i = 0; i < V.size(); ++i) 
            if (gc.unit(V.get(i).id()).structureIsBuilt() == 1
                && V.get(i).health() < V.get(i).maxHealth()) // and isn't being built ...
                A.add(V.get(i));

        return fastGC.getClosest(U,A);
    }
    

    static ArrayList<Unit> genStructure(Unit U, int dist) { // find your own structures
		MapLocation cloc = mapLoc(U);
		int r = (int)Math.sqrt(dist);
		
		ArrayList<Unit> A = new ArrayList<>();
		for (int i = -r; i <= r; ++i) 
	    		for (int j = -r; j <= r; ++j) if (i*i+j*j <= dist) {
	    			int X = cloc.getX()+i, Y = cloc.getY()+j;
	    			if (fastGC.onBoard(X,Y) && tmp[X][Y] != null 
	    				&& tmp[X][Y].team() == cteam
	    				&& fastGC.isStructure(tmp[X][Y])) A.add(tmp[X][Y]);
	    		}
		
		return A;
	}
    
    static boolean build(Unit U) {
		Unit f = closeFactoryThatNeedsRepair(U);
		if (f == null) return false;
		if (isAdjDiagonal(mapLoc(f), mapLoc(U))) {
			if(gc.canBuild(U.id(), f.id())) {
				gc.build(U.id(), f.id());
				return true;
			}
		} else {
			Movable.tryMove(U, toPii(f), 0);
			return false;
		}
		return false;
	}

	static boolean disintegrate(Unit U) {
		int c = comp(U);
		if (cPlanet == Planet.Earth && sz[c] <= 3*cNum[c]/2) {
			gc.disintegrateUnit(U.id());
			cNum[c] --;
			return true;
		}
		return false;
	}
    
    static int getNum(Unit U, UnitType u) {
		VecUnitID V = U.structureGarrison();
		int num = 0;
		for (int i = 0; i < V.size(); ++i) 
			if (gc.unit(V.get(i)).unitType() == u)
				num ++;
		return num;
	}
    
    /*static Unit farthestFromBase() { //find furthest worker/healer from base
		VecUnit units = gc.myUnits();
		long hi = 0; int ind = -1;
		for(int i = 0; i < units.size(); i++) {
			if(units.get(i).unitType() == UnitType.Healer || units.get(i).unitType() == UnitType.Worker) {
				MapLocation fac = close(units.get(i),UnitType.Factory,cteam);
				long dist = mapLoc(units.get(i)).distanceSquaredTo(fac);
				if(dist > hi) {
					hi = dist;
					ind = i;
				}
			}
		}
		if(ind == -1) return null;
		return units.get(ind);
	}*/
    
    /* VecUnit V = gc.senseNearbyUnitsByType(mapLoc(U),INF,unitType);
    ArrayList<Unit> v = new ArrayList<>();
    for (int i = 0; i < V.size(); ++i) 
        if (V.get(i).team() == te) 
            v.add(V.get(i));
            
    Unit u = getClosest(U,v);
    if (u == null) return null;
    return mapLoc(u);
	 */

	/*static int absDist(Unit U, Unit u) {
		MapLocation A = mapLoc(U);
		MapLocation B = mapLoc(u);
		return Math.max(Math.abs(A.getX()-B.getX()), Math.abs(A.getY()-B.getY()));
	}*/

    static Unit closeFactoryThatNeedsRepair(Unit U) {
        VecUnit near = gc.senseNearbyUnitsByType(mapLoc(U), 30, UnitType.Factory);
        Unit ans = null;
        long minDist = INF;
        for(int i = 0; i < near.size(); i++) {
        		if(near.get(i).health() < 300 && mapLoc(near.get(i)).distanceSquaredTo(mapLoc(U)) < minDist) {
        			minDist = mapLoc(near.get(i)).distanceSquaredTo(mapLoc(U));
        			ans = near.get(i);
        		}
        }
        return ans;
    }
	/*static ArrayList<Unit> con(VecUnit V) {
		ArrayList<Unit> A = new ArrayList<>();
		for (int i = 0; i < V.size(); ++i) A.add(V.get(i));
		return A;
	}*/

	static boolean isAdj(MapLocation A, MapLocation B) {
		// check if two locations are exactly one square apart
		if (!fastGC.valid(A) || !fastGC.valid(B)) return false;
		if (A.distanceSquaredTo(B) == 1) return true;
		return false;
	}

	static int numFree(Unit U) {
		pii cloc = toPii(U);

		int t = 0;
		for (int i = 1; i < 9; ++i) {
			pii CLOC = cloc.add(i);
			if (fastGC.valid(CLOC) && tmp[CLOC.f][CLOC.s] == null) t ++;
		}
		
		return t;
	}
	

	static void overchargeNaive(Unit U) {
        if (U.abilityHeat() >= 10 || re.getLevel(UnitType.Healer) != 3) return;
        
        pii cloc = toPii(U);
        Unit bes = null;
        
		for (int i = -5; i <= 5; ++i)
			for (int j = -5; j <= 5; ++j) if (i*i+j*j <= 30) {
				pii CLOC = new pii(cloc.f+i,cloc.s+j);
				if (!fastGC.valid(CLOC)) continue;
				Unit u = tmp[CLOC.f][CLOC.s];
				
				if (yourBadAttacker(u)) 
					if (2*u.health() >= u.maxHealth())
						if (bes == null || UnitComparator.getVal(u) < UnitComparator.getVal(bes)) 
							bes = u;
			}
		
		if (bes != null) {
			fastGC.overcharge(U, bes);
			gc.overcharge(U.id(), bes.id());
			fastGC.recalc(U);
			fastGC.recalc(bes);
			System.out.println("Overcharged attacker!");
			Player.processUnit(bes);
			return;
		}
	}
	/*
	ArrayList<Unit> A = new ArrayList<>();
	for (int i = -12; i <= 12; ++i)
		for (int j = -12; j <= 12; ++j) if (i*i+j*j <= 144) {
			int x = cloc.f+i, y = cloc.s+j;
			if (fastGC.valid(x,y) && fastGC.yourDamagedUnit(tmp[x][y]) && fastGC.isAttacker(tmp[x][y])) A.add(tmp[x][y]);
		}
	
	return fastGC.getClosest(U,A);*/
}
