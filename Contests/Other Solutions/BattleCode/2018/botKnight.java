import bc.*;

public class botKnight extends Attackable {
	static pii getPri(Unit U) {
		pii M = toPii(U);
		pii bes1 = null, bes2 = null;
		
		for (int x = M.f-3; x <= M.f+3; x++) {
			for (int y = M.s-3; y <= M.s+3; y++) {
				if (fastGC.valid(x, y)) {
					if (tmp[x][y] != null && tmp[x][y].team() == oteam) {
						if (fastGC.isAttacker(tmp[x][y]) || fastGC.isStructure(tmp[x][y])) {
							if (getDistGround(M,bes1) > getDistGround(M,new pii(x, y))) {
								bes1 = new pii(x,y);
							} else if (getDistGround(M,bes1) == getDistGround(M,new pii(x, y)) && fastGC.isAttacker(tmp[x][y])) {
								bes1 = new pii(x,y);
							}
						} else {
							if (getDistGround(M,bes2) > getDistGround(M,new pii(x, y))) {
								bes2 = new pii(x, y);
							}
						}
					}
				}
			}
		}
		
		if (bes1 == null) return bes2;
		return bes1;
	}

	static Unit tryAttack(Unit U) {
		pii cloc = toPii(U);
		Unit bes1 = null, bes2 = null;
		
		for (int i = 1; i < 9; i ++) {
            int X = cloc.f+xdir[i], Y = cloc.s+ydir[i];
            if (fastGC.onBoard(X,Y) && tmp[X][Y] != null && tmp[X][Y].team() == oteam) {
                if (fastGC.isAttacker(tmp[X][Y]) || fastGC.isStructure(tmp[X][Y])) {
                    if (bes1 == null) bes1 = tmp[X][Y];
                    else if (tmp[X][Y].health() < bes1.health()) bes1 = tmp[X][Y];
                } else {
                    if (bes2 == null) bes2 = tmp[X][Y];
                    else if (tmp[X][Y].health() < bes2.health()) bes2 = tmp[X][Y];
                }
            }
        }
		
		if (bes1 != null) return fastGC.attack(U, bes1);
		return fastGC.attack(U, bes2);
	}
	
    static void run(Unit U) {
    		if (cRound > 300) { fastGC.disintegrateUnit(U); return; }
    		
    		pii cloc = toPii(U);
    		U = tryAttack(U);
    		pii u = firstPriority(U);

     	if (cloc.distanceSquaredTo(u) > 50) {
     		pii uu = fastGC.closeFactory(U, oteam);
     		if (uu != null) u = uu;
     	}
    		
    		if (u != null) {
    			if (cloc.distanceSquaredTo(u) > 2) U = tryMove(U,u,0);
        		U = tryAttack(U);
    		} else {
        		U = avoidFac(U);
        		U = findTeammate(U);
    		}
    }
}