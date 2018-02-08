import bc.*;

public class botMage extends Attackable {	
	static int getValMage(int x, int y) {
		int t = 0;
		for (int i = x-1; i <= x+1; ++i)
			for (int j = y-1; j <= y+1; ++j)
				if (fastGC.onBoard(i,j) && tmp[i][j] != null) {
					int sgn = (tmp[i][j].team() == cteam) ? -2 : 1;
					if (fastGC.isAttacker(tmp[i][j])) sgn *= 2;
					else if (fastGC.isStructure(tmp[i][j])) sgn *= 3;
					t += sgn;
				}
		
		return t;
	}
	
	static Unit blinkToward(Unit U, pii des) {
		if (re.getLevel(UnitType.Mage) != 4) return null;
		
		U = gc.unit(U.id());
		pii cloc = toPii(U);
		pii bes = new pii(cloc.f, cloc.s);
		
		for (int i = -2; i <= 2; ++i)
			for (int j = -2; j <= 2; ++j) {
				pii CLOC = new pii(cloc.f+i,cloc.s+j);
				if (fastGC.valid(CLOC) && bes.distanceSquaredTo(des) > CLOC.distanceSquaredTo(des))
					bes = CLOC;
			}
		
		if (!bes.equals(cloc)) 
			if (moveAside(bes)) 
				return fastGC.blink(U,new MapLocation(cPlanet,bes.f,bes.s));
		
		for (int i = -2; i <= 2; ++i)
			for (int j = -2; j <= 2; ++j) {
				pii CLOC = new pii(cloc.f+i,cloc.s+j);
				if (fastGC.isEmpty(CLOC) && bes.distanceSquaredTo(des) > CLOC.distanceSquaredTo(des))
					bes = CLOC;
			}
		
		if (!bes.equals(cloc)) 
			return fastGC.blink(U, new MapLocation(cPlanet,bes.f,bes.s));
		
		return null;
	}
	
	static void moveAid(Unit U, pii des) {
		if (des == null) return;
		
		boolean didsmth = true;
		
		pii lst = null;
		while (toPii(U).distanceSquaredTo(des) > 30) {
			U = gc.unit(U.id());

			if (U.abilityHeat() < 10) {
				Unit UU = blinkToward(U,des);
				if (UU != null) { didsmth = true; U = UU; }
			}
			
			if (U.movementHeat() < 10) {
				Direction D = fastGC.getDir(U, des, 0);
				MapLocation next = mapLoc(U).add(D);
				if (D != Direction.Center && moveAside(new pii(next.getX(), next.getY()))) {
					U = fastGC.move(U, D);
					didsmth = true;
				}
			}

			int d = toPii(U).distanceSquaredTo(lst);
			if (3 <= d && d <= 30 && lst != null && tmp[lst.f][lst.s] != null) {
				U = fastGC.attack(U, tmp[lst.f][lst.s]);
			} else {
				pii u = firstPriority(U);
				if (toPii(U).distanceSquaredTo(u) <= 30) {
					lst = u;
					U = fastGC.attack(U, tmp[u.f][u.s]);
					didsmth = true;
				}
			}

			if (didsmth == false) return;
			U = tryOvercharge(U); if (U == null) return;
			didsmth = false;
		}
		
		while (true) {
			des = firstPriority(U);
			if (toPii(U).distanceSquaredTo(des) > 64) return;
			U = gc.unit(U.id());

			if (U.abilityHeat() < 10) {
				Unit UU = blinkToward(U,des);
				if (UU != null) { didsmth = true; U = UU; }
			}
			
			if (U.movementHeat() < 10) {
				Direction D = fastGC.getDir(U, des, 0);
				MapLocation next = mapLoc(U).add(D);
				if (D != Direction.Center && moveAside(new pii(next.getX(), next.getY()))) {
					U = fastGC.move(U, D);
					didsmth = true;
				}
			}
				
			pii u = firstPriority(U);
			if (toPii(U).distanceSquaredTo(u) <= 30) {
				U = fastGC.attack(U, tmp[u.f][u.s]);
				didsmth = true;
			}

			if (didsmth == false) return;
			U = tryOvercharge(U); if (U == null) return;
			didsmth = false;
		}
	}
	
	static pii select(Unit U) {
		pii cloc = toPii(U), des = null;
		int r = (int)Math.sqrt(81), bes = 0;

        for (int i = -r; i <= r; ++i) 
            for (int j = -r; j <= r; ++j) if (i*i+j*j <= 81) {
                int X = cloc.f+i, Y = cloc.s+j;
                if (fastGC.onBoard(X,Y) && tmp[X][Y] != null && botMage.getValMage(X,Y) > bes) {
                    des = new pii(X,Y);
                    bes = botMage.getValMage(X,Y);
                }
            }
        
        if (des != null && bes > 2) return des;
        return null;
	}
	
	static int nearbyHeal(Unit U) {
		if (re.getLevel(UnitType.Healer) != 3) return 0;
		
		pii cloc = toPii(U);
		
		int co = 0;
		for (int i = -5; i <= 5; i++)
			for (int j = -5; j <= 5; j++) if (i*i+j*j <= 30) {
				pii CLOC = new pii(cloc.f+i,cloc.s+j);
				if (fastGC.valid(CLOC) 
						&& fastGC.your(tmp[CLOC.f][CLOC.s],UnitType.Healer) 
						&& tmp[CLOC.f][CLOC.s].abilityHeat() < 10) co ++;
			}
		
		return co;
	}
	
	static boolean suddenAttack(Unit U) {
		if (!fastGC.isBlinkReady(U) || nearbyHeal(U) < 2) return false;
		pii des = select(U); if (des == null) return false;
		
        moveAid(U,des);
		System.out.println("Attacked! "+mapLoc(U));
        return true;
	}
	
	static Unit positionPassive(Unit U, Unit u) {
		if (u == null) return U;

		int d = toPii(U).distanceSquaredTo(toPii(u));
		
		if (d <= 2) return tryMoveNaive(U,toPii(u),1);
		if (d <= 64) return U;
		
		return tryMove(U,toPii(u),0);
	}
	
	static Unit nearbyRanger(Unit U) {
		pii cloc = toPii(U);
		for (int i = -8; i <= 8; ++i)
			for (int j = -8; j <= 8; ++j) {
				pii CLOC = new pii (cloc.f+i,cloc.s+j);
				if (i*i+j*j <= 64 && fastGC.onBoard(CLOC.f, CLOC.s)) 
					if (fastGC.opRanger(tmp[CLOC.f][CLOC.s])) return tmp[CLOC.f][CLOC.s];
			}
		return null;
	}
	
	static Unit retreatPassive(Unit U, Unit u) {
		Unit uu = nearbyRanger(U);
		if (uu != null) return tryMoveNaive(U,toPii(uu),1);
		
		if ((u.unitType() == UnitType.Mage && mapLoc(U).distanceSquaredTo(mapLoc(u)) <= 49) 
			|| (u.unitType() == UnitType.Knight && mapLoc(U).distanceSquaredTo(mapLoc(u)) <= 16))
				return tryMoveNaive(U,toPii(u),1);
		return U;
	}
	
	static void runPassive(Unit U) {
		U = structRocket.runRocket(U); if (U == null) return;
		if (runHealer(U)) return;
		
		if (U.movementHeat() >= 10) {
			if (U.attackHeat() >= 10) return;
			pii u = getPri(U,30); if (u == null) return;
			Unit uu = tmp[u.f][u.s]; fastGC.attack(U,uu); 
			return;
		} 
		
		pii u = getPri(U,64);
		
		if (u == null || tmp[u.f][u.s] == null) { decide(U); return; }
		Unit uu = tmp[u.f][u.s];

		U = positionPassive(U,uu); 
		U = fastGC.attack(U,uu); 
		U = retreatPassive(U,uu);
	}
	
	static pii getPri(Unit U, int mx) {
		pii cloc = toPii(U);
		
		int r = (int)Math.sqrt(mx); 
        int x = -1, y = -1, bes = 0;

        for (int i = -r; i <= r; ++i) // gen
            for (int j = -r; j <= r; ++j) if (i*i+j*j <= mx && i*i+j*j >= 3) {
                int X = cloc.f+i, Y = cloc.s+j;
                if (fastGC.onBoard(X,Y) && tmp[X][Y] != null && botMage.getValMage(X,Y) > bes) {
                    x = X; y = Y; 
                    bes = botMage.getValMage(X,Y);
                }
            }

        if (x == -1) return null;
        return new pii(x,y);
	}
	
	static pii getPri(Unit U) { return getPri(U,30); }
	
    static void run(Unit U) {
		if (suddenAttack(U)) return;
		if (cRound > 225) {
			runPassive(U);
			return;
		}
		attack(U);
    }
}

