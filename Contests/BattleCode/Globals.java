import java.util.*;
import bc.*;

public class Globals {
	// GAME
	static GameController gc;
	static Team cteam, oteam;
	static Planet cPlanet, oPlanet;
	static PlanetMap C, O;
	static Map<Integer,Integer> R = new HashMap<>(), wait = new HashMap<>();
	static ResearchInfo re;
	static int cRound = 0;

	// MARS 
	static AsteroidPattern pat;
	static int[][] marsVal = new int[50][50];
	static int rocket = 0, totRocket = 0;
	static boolean[][] sentRocket = new boolean[50][50];
	static boolean hasLaunched = false;

	// MISC
	static long startTime, mxTime = 0, totTime = 0; 

	static final int INF = 10000000;
	static Random ran = new Random();

	static boolean[][] passable = new boolean[50][50];
	static final int[] xdir = {0,1,1,0,-1,-1,-1,0,1};
	static final int[] ydir = {0,0,1,1,1,0,-1,-1,-1};
	static Direction[] directions = {Direction.Center,
									 Direction.East,Direction.Northeast,Direction.North,Direction.Northwest,
									 Direction.West,Direction.Southwest,Direction.South,Direction.Southeast};
	static int[] dir = new int[9];

	// UNITS
	static VecUnit units;
	static ArrayList<Unit> UNITS = new ArrayList<>();
	static Unit[][] tmp = new Unit[50][50];    
	static ArrayList<Unit> closestWorkers = new ArrayList<>();
	static Map<Integer, Boolean> knightRushing = new HashMap<>();
	static int co = 0, killMode = 0, lastSeen = 0;
	static int worker = 0, attack = 0, ranger = 0, healer = 0, factory = 0, knight = 0, mage = 0;
	static int[] cattack = new int[2500];
	static int MAXLIMIT, rushRounds = 0;
	static boolean mageSeen = false;
	static boolean enemySeen = false;

	static int[] minFac = new int[2501], fac = new int[2501];
	static int[] minWork = new int[2501], work = new int[2501];
	static int[] totKarb = new int[2501];

	// KARBONITE
	static Set<Integer> hasNearbyMage;
	static boolean[][] bad = new boolean[50][50];
	static int[][] karboniteCount = new int[50][50]; // keep it like this!
	static Direction[][] bfsFrom = new Direction[50][50];
	static boolean coolvariable;
	static int workerCost = 0;
	static Map<Integer,Integer> lastCollect = new HashMap<>();
	static int[] collectedKarbonite = new int[1001];
	
	static int getCollectedKarbonite(int l, int r) { // get total worker profit from rounds l..r
		int ans = 0;
		if (l <= 0) {
			ans -= 20*l;
			l = 1;
		}
		for (int i = l; i <= r; i++) ans += collectedKarbonite[i];
		return ans;
	}

	static pii[][] closeFriendGround = new pii[50][50];
	static pii[][] damageFriend = new pii[50][50];
	static int[][] distDamageFriend = new int[50][50];
	static pii[][] nearbyHealer = new pii[50][50];
	
	static int[][][][] distGround = new int[50][50][50][50]; 
	
	static int getDistGround(pii A, pii B) {
		if(A == null || B == null) return INF;
		return distGround[B.f][B.s][A.f][A.s];
	}
	static int getDistGround(Unit A, Unit B) {
		return getDistGround(toPii(A),toPii(B));
	}

	// COMPONENTS
	static int totsz = 0;
	static int[][] comp = new int[50][50]; 
	static int[][] compO = new int[50][50]; 
	static int maxAtk; // component with most attackers
	static int[] sz = new int[2501], cNum = new int[2501];
	static boolean[] ok = new boolean[2501];
	
	static void genComp(int X, int Y, int num) {
		if (!fastGC.onBoard(X,Y) || comp[X][Y] != 0
			|| C.isPassableTerrainAt(new MapLocation(cPlanet,X,Y)) == 0) return;
		comp[X][Y] = num;
		for (int i = 1; i < 9; ++i) genComp(X+xdir[i],Y+ydir[i],num);
	}  
	
	static void genCompO(int X, int Y, int num) {
		if (!fastGC.onBoardO(X,Y) || compO[X][Y] != 0
			|| O.isPassableTerrainAt(new MapLocation(oPlanet,X,Y)) == 0) return;
		compO[X][Y] = num;
		for (int i = 1; i < 9; ++i) genCompO(X+xdir[i],Y+ydir[i],num);
	}  
	
	static int comp(Unit U) {
		MapLocation M = mapLoc(U);
		return comp[M.getX()][M.getY()];
	}

	// ENEMIES
	static int[][] lastSense = new int[50][50];
	static pii[][] closeLastSense = new pii[50][50];
	
	static ArrayList<pii> cFac = new ArrayList<>(), oFac = new ArrayList<>(); 
	static void genOpposingFac() { // store / update opponent's factories
		ArrayList<pii> A = new ArrayList<>(oFac); oFac.clear();
		for (pii M: A) if (lastSense[M.f][M.s] != cRound) oFac.add(M);
		for (int i = 0; i < units.size(); ++i) 
			if (units.get(i).team() == oteam && fastGC.isStructure(units.get(i)))
				oFac.add(toPii(units.get(i)));
	}

	static int[][] distCloseEnemyGround = new int[50][50];
	static pii[][] closeEnemyGround = new pii[50][50];
	static pii[][] closeEnemyEuclid = new pii[50][50];

	static boolean existsEnemy(Unit U, int r) {
		pii u = get(U,closeEnemyEuclid);
		if (u != null && u.distanceSquaredTo(toPii(U)) <= r*r) return true;
		return false;
	}

	// STRUCTURES
	static MapLocation nextDestination;
	static pii[][] closeRocket = new pii[50][50];
	static boolean yourRocket(Unit U) {
		if (U == null) return false;
		return U.unitType() == UnitType.Rocket && U.team() == cteam && U.structureIsBuilt() == 1;
	} 
	
	static pii[][] closeDamageStructure = new pii[50][50];
	static pii[][] closeStructure = new pii[50][50];
	

	// HELPER

	static pii get(Unit U, pii[][] arr) {
		pii cloc = toPii(U);
		return arr[cloc.f][cloc.s];
	}

	static Unit GET(Unit U, pii[][] arr) {
		pii cloc = get(U,arr);
		if (cloc == null) return null;
		return tmp[cloc.f][cloc.s];
	}

	static boolean good(MapLocation M) {
		int t = M.getX()+M.getY();
		if (t % 2 == 0) return true;
		return false;
	}

	static MapLocation mapLoc(Unit U) { // convert unit to mapLoc
		if (U == null) return null;
		Location L = U.location();
		if (!L.isOnMap()) return null;
		return L.mapLocation();
	}

	static void shuffleArray(int[] ar) {
		for (int i = ar.length - 1; i > 0; i--) {
			int index = ran.nextInt(i + 1);
			int a = ar[index];
			ar[index] = ar[i];
			ar[i] = a;
		}
	}

	static pii toPii(Unit U) {
		MapLocation cloc = mapLoc(U);
		if (cloc == null) return null;
		return new pii (cloc.getX(),cloc.getY());
	}
	
	static int opposite(int x) {
		return x <= 4 ? x+4 : x-4;
	}
	
	static boolean notCloseWorker(int x, int y) {
		for (int i = x-1; i <= x+1; ++i)
			for (int j = y-1; j <= y+1; ++j)
				if (fastGC.onBoard(i,j) && fastGC.your(tmp[i][j],UnitType.Worker))
					return false;
		return true;
	}
}
