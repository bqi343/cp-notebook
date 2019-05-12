import bc.*;

public class Movable extends Player {
	static Unit tryOvercharge(Unit U) {
		if (re.getLevel(UnitType.Healer) != 3 || !fastGC.isAttacker(U)) return null;
		
		pii cloc = toPii(U);
		
		for (int i = -5; i <= 5; i++)
			for (int j = -5; j <= 5; j++) if (i*i+j*j <= 30) {
				pii CLOC = new pii(cloc.f+i,cloc.s+j);
				if (fastGC.valid(CLOC) 
						&& fastGC.your(tmp[CLOC.f][CLOC.s],UnitType.Healer) 
						&& tmp[CLOC.f][CLOC.s].abilityHeat() < 10) {
					fastGC.overcharge(tmp[CLOC.f][CLOC.s],U);
					// System.out.println("Overcharged!");
					return fastGC.recalc(U);
				}
			}
		
		return null;
	}
	
	static Unit findTeammate(Unit U) {
		pii u = get(U,closeFriendGround);
		if (u == null) return U;

		int d = getDistGround(toPii(U),u);
		if (d > 2 || (d > 1 && Math.random() < 0.433)) return tryMove(U, u, 0);
		return U;
	}
	
	static Unit tryMoveEnemy(Unit U) {
		if (U.movementHeat() >= 10) return U;
		pii cloc = toPii(U);
		
		for (int i = 1; i < 9; ++i) {
			pii CLOC = cloc.add(i);
			if (fastGC.VALID(CLOC) 
					&& distCloseEnemyGround[CLOC.f][CLOC.s] < distCloseEnemyGround[cloc.f][cloc.s]
					&& fastGC.canMove(U,i)) 
				return fastGC.move(U,directions[i]);
		}
		
		return U;
	}

	static void tryMoveFriend(Unit U) {
		U = gc.unit(U.id());
		if (U.movementHeat() >= 10) return;
		pii cloc = toPii(U);
		
		for (int i = 1; i < 9; ++i) {
			pii CLOC = cloc.add(i);
			if (fastGC.VALID(CLOC) 
					&& distDamageFriend[CLOC.f][CLOC.s] > distDamageFriend[cloc.f][cloc.s]
					&& fastGC.canMove(U,i)) {
				fastGC.move(U,directions[i]);
				return;
			}
		}
	}
	
    static pii getPri (Unit U) { // sense closest with lowest health
        switch(U.unitType()) {
        		case Ranger:
        			return botRanger.getPri(U);
        		case Mage:
        			return botMage.getPri(U);
        		case Knight:
        			return botKnight.getPri(U);
        		default:
        			pii cloc = toPii(U);
        			Unit bes1 = null, bes2 = null;
                int r = (int)Math.sqrt(81); 
                
                for (int i = -r; i <= r; ++i) // gen
                    for (int j = -r; j <= r; ++j) if (i*i+j*j <= 81) {
                        int X = cloc.f+i, Y = cloc.s+j;
                        if (fastGC.onBoard(X,Y) && fastGC.opAttacker(tmp[X][Y])) {
                            if (bes1 == null) bes1 = tmp[X][Y];
                            else if (fastGC.closer(U,tmp[X][Y],bes1)) bes1 = tmp[X][Y];
                        }
                    }
                
                if (bes1 != null) return toPii(bes1);
                return toPii(bes2);
        }

    }

    static pii firstPriority(Unit U) {
        pii u = getPri(U);
        if (u != null) return u;
        return get(U,closeEnemyGround);
    }

    static Unit move(Unit U, int des) {
        if (des == -1) return U;
        return fastGC.move(U,directions[des]);
    }

    static Unit moveRandom(Unit U) {
        if (U.movementHeat() >= 10) return U;
        int x = ran.nextInt(8)+1;
        if (fastGC.canMove(U,x)) return move(U,x);
        return U;
    }

    static Unit tryMove(Unit U, Direction D) {
        if (D == null || U.movementHeat() >= 10 || !fastGC.canMove(U,D)) return U;
        return fastGC.move(U, D);
    }

    static boolean tr(Unit U, pii M, int z) {
        MapLocation cloc = mapLoc(U);

        int des = -1;
        for (int i = 0; i < 9; ++i) {
            int t = dir[i];
            int ok = nextStep(cloc.getX(),cloc.getY(),M.f,M.s,t);
            if (ok == z && fastGC.canMove(U,t)) {
                if (good(cloc.add(directions[t]))) {
	                	move(U,t);
	                	return true;
                } else des = t;
            }
        }
        
        if (des == -1) return false;
        move(U,des);
        return true;
    }

    
    static Unit tryMoveNaive(Unit U, pii M, int away) {
    		if (U.movementHeat() >= 10) return U;
    		
        pii cloc = toPii(U);
        int mn = cloc.distanceSquaredTo(M), bes = -1;

        for (int i = 0; i < 9; ++i) {
            int t = dir[i];
            pii CLOC = cloc.add(t);
            if (fastGC.better(CLOC.distanceSquaredTo(M),mn,away)
                && fastGC.canMove(U, t)) {
                bes = t;
                mn = (int)CLOC.distanceSquaredTo(M);
            }
        }

        return move(U,bes);
    }

    static Unit tryMove(Unit U, pii M, int away) {
        if (U.movementHeat() >= 10) return U;
        if (M == null) { return moveRandom(U); }
        if (getDistGround(toPii(U),M) == INF) return tryMoveNaive(U,M,away);

        shuffleArray(dir);
        if (tr(U,M,2-2*away)) return fastGC.recalc(U);
        tr(U,M,1); return fastGC.recalc(U);
    }

    static Unit avoidClose(Unit U, pii u) {
        if (u != null && toPii(U).distanceSquaredTo(u) <= 81) return tryMove(U,u,1);
        return U;
    }

    static Unit retreat(Unit U, pii u) { // go to closest factory
        U = avoidClose(U,u);
        pii M = fastGC.closeFactory(U,cteam);
        if (M != null && toPii(U).distanceSquaredTo(M) > 50) return tryMove(U,M,0);
        else return moveRandom(U);
    }

    static Unit avoidFac(Unit U) {
        pii M = fastGC.closeFactory(U,cteam);
        pii u = toPii(U);
        
        if ((u.distanceSquaredTo(M) <= 25 && U.unitType() != UnitType.Knight) &&
           (u.distanceSquaredTo(M) <= 2 || fastGC.isBlocked(tmp[M.f][M.s]))) 
            return tryMove(U, M, 1);
        return U;
    }
    
    static boolean moveAside(pii M) {
    		if(tmp[M.f][M.s] == null) return true;
    		
    		Unit U = tmp[M.f][M.s];
    		if (fastGC.isStructure(U) || U.team() == oteam) return false;
    		if (U.movementHeat() >= 10) {
    			U = tryOvercharge(U);
    			if (U == null) return false;
    		}
    		
    		for(int i = 1; i < 9; i++) if(fastGC.canMove(U, directions[i])) {
    			tryMove(U, directions[i]);
    			return true;
    		}
    		return false;
    }

    ///////////////////////////////////////////////////////////////// HELPER NAVIGATION

    static int nextStep(int x1, int y1, int x2, int y2, int dir) {
        if (x1 == x2 && y1 == y2) return 0;
        if (distGround[x2][y2][x1][y1] == INF) return 0;

        int X1 = x1+xdir[dir], Y1 = y1+ydir[dir];
        if (fastGC.onBoard(X1,Y1)) {
            if (distGround[x2][y2][X1][Y1]+1 == distGround[x2][y2][x1][y1]) return 2;
            if (distGround[x2][y2][X1][Y1] == distGround[x2][y2][x1][y1]) return 1;
        }
        return 0;
    }

    static pii closeUnseen(Unit U) {
        pii cloc = toPii(U);
        return closeLastSense[cloc.f][cloc.s];
    }
}