import bc.*;

public class botHealer extends Attackable {
	static pii getPri(Unit U) {
		pii cloc = toPii(U);
		Unit best = null, best1 = null;
		
		for (int i = -5; i <= 5; ++i)
			for (int j = -5; j <= 5; ++j) if (i*i+j*j <= 30) {
				int x = cloc.f+i, y = cloc.s+j;
				if (fastGC.valid(x,y) && fastGC.yourDamagedUnit(tmp[x][y])) {
					if (fastGC.isAttacker(tmp[x][y])) {
						if (best == null || tmp[x][y].health() < best.health()) best = tmp[x][y];
					} else {
						if (best1 == null || tmp[x][y].health() < best1.health()) best1 = tmp[x][y];
					}
				}
			}
		
		if (best != null) return toPii(best);
		if (best1 != null) return toPii(best1);
		
		for (int i = -7; i <= 7; ++i)
			for (int j = -7; j <= 7; ++j) if (i*i+j*j > 30 && i*i+j*j <= 50) {
				int x = cloc.f+i, y = cloc.s+j;
				if (fastGC.valid(x,y) && fastGC.yourDamagedUnit(tmp[x][y])) {
					if (fastGC.isAttacker(tmp[x][y])) {
						if (best == null || tmp[x][y].health() < best.health()) best = tmp[x][y];
					} else {
						if (best1 == null || tmp[x][y].health() < best1.health()) best1 = tmp[x][y];
					}
				}
			}
		
		if (best != null) return toPii(best);
		if (best1 != null) return toPii(best1);
		return null;
	}
	
	static Unit healPriority(Unit U, pii getPri) {
		if (getPri == null) return null;
		Unit u = tmp[getPri.f][getPri.s];
		if (fastGC.yourDamagedUnit(u)) return u;
		return null;
	}
	
    static void run(Unit U) { 
    		if (fastGC.surrounded(U)) {
    			Unit H = healPriority(U,getPri(U));
    			if (H != null) fastGC.heal(U,H);
    			return;
    		}
    		
    		U = structRocket.runRocket(U); if (U == null) return;
        pii u = get(U,closeEnemyEuclid);
        if (u != null && toPii(U).distanceSquaredTo(u) <= 81) U = tryMoveNaive(U,u,1);
		U = avoidFac(U);

		pii h = getPri(U);
		Unit H = healPriority(U,h);
		
        if (h == null) {
        		tryMoveFriend(U);
        		return;
        } else {
            U = position(U,H); 
            U = fastGC.heal(U,H);
            U = retreatAttacker(U,H);
        }
    }	
}