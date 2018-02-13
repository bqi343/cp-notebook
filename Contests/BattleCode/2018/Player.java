// latest: https://www.battlecode.org/#/materials/releases
// specs: https://s3.amazonaws.com/battlecode-2018/specs/battlecode-specs-2018.html
// javadocs: https://s3.amazonaws.com/battlecode-2018/api/java/index.html
// COMMON ERROR: if unit is in garrison it can't do anything ...

import bc.*;
import java.util.*;

public class Player extends Globals {
	static void initialize() { // initialize teams, variables, etc
		gc = new GameController();
		for (int i = 0; i < 9; ++i) dir[i] = i;

		if (gc.team() == Team.Red) {
			cteam = Team.Red; oteam = Team.Blue;
		} else {
			cteam = Team.Blue; oteam = Team.Red;
		}

		if (gc.planet() == Planet.Earth) {
			cPlanet = Planet.Earth; oPlanet = Planet.Mars;
		} else {
			cPlanet = Planet.Mars; oPlanet = Planet.Earth; 
		}

		C = gc.startingMap(cPlanet); O = gc.startingMap(oPlanet);

		for (int X = 0; X < C.getWidth(); ++X)
			for (int Y = 0; Y < C.getHeight(); ++Y) 
				genComp(X,Y,50*X+Y+1);
		
		for (int X = 0; X < O.getWidth(); ++X)
			for (int Y = 0; Y < O.getHeight(); ++Y) 
				genCompO(X,Y,50*X+Y+1);
		
		for (int X = 0; X < C.getWidth(); ++X)
			for (int Y = 0; Y < C.getHeight(); ++Y) {
				sz[comp[X][Y]] ++;
				karboniteCount[X][Y] = (int)C.initialKarboniteAt(new MapLocation(cPlanet,X,Y));
				totKarb[comp[X][Y]] += karboniteCount[X][Y];
				genBFS.genDist(X,Y);
			}
		
		VecUnit V = gc.myUnits();
		for (int i = 0; i < V.size(); ++i) {
			pii cloc = toPii(V.get(i));
			int c = comp[cloc.f][cloc.s];
			if (!ok[c]) totsz += sz[c];
			ok[c] = true;
		}
		
		double tot = 0;
		int totFac = 0;
		for (int i = 1; i <= 2500; ++i) if (ok[i]) {
			double des = Math.pow(totKarb[i]+1,1.0/3)/3.5;
			tot += totKarb[i];
			minFac[i] = (int)Math.ceil(des);
			totFac += minFac[i];
		}
		
		if (cPlanet == Planet.Earth) {
			while (totFac < 3) {
				for (int i = 1; i <= 2500; ++i) {
					if (totFac >= 4) break;
					if (ok[i]) {
						minFac[i] ++;
						totFac ++;
					}
				}
			}
		}
		for (int i = 1; i <= 2500; ++i) minWork[i] = 6*minFac[i];
		
		rushRounds = Math.max(10, (int)Math.ceil(6*Math.pow(tot,1.0/3)/3.5));
		if (cPlanet == Planet.Mars) rushRounds = 1001;
		System.out.println("RUSH "+rushRounds);

		pat = gc.asteroidPattern();
	}

	static boolean splitMap(VecUnit V) {
		for (int i = 0; i < V.size(); ++i)
			for (int j = 0; j < V.size(); ++j) 
				if (V.get(i).team() == cteam && V.get(j).team() == oteam)
					if (getDistGround(V.get(i),V.get(j)) != INF) return false;
		return true;
	}
	
	static void initializeEarth() { 	// research ranger!
		VecUnit V = C.getInitial_units();
		
		for (int i = 0; i < V.size(); ++i) 
			if (V.get(i).team() == oteam) 
				oFac.add(toPii(V.get(i)));

		boolean[] counted = new boolean[2500];
		int tot = 0;
		for (int i = 0; i < V.size(); ++i) {
			if (V.get(i).team() == oteam) 
				oFac.add(toPii(V.get(i)));
			else {
				if(!counted[comp(V.get(i))]) tot += totKarb[comp(V.get(i))];
				counted[comp(V.get(i))] = true;
			}
		}
			
		if(tot >= 1200) gc.queueResearch(UnitType.Worker); // 25
		
		if (splitMap(V)) { // 250
			gc.queueResearch(UnitType.Rocket); // 50
			gc.queueResearch(UnitType.Rocket); // 100
			gc.queueResearch(UnitType.Rocket); // 100
		}
		
		// 225
		gc.queueResearch(UnitType.Healer); // 25
		gc.queueResearch(UnitType.Healer); // 100
		gc.queueResearch(UnitType.Healer); // 100
		
		// 75
		gc.queueResearch(UnitType.Mage); // 25
		
		// 250
		gc.queueResearch(UnitType.Mage); // 75
		gc.queueResearch(UnitType.Mage); // 100
		gc.queueResearch(UnitType.Mage); // 75
		
		gc.queueResearch(UnitType.Rocket); // 50
		
		gc.queueResearch(UnitType.Ranger); // 25
		gc.queueResearch(UnitType.Ranger); // 100
		
		gc.queueResearch(UnitType.Ranger); // 200

		structRocket.genMarsVal();
		nextDestination = structRocket.chooseDestination();
	}

	public static void main(String[] args) { // runs program
		initialize();
		if (cPlanet == Planet.Earth) initializeEarth();
		while (true) turn();
	}

	static void propagate(Unit U) { // update isSense
		pii cloc = toPii(U);
		int v = (int)U.visionRange();
		int r = (int)Math.sqrt(U.visionRange());
		for (int i = -r; i <= r; ++i) {
			for (int j = -r; j <= r; ++j) if (i*i+j*j <= v) {
				int X = cloc.f+i, Y = cloc.s+j;
				if (fastGC.onBoard(X,Y)) {
					pii CLOC = new pii(X,Y);
					lastSense[X][Y] = cRound;
					if (lastSeen != cRound 
						&& fastGC.opUnit(tmp[X][Y])
						&& getDistGround(cloc, CLOC) != INF)		    				
						lastSeen = cRound;
				}
			}
		}
	}

	static void propagateBad(Unit U) {
		pii cloc = toPii(U);
		int r = (int)Math.sqrt(50);
		for (int i = -r; i <= r; ++i) {
			for (int j = -r; j <= r; ++j) if (i*i+j*j <= 50) {
				int X = cloc.f+i, Y = cloc.s+j;
				if (fastGC.onBoard(X,Y)) {
					pii CLOC = new pii(X,Y);
					if (getDistGround(cloc, CLOC) != INF) bad[X][Y] = true;
				}
			}
		}
	}

	static void updateVision() {
		for (int i = 0; i < UNITS.size(); i++) propagate(UNITS.get(i));
		for (int i = 0; i < units.size(); i++) {
			Unit unit = units.get(i);
			if (unit.team() == oteam && fastGC.isAttacker(unit) && unit.location().isOnMap()) 
				propagateBad(unit);
		}
		
		for (int i = 0; i < 50; ++i) 
			for (int j = 0; j < 50; ++j) if (lastSense[i][j] == cRound) {
				if (fastGC.isStructure(tmp[i][j])) karboniteCount[i][j] = 0;
				else karboniteCount[i][j] = (int)gc.karboniteAt(new MapLocation(cPlanet,i,j));
			}
	}

	static void clear() {
		for (int i = 0; i < 50; ++i)
			for (int j = 0; j < 50; ++j) {
				tmp[i][j] = null;
				bad[i][j] = false;
				passable[i][j] = (comp[i][j] != 0);
			}

		for (int i = 1; i <= 2500; ++i) {
			work[i] = fac[i] = cNum[i] = 0;
			ok[i] = false;
		}

		cFac.clear(); hasNearbyMage = new HashSet<>();
		rocket = attack = worker = ranger = healer = knight = mage = 0;
		factory = 0;

		startTime = System.nanoTime();
		cRound = (int)gc.round();

		botRanger.snipeCandidate.clear();
		re = gc.researchInfo();
		units = gc.units();
		UNITS.clear();
	}

	static void printInfo() {
		System.out.println("Current round: "+cRound);
		System.out.println("Karbonite: "+gc.karbonite());
		System.out.println("Time: "+(double)gc.getTimeLeftMs()/1000);
		System.out.println("Units: "+UNITS.size());
		System.out.println(worker+" "+ranger+" "+healer+" "+mage);
		// System.out.println("WP "+getCollectedKarbonite(cRound-20,cRound)+" "+workerCost);
	}

	static void runAsteroid() {
		if (pat.hasAsteroid(cRound)) {
			AsteroidStrike PAT = pat.asteroid(cRound);
			MapLocation cloc = PAT.getLocation();
			if (cPlanet == Planet.Mars) karboniteCount[cloc.getX()][cloc.getY()] += PAT.getKarbonite();
			else {
				for (int x = cloc.getX()-2; x <= cloc.getX()+2; ++x) if (0 <= x && x < O.getWidth())
					for (int y = cloc.getY()-2; y <= cloc.getY()+2; ++y) if (0 <= y && y < O.getHeight()) {
						if (x == cloc.getX() && y == cloc.getY()) continue;
						if (compO[x][y] == compO[cloc.getX()][cloc.getY()]) {
							marsVal[x][y] += PAT.getKarbonite();
						}
					}
			}
		}
	}

	static double getTime() {
		return (double)(System.nanoTime()-startTime)/1000000;
	}
	
	static void testNearby(Unit U) {
		pii cloc = toPii(U);
		
		for (int i = -5; i <= 5; ++i)
			for (int j = -5; j <= 5; ++j) if (i*i+j*j <= 30) {
				pii x = new pii (cloc.f+i,cloc.s+j);
				if (fastGC.onBoard(x.f,x.s) && fastGC.your(tmp[x.f][x.s],UnitType.Mage)) {
					hasNearbyMage.add(U.id());
					return;
				}
			}
				
	}
	
	static void turn() { // turn by turn
		if (gc.round() % 3 == 0) { System.runFinalization(); System.gc(); }
		if (gc.getTimeLeftMs() < 1000) { gc.nextTurn(); return; }

		runAsteroid(); clear(); Attackable.setKillMode();

		if (units.size() == 0) { gc.writeTeamArray(0, 1); gc.nextTurn(); return; }
		
		for (int i = 0; i < units.size(); i++) {
			Unit unit = units.get(i); pii cloc = toPii(unit);
			
			if (fastGC.your(unit) && cloc != null) {
				int c = comp[cloc.f][cloc.s];
				cNum[c] ++; ok[c] = true;
				
				UnitType U = unit.unitType();
				switch(U) {
					case Worker:
						work[c] ++; worker ++;
						break;
					case Factory:
						fac[c] ++; cFac.add(cloc);
						if(unit.isFactoryProducing() != 0) {
							UnitType U2 = unit.factoryUnitType();
							if (U2 == UnitType.Ranger) ranger++;
							else if(U2 == UnitType.Healer) healer++;
						}
						passable[cloc.f][cloc.s] = false;
						break;
					case Rocket:
						cFac.add(cloc);
						passable[cloc.f][cloc.s] = false;
						if (unit.structureGarrison().size() != unit.structureMaxCapacity()) rocket ++;
						break;
					default:
						attack ++; cattack[c]++;
						if(cattack[c] > cattack[maxAtk]) maxAtk = comp(unit);
						switch (U) {
							case Ranger:
								ranger ++;
								break;
							case Healer:
								healer ++;
								testNearby(unit);
								break;
							case Knight:
								knightRushing.putIfAbsent(unit.id(), false);
								knight ++;
								break;
							case Mage:
								mage ++;
								break;
							default:
						}
				}
				
				UNITS.add(unit);
			} 
			if (unit.team() == oteam) {
				if((unit.unitType() == UnitType.Mage || unit.unitType() == UnitType.Ranger)) mageSeen = true;
				enemySeen = true;
			}
			if (cloc != null) tmp[cloc.f][cloc.s] = unit;
		}

		updateVision(); 

		genBFS.gen(); 
		Collections.sort(UNITS, new UnitComparator());
		printInfo(); 

		coolvariable = true;
		MAXLIMIT = 175;
		
		try {
			Structure.tryMake();
			
			for (int i = 0; i < Math.min(MAXLIMIT+50,UNITS.size()); i++) {
				try {
					processUnit(UNITS.get(i));
				} catch (Exception e) {
					System.out.println("ERROR!");
					System.out.println(mapLoc(UNITS.get(i)));
					e.printStackTrace();
				}
			}

			botRanger.trySnipe();
		} catch (Exception e) {
			System.out.println("ERROR!");
			e.printStackTrace();
		}
		
		System.out.println("-------------------");
		gc.nextTurn();
	}
	
	
	static boolean processUnit(Unit U) { // run a unit
		U = fastGC.upd(U);
		if (U == null) return false;
		switch (U.unitType()) {
			case Factory:
				structFactory.run(U);
				break;
			case Healer:
				botHealer.run(U);
				break;
			case Knight:
				botKnight.run(U);
				break;
			case Mage:
				botMage.run(U);
				break;
			case Ranger: 
				botRanger.run(U);
				break;
			case Rocket:
				structRocket.run(U);
				break;
			case Worker:
				botWorker.run(U);
				break;
			default:
		}
		return true;
	}
}
