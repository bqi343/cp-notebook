package bc19;

import java.util.*;
import java.math.*;

import static bc19.Consts.*;

public class MyRobot extends BCAbstractRobot {
  // note: arrays are by y and then x

  // ROBOTS
  Robot2 ORI, CUR;
  Robot2[] robots;
  pi[] lastPos = new pi[4097];
  int[] hits = new int[4097];
  Robot2[][] robotMap; // stores last robot seen in pos
  int[][] robotMapID, lastTurn; // stores last id seen in pos, last turn seen

  ArrayList<Integer> myCastle = new ArrayList<>(), otherCastle = new ArrayList<>();
  ArrayList<Integer> myChurch = new ArrayList<>(), otherChurch = new ArrayList<>();
  ArrayList<Integer> myStructID = new ArrayList<>(), myCastleID = new ArrayList<>();

  // MAP
  ArrayList<pi> dirs;
  int w, h; // width, height
  boolean wsim, hsim;
  bfsMap bfs; // bfsShort;

  // ALL UNITS
  int lastHealth, castle_talk, lastPatrol, endPosAssigned = MOD, endPos = MOD, lastAction, lastSecretAttack = -MOD;
  pi nextSignal;
  pi[] posRecord = new pi[1001];
  unitCounter U;
  int totResource, lastSpam = -MOD;

  // MOVABLE
  boolean goHome;
  boolean producedByCastle;

  // NOT PILGRIM
  boolean updEnemy = true, seenEnemy = false;
  int[][][] enemyDist;

  // ATTACKERS
  boolean waited, avoidCastle, attackMode; // avoidCastle = if castle is too crowded don't patrol next to it
  int atFront = 0; // set to 100 when see an ally die nearby, decrement every turn until reach 0
  ArrayList<Integer> nearbyAllies = new ArrayList<>(); // keeps track of allies in 5x5 square to determine when they die
  int posLastTurn = MOD;

  // CASTLE
  boolean canRush = false, shouldSave = false;
  int originalCastles;
  int FUEL_RATIO = 100;
  int[] type = new int[4097];
  int lastSignalAttack, lastAttack, numAttacks;

  int karbcount, fuelcount;
  int[] sortedKarb, sortedFuel, pilToKarb, pilToFuel, karbPos, fuelPos;
  boolean[] badResource = new boolean[4096];
  Map<Integer,Integer> castleX = new HashMap<>(), castleY = new HashMap<>();
  pi assignedPilgrimPos, escortPos;
  boolean[][] sentEscort = new boolean[64][64];
  boolean[][] assigned;
  int myPilgrim = 0;

  // BUILDING
  int patrolcount;
  int[] atkToPatrol, patrolPos, atkToPatrolPrev;
  int[][] badPatrol; // if positive, don't patrol here
  int assignedAttackerPos = -1;
  int enex=-1, eney=-1;
  double besx = -1, besy = -1;
  double[] patrolscore = new double[4097];

  // PILGRIM
  int sparseGoal = MOD;
  int[][] danger; safeMap safe;
  int resource = -1; // karbonite or fuel
  pi resourceLoc;
  boolean giveup = false;

  // SUPER SECRET STRATEGY
  boolean continuedChain = false, isSuperSecret = false, signaledSuccessfulAttack = false;
  // has this pilgrim/church already built the next one in line?
  // is this unit part of the super secret strategy?
  Set<Integer> seenSuccesses = new HashSet<Integer>();
  int numSuccessfulAttacks = 0;

  int destination;
  secretMap sm;

  // END SPAM
  Action2 build;
  boolean shouldSpam = false;

  void sortClose(ArrayList<pi> dirs) {
    Collections.sort(dirs, new Comparator<pi>() {
      public int compare(pi a, pi b) {
        return a.norm()-b.norm();
      }
    });
  }
  int getVal(pi x) {
    int val = 10*(Math.abs(x.f)+Math.abs(x.s));
    if (x.f != 0 && x.s != 0) val ++;
    return val;
  }
  void sortMove(ArrayList<pi> dirs) {
    Collections.sort(dirs, new Comparator<pi>() {
      public int compare(pi a, pi b) {
        return getVal(b)-getVal(a);
      }
    });
  }

  boolean genhsim() { // symmetric with respect to y
    for (int i = 0; i < h-1-i; ++i)
    for (int j = 0; j < w; ++j) {
      if (map[i][j] != map[h-1-i][j]) return false;
      if (karboniteMap[i][j] != karboniteMap[h-1-i][j]) return false;
      if (fuelMap[i][j] != fuelMap[h-1-i][j]) return false;
    }
    return true;
  }
  boolean genwsim() { // symmetric with respect to x
    for (int i = 0; i < h; ++i)
    for (int j = 0; j < w-1-j; ++j) {
      if (map[i][j] != map[i][w-1-j]) return false;
      if (karboniteMap[i][j] != karboniteMap[i][w-1-j]) return false;
      if (fuelMap[i][j] != fuelMap[i][w-1-j]) return false;
    }
    return true;
  }

  void initVars() {
    // if (me.unit == CASTLE) canRush = true;
    if (dirs == null) {
      // log("HI");
      dirs = new ArrayList<>();
      for (int dx = -3; dx <= 3; ++dx) for (int dy = -3; dy <= 3; ++dy)
      if (dx*dx + dy*dy <= 9) dirs.add(new pi(dx,dy));
      sortMove(dirs);

      w = map[0].length; h = map.length;
      wsim = genwsim(); hsim = genhsim();
      totResource = 0;
      for (int i = 0; i < h; ++i) for (int j = 0; j < w; ++j)
        if (karboniteMap[i][j] || fuelMap[i][j])
          totResource ++;

      robotMap = new Robot2[h][w]; robotMapID = new int[h][w];
      for (int i = 0; i < h; ++i) for (int j = 0; j < w; ++j)
        robotMapID[i][j] = -1;

      if (me.unit == CRUSADER) bfs = new bfsMap(this,9);
      else bfs = new bfsMap(this,4);

      lastTurn = new int[h][w];
      for (int i = 0; i < h; ++i) for (int j = 0; j < w; ++j) lastTurn[i][j] = -MOD;

      if (me.unit == PILGRIM) {
        danger = new int[h][w];
        safe = new safeMap(this,4);
      }
    }
  }

  // MATH
  int fdiv(int a, int b) { return (a-(a%b))/b; }
  int sq(int x) { return x*x; }
  double sq(double x) { return x*x; }
  String coordinates(int t) {
    if (t == MOD) return "(??)";
    int y = t%64, x = fdiv(t,64);
    return "("+x+", "+y+")";
  }

  // ACTION
  Action2 moveAction(int dx, int dy) {
    Action2 A = new Action2();
    A.type = 0; A.dx = dx; A.dy = dy;
    return A;
  }
  Action2 mineAction() {
    Action2 A = new Action2();
    A.type = 1;
    return A;
  }
  Action2 giveAction(int dx, int dy, int karb, int fuel) {
    Action2 A = new Action2();
    A.type = 2; A.dx = dx; A.dy = dy; A.karb = karb; A.fuel = fuel;
    return A;
  }
  Action2 attackAction(int dx, int dy) {
    Action2 A = new Action2();
    A.type = 3; A.dx = dx; A.dy = dy;
    return A;
  }
  Action2 buildAction(int unit, int dx, int dy) {
    Action2 A = new Action2();
    A.type = 4; A.unit = unit; A.dx = dx; A.dy = dy;
    return A;
  }
  Action conv(Action2 A) {
    if (A == null || A.type < 0) return null;
    if (A.type == 0 && A.dx == 0 && A.dy == 0) return null;
    if (A.type == 0) return move(A.dx,A.dy);
    if (A.type == 1) return mine();
    if (A.type == 2) return give(A.dx,A.dy,A.karb,A.fuel);
    if (A.type == 3) return attack(A.dx,A.dy);
    if (A.type == 4) return buildUnit(A.unit,A.dx,A.dy);
    return null;
  }

  // ROBOT
  Robot2 makeRobot(int unit, int team, int x, int y) {
    Robot2 R = new Robot2(null);
    R.id = MOD; R.unit = unit; R.team = team; R.x = x; R.y = y;
    return R;
  }
  Robot2 makeRobot(int id, int unit, int team, int x, int y) {
    Robot2 R = makeRobot(unit,team,x,y); R.id = id;
    return R;
  }
  Robot2 getRobot2(int id) { return new Robot2(getRobot(id)); }
  void dumpRobots() { String T = ""; for (Robot2 R: robots) T += R.getInfo(); log(T); }

  // ARRAYLIST
  void removeDup(ArrayList<Integer> A) {
    ArrayList<Integer> B = new ArrayList<>();
    for (Integer i : A) if (!B.contains(i)) B.add(i);
    A.clear(); for (Integer i : B) A.add(i);
  }
  int min(ArrayList<Integer> A) {
    int res = MOD; for (int i: A) res = Math.min(res,i);
    return res;
  }
  String toString(ArrayList<Integer> A) {
    String res = "{";
    for (int i = 0; i < A.size(); ++i) {
      res += coordinates(A.get(i));
      if (i != A.size()-1) res += ", ";
    }
    res += "}";
    return res;
  }

  // EUCLID DIST
  int euclidDist(int x1, int y1, int x2, int y2) {
    if (x1 == -1 || x2 == -1) return MOD;
    return sq(x1-x2) + sq(y1-y2);
  }
  int euclidDist(Robot2 A, int x, int y) { return A == null ? MOD : euclidDist(A.x,A.y,x,y); }
  int euclidDist(Robot2 A, Robot2 B) {
    if (A == null || B == null) return MOD;
    return euclidDist(A.x,A.y,B.x,B.y);
  }
  int euclidDist(Robot2 A) { return euclidDist(CUR,A); }
  int euclidDist(int x, int y) { return euclidDist(CUR,x,y); }
  int euclidDist(int x) { return x == MOD ? MOD : euclidDist(fdiv(x,64),x%64); }
  double realdis(double x1, double y1, double x2, double y2) { return Math.sqrt(sq(x1-x2)+sq(y1-y2)); }
  double realdis(int pos1, int pos2) { return Math.sqrt(euclidDist(pos1,pos2)); }
  boolean adjacent(Robot2 A, Robot2 B) {
    int e = euclidDist(A,B);
    return e > 0 && e <= 2;
  }
  boolean inVisionRange(Robot2 A, Robot2 B) {
    if (A == null || A.unit == -1) return false;
    return euclidDist(A,B) <= VISION_R[A.unit];
  }
  boolean inVisionRange(int x, int y) { return euclidDist(CUR,x,y) <= VISION_R[CUR.unit]; }
  boolean inVisionRange(int pos) { return inVisionRange(fdiv(pos,64), pos%64); }

  // DEBUG
  void dumpCastles() {
    log(CUR.getInfo()+" "+myCastle.size()+" "+otherCastle.size()+"\n"+toString(myCastle));
  }
  void dumpInfo() {
    String T = CUR.getInfo();
    T += myCastle.size()+" "+otherCastle.size();
    if (otherCastle.size() > 0) T += " " + coordinates(otherCastle.get(0));
    T += "\n";
    log(T);
  }

  // MAP
  boolean inMap(int x, int y) { return x >= 0 && x < w && y >= 0 && y < h; }
  boolean valid(int x, int y) { return inMap(x,y) && map[y][x]; }
  boolean containsResource(int x, int y) { return valid(x,y) && (karboniteMap[y][x] || fuelMap[y][x]); }
  boolean passable(int x, int y) { return valid(x, y) && (robotMapID[y][x] <= 0 || robotMapID[y][x] == MOD); }
  boolean containsRobot(int x, int y) { return valid(x, y) && robotMapID[y][x] > 0; }
  boolean containsRobot(int pos) { return containsRobot(fdiv(pos,64), pos%64); }
  boolean containsStruct(int x, int y) { return containsRobot(x, y) && IS_STRUCT[robotMap[y][x].unit]; }
  boolean adjStruct(int x, int y) {
    for(int dx = -1; dx <= 1; dx++) {
      for(int dy = -1; dy <= 1; dy++) {
        if(containsStruct(x+dx,y+dy)) return true;
      }
    }
    return false;
  }

  boolean teamRobot(int x, int y, int t) { return containsRobot(x,y) && robotMap[y][x].team == t; }
  boolean yourRobot(int x, int y) { return teamRobot(x,y,CUR.team); }
  boolean yourStruct(int x, int y) { return yourRobot(x,y) && robotMap[y][x].unit <= 1; }
  boolean enemyRobot(int x, int y) { return teamRobot(x,y,1-CUR.team); }
  boolean enemyRobot(int x, int y, int t) { return teamRobot(x,y,1-CUR.team) && robotMap[y][x].unit == t; }
  boolean enemyStruct(int x, int y) { return enemyRobot(x,y) && robotMap[y][x].unit <= 1; }
  boolean enemyStruct(Robot2 R) { return R != null && R.team == 1-CUR.team && R.isStructure(); }

  boolean attacker(int x, int y) { return containsRobot(x,y) && CAN_ATTACK[robotMap[y][x].unit]; }
  boolean teamAttacker(int x, int y, int t) { return attacker(x,y) && teamRobot(x,y,t);  }
  boolean yourAttacker(int x, int y) { return teamAttacker(x,y,CUR.team); }
  boolean enemyAttacker(int x, int y) { return teamAttacker(x,y,1-CUR.team); }

  boolean adjEnemyPreacher(int x, int y) {
    for (int i = -1; i <= 1; ++i) for (int j = -1; j <= 1; ++j)
    if (enemyRobot(x+i,y+j,PREACHER)) return true;
    return false;
  }
  boolean adjEnemyCastle(Robot2 P) {
    int x = P.x, y = P.y;
    for (int i = -1; i <= 1; ++i) for (int j = -1; j <= 1; ++j)
    if (enemyRobot(x+i,y+j,CASTLE)) return true;
    return false;
  }
  boolean seeEnemyStruct() {
    for (int i = -10; i <= 10; ++i) for (int j = -10; j <= 10; ++j)
    if (i*i+j*j <= VISION_R[CUR.unit] && enemyStruct(CUR.x+i,CUR.y+j))
    return true;
    return false;
  }
  boolean containsEnemy(int x, int y) {
    for (int i = -1; i <= 1; ++i) for (int j = -1; j <= 1; ++j)
    if (enemyRobot(x+i,y+j)) return true;
    return false;
  }

  int numOpen (int x, int y) { // how many squares around t are free
    int ret = 0;
    for (int i = x-1; i <= x+1; ++i) for (int j = y-1; j <= y+1; ++j)
    if (passable(i,j)) ret ++;
    return ret;
  }
  int numOpen(int t) { return numOpen(fdiv(t,64),t%64); }
  int dangerRadius(Robot2 R) {
    return 64;
  }
  int lastDanger(int x, int y) {
    int ret = -MOD;
    for (int i = y-10; i <= y+10; ++i) for (int j = x-10; j <= x+10; ++j)
    if (teamAttacker(j,i,1-CUR.team)) {
      Robot2 R = robotMap[i][j];
      if (euclidDist(R,j,i) <= dangerRadius(R))
      ret = Math.max(ret,lastTurn[i][j]);
    }
    return ret;
  }
  Robot2 closestRobot(Robot2 R, int t) {
    Robot2 bes = null;
    for (int i = 0; i < h; ++i) for (int j = 0; j < w; ++j)
    if (teamRobot(j,i,t) && euclidDist(R,j,i) < euclidDist(R,bes))
    bes = robotMap[i][j];
    return bes;
  }
  Robot2 closestAttacker(Robot2 R, int t) {
    Robot2 bes = null;
    for (int i = 0; i < h; ++i) for (int j = 0; j < w; ++j)
    if (teamAttacker(j,i,t) && euclidDist(R,j,i) < euclidDist(R,bes) && lastTurn[i][j] >= CUR.turn-5)
    bes = robotMap[i][j];
    return bes;
  }
  Robot2 closestNotPilgrim(Robot2 R, int t) {
    Robot2 bes = null;
    for (int i = 0; i < h; ++i) for (int j = 0; j < w; ++j)
    if (teamRobot(j,i,t) && euclidDist(R,j,i) < euclidDist(R,bes) && lastTurn[i][j] >= CUR.turn-5 && robotMap[i][j].unit != PILGRIM)
    bes = robotMap[i][j];
    return bes;
  }
  int closestEuclid(ArrayList<Integer> A) {
    int bestDist = MOD, bestPos = MOD; if (A == null) return bestPos;
    for (int x : A) {
      int d = euclidDist(x);
      if (d < bestDist) { bestDist = d; bestPos = x; }
    }
    return bestPos;
  }

  boolean yesStruct(int x, int y) {
    if (!valid(x,y) || robotMapID[y][x] == 0) return false;
    if (robotMapID[y][x] > 0 && !robotMap[y][x].isStructure()) return false;
    return true;
  }
  void addYour(ArrayList<Integer> A, Robot2 R) {
    int p = 64*R.x+R.y;
    if (!yesStruct(R.x,R.y)) return;
    if (R.id != MOD && !myStructID.contains(R.id)) myStructID.add(R.id);
    if (R.unit == CASTLE && R.id != MOD && !myCastleID.contains(R.id)) myCastleID.add(R.id);
    if (A.contains(p)) return;
    if (CUR.unit == CASTLE && R.unit == CASTLE)
    for (int i = 0; i < h; ++i) for (int j = 0; j < w; ++j)
    if (euclidDist(j,i) > euclidDist(R,j,i)) badResource[64*j+i] = true;
    A.add(p);
    if (robotMapID[R.y][R.x] == -1) { robotMapID[R.y][R.x] = R.id; robotMap[R.y][R.x] = R; }
  }
  void addOther(ArrayList<Integer> A, Robot2 R) {
    int p = 64*R.x+R.y;
    if (!yesStruct(R.x,R.y) || A.contains(p)) return;
    if (CUR.unit == CASTLE && R.unit == CASTLE)
    for (int i = 0; i < h; ++i) for (int j = 0; j < w; ++j)
    if (euclidDist(j,i) > euclidDist(R,j,i) && euclidDist(R,j,i) <= 100) badResource[64*j+i] = true;
    A.add(p); updEnemy = true;
    if (robotMapID[R.y][R.x] == -1) { robotMapID[R.y][R.x] = R.id; robotMap[R.y][R.x] = R; }
  }
  void rem(ArrayList<Integer> A) {
    ArrayList<Integer> B = new ArrayList<>();
    for (int i : A) {
      int x = fdiv(i,64), y = i%64;
      if (yesStruct(x,y)) B.add(i);
      else if (A == otherCastle || A == otherChurch) updEnemy = true;
    }
    A.clear();
    for (int i : B) A.add(i);
  }
  void addStruct(Robot2 R) {
    if (!yesStruct(R.x,R.y)) return;
    //log("OOPS "+R.getInfo());
    if (R.unit == CHURCH) {
      if (R.team == CUR.team) addYour(myChurch,R);
      else if (R.team != CUR.team) addOther(otherChurch,R);
    } else {
      if (R.team == CUR.team) {
        addYour(myCastle,R);
        if (wsim) addOther(otherCastle,makeRobot(0,1-CUR.team,w-1-R.x,R.y));
        if (hsim) addOther(otherCastle,makeRobot(0,1-CUR.team,R.x,h-1-R.y));
      } else if(R.team != CUR.team) {
        addOther(otherCastle,R);
        if (wsim) addYour(myCastle,makeRobot(0,CUR.team,w-1-R.x,R.y));
        if (hsim) addYour(myCastle,makeRobot(0,CUR.team,R.x,h-1-R.y));
      }
    }
  }

  int surround(int dest) {
    int x = fdiv(dest,64), y = dest%64;
    int ret = 0;
    for (int i = x-3; i <= x+3; ++i) for (int j = y-3; j <= y+3; ++j)
    if (!valid(i,j)) ret ++;
    return ret;
  }

  // BFS DIST
  void genDanger() {
    // round 20: 5
    // round 1000: 60
    // 5+round/20
    int dangerRound = CUR.turn-(5+CUR.turn/20);
    for (int i = 0; i < h; ++i) for (int j = 0; j < w; ++j) danger[i][j] = 0;
    for (int i = 0; i < h; ++i) for (int j = 0; j < w; ++j) if (lastTurn[i][j] >= dangerRound) {
      if (enemyAttacker(j,i)) {
        Robot2 R = robotMap[i][j];
        int d = dangerRadius(R);
        for (int I = -10; I <= 10; ++I) for (int J = -10; J <= 10; ++J) {
          int D = I*I+J*J;
          if (D <= d && inMap(j+J,i+I)) {
            int tmp = MAX_ATTACK_R[R.unit];
            if (R.unit == PREACHER) tmp = 49;
            if (D <= tmp) danger[i+I][j+J] = 2;
            else danger[i+I][j+J] = Math.max(danger[i+I][j+J],1);
          }
        }
      } else if (teamRobot(j,i,1-CUR.team) && robotMap[i][j].isStructure()) {
        for (int I = -1; I <= 1; ++I) for (int J = -1; J <= 1; ++J) if (inMap(j+J,i+I)) {
          // log("STRUCT "+(j+J)+" "+(i+I));
          danger[i+I][j+J] = 2;
        }
      }
    }

    for (int i = 0; i < h; ++i) for (int j = 0; j < w; ++j) if (lastTurn[i][j] >= dangerRound)
    if (yourAttacker(j,i)) {
      for (int I = -4; I <= 4; ++I) for (int J = -4; J <= 4; ++J) {
        int D = I*I+J*J;
        if (D <= 16 && inMap(j+J,i+I) && danger[i+I][j+J] == 1)
        danger[i+I][j+J] = 0;
      }
    }

    safe.upd();
  }
  void genEnemyDist() {
    if (enemyDist == null) {
      enemyDist = new int[h][w][2];
      for (int i = 0; i < h; ++i) for (int j = 0; j < w; ++j)
      for (int k = 0; k < 2; ++k) enemyDist[i][j][k] = MOD;
    }
    if (!updEnemy) return;
    updEnemy = false;
    LinkedList<Integer> Q = new LinkedList<Integer>();
    for (int i = 0; i < h; ++i) for (int j = 0; j < w; ++j)
    for (int k = 0; k < 2; ++k) enemyDist[i][j][k] = MOD;
    for (int i: otherCastle) {
      Q.add(2*i);
      enemyDist[i%64][fdiv(i,64)][0] = 0;
    }
    for (int i: otherChurch) {
      Q.add(2*i);
      enemyDist[i%64][fdiv(i,64)][0] = 0;
    }
    while (Q.size() > 0) {
      int t = Q.poll();
      int k = t % 2; t = fdiv(t,2);
      int x = fdiv(t,64), y = t % 64;
      for (int z = 0; z < 4; ++z) {
        int X = x+DX_EDGE_ONLY[z], Y = y+DY_EDGE_ONLY[z];
        if (inMap(X,Y)) {
          int K = k+1; if (map[Y][X]) K = 0;
          if (K == 2 || enemyDist[Y][X][K] != MOD) continue;
          enemyDist[Y][X][K] = enemyDist[y][x][k]+1;
          Q.push(2*(64*X+Y)+K);
        }
      }
    }
  }
  int closestOurSide(boolean[][] B) { // prioritize all locations on our side first
    if(B == null) return MOD;
    if (hsim) {
      // check our side
      int bestPos = MOD, bestDist = MOD;
      int mid = fdiv(h,2);
      if(CUR.y >= mid) {
        for(int x = 0; x < w; x++) for(int y = mid; y < h; y++) {
          if(B[y][x] && bfs.dist[y][x] < bestDist && robotMapID[y][x] <= 0) {
            bestDist = bfs.dist[y][x]; bestPos = 64*x+y;
          }
        }
      } else {
        for(int x = 0; x < w; x++) for(int y = 0; y < mid; y++) {
          if(B[y][x] && bfs.dist[y][x] < bestDist && robotMapID[y][x] <= 0) {
            bestDist = bfs.dist[y][x]; bestPos = 64*x+y;
          }
        }
      }
      if(bestPos != MOD) return bestPos;
      // check other side
      if(CUR.y >= mid) {
        for(int x = 0; x < w; x++) for(int y = 0; y < mid; y++) {
          if(B[y][x] && bfs.dist[y][x] < bestDist && robotMapID[y][x] <= 0) {
            bestDist = bfs.dist[y][x]; bestPos = 64*x+y;
          }
        }
      } else {
        for(int x = 0; x < w; x++) for(int y = mid; y < h; y++) {
          if(B[y][x] && bfs.dist[y][x] < bestDist && robotMapID[y][x] <= 0) {
            bestDist = bfs.dist[y][x]; bestPos = 64*x+y;
          }
        }
      }
      return bestPos;
    } else {
      // check our side
      int bestPos = MOD, bestDist = MOD;
      int mid = fdiv(w,2);
      if(CUR.x >= mid) {
        for(int x = mid; x < w; x++) for(int y = 0; y < h; y++) {
          if(B[y][x] && bfs.dist[y][x] < bestDist && robotMapID[y][x] <= 0) {
            bestDist = bfs.dist[y][x]; bestPos = 64*x+y;
          }
        }
      } else {
        for(int x = 0; x < mid; x++) for(int y = 0; y < h; y++) {
          if(B[y][x] && bfs.dist[y][x] < bestDist && robotMapID[y][x] <= 0) {
            bestDist = bfs.dist[y][x]; bestPos = 64*x+y;
          }
        }
      }
      if(bestPos != MOD) return bestPos;
      // check other side
      if(CUR.x >= mid) {
        for(int x = 0; x < mid; x++) for(int y = 0; y < h; y++) {
          if(B[y][x] && bfs.dist[y][x] < bestDist && robotMapID[y][x] <= 0) {
            bestDist = bfs.dist[y][x]; bestPos = 64*x+y;
          }
        }
      } else {
        for(int x = mid; x < w; x++) for(int y = 0; y < h; y++) {
          if(B[y][x] && bfs.dist[y][x] < bestDist && robotMapID[y][x] <= 0) {
            bestDist = bfs.dist[y][x]; bestPos = 64*x+y;
          }
        }
      }
      return bestPos;
    }
  }

  boolean canMove(Robot2 R, int dx, int dy) {
    if (R == null || R.unit == -1) return false;
    // if (dx == 0 && dy == 0) return false;
    int u = R.unit, d = dx*dx+dy*dy;
    return passable(R.x+dx,R.y+dy) && d <= MOVE_SPEED[u] && d*MOVE_F_COST[u] <= fuel;
  }

  // CASTLE LOCATIONS / ATTACK
  boolean isAttacking(int c) { return c == 8 || c == 9; }
  boolean seesEnemy(int c) { return c == 7 || c == 9; }
  int farthestDefenderRadius() {
    int t = 0;
    for (int x = 0; x < w; ++x) for (int y = 0; y < h; ++y) {
      if (yourAttacker(x,y)) {
        Robot2 R = robotMap[y][x];
        if (!isAttacking(R.castle_talk)) t = Math.max(t,euclidDist(64*x+y));
      }
    }
    return t;
  }
  /*void startAttack() {
    if (CUR.unit != CASTLE) return;
    for (Robot2 R: robots)
    if (R.team == CUR.team && R.unit == CASTLE && R.castle_talk == 255)
    lastAttack = CUR.turn;
    if (nextSignal != null || lastSignalAttack >= CUR.turn-10) return;
    if (U.shouldBeginAttack()) { // (CUR.team == 0 && attackMode))
      int r = 8192;
      if (r > 0 && fuel >= Math.ceil(Math.sqrt(r))) {
        lastSignalAttack = CUR.turn;
        //log("SIGNAL ATTACK "+CUR.x+" "+CUR.y+" "+r+" "+fuel+" "+U.closeAttackers());
        numAttacks ++;
        nextSignal = new pi(encodeCastleLocations(),r); castle_talk = 255;
      }
    }
  }*/

  void startEconSpam() {
    if (CUR.unit != CASTLE) return;
    if (CUR.turn != 989) return;
    int r = w*w+h*h-7;
    if (r <= fuel*fuel && CUR.id == min(myCastleID)) {
      nextSignal = new pi(25432, r);
      log("START ECON SPAM");
    }
  }

  int compress(int i) {
    int x = fdiv(i, 64), y = i % 64;
    x = fdiv(x, 4); y = fdiv(y, 4);// approximating location
    return 16*x+y;
  }
  int encodeCastleLocations() {
    int key = 0;
    for(int x = 0; x < w; x++) for(int y = 0; y < h; y++) {
      if(containsResource(x,y)) key += 7;
      else if(valid(x,y)) key += 3;
    }
    key %= 50;

    int myLoc = compress(64*CUR.x+CUR.y);

    int ret = (myLoc * 50) + key + 7000;
    return ret;
  }
  void fill4by4(int approxX, int approxY) {
    // log("FILL "+approxX+" "+approxY);
    for (int i = 0; i < 4; i++) for (int j = 0; j < 4; j++) {
      int x = 16 * approxX + i;
      int y = 16 * approxY + j;
      addStruct(makeRobot(0,CUR.team,x,y));
    }
  }
  void decodeCastleLocations(int sig) {
    sig -= 7000;
    int key = 0;
    for(int x = 0; x < w; x++) for(int y = 0; y < h; y++) {
      if(containsResource(x,y)) key += 7;
      else if(valid(x,y)) key += 3;
    }
    key %= 50;

    if((sig%50) != key) return;

    sig -= key;
    sig /= 50;

    fill4by4(fdiv(sig,16),sig%16);
  }

  // ATTACK DAMAGE
  double attackPriority(Robot2 R) {
    if (R.unit == CASTLE) return 50;
    if (R.unit == PREACHER) return 20;
    if (R.unit == PROPHET) return 18;
    if (R.unit == CRUSADER) return 14;
    if (R.unit == PILGRIM) return 10;
    return 8;
  }
  boolean inAttackRange(Robot2 R, int x, int y) { // can R attack (x,y)?
    int d = euclidDist(R,x,y);
    int mn = MIN_ATTACK_R[R.unit]; if (R.unit == PREACHER) mn = 3;
    return d >= mn && d <= MAX_ATTACK_R[R.unit];
  }
  boolean isAttacked(int x, int y) {
    for (int i = -8; i <= 8; ++i) for (int j = -8; j <= 8; ++j) {
      int X = x+i, Y = y+j;
      if (teamAttacker(X,Y,1-CUR.team) && inAttackRange(robotMap[Y][X],x,y))
      return true;
    }
    return false;
  }
  double preacherVal(Robot2 P, int x, int y) {
    if (!valid(x,y) || euclidDist(P,x,y) < 3) return 0;

    double t = 0;
    for (int i = x-1; i <= x+1; ++i) for (int j = y-1; j <= y+1; ++j)
    if (containsRobot(i,j)) {
      Robot2 R = robotMap[j][i];
      double val = attackPriority(R);
      if (lastTurn[j][i] < CUR.turn-1) val /= 5;
      if (R.team == P.team) val *= -3;
      if (R.isStructure()) val *= 5;
      //if (R.unit == CASTLE && lastTurn[j][i] >= CUR.turn-1) val *= 10;
      t += val;
    }

    return t;
  }
  double preacherDanger(Robot2 P) {
    double res = 0;
    for (int i = -4; i <= 4; ++i) for (int j = -4; j <= 4; ++j) if (i*i+j*j <= 16)
    res = Math.max(res,preacherVal(P,P.x+i,P.y+j));
    if (adjEnemyCastle(P)) res -= 50;
    return res;
  }
  double maxPreacherVal(Robot2 P, int x, int y) { // P is the preacher
    double tot = 0;
    for (int X = x-1; X <= x+1; ++X) for (int Y = y-1; Y <= y+1; ++Y)
    if (inAttackRange(P,X,Y)) tot = Math.max(tot,preacherVal(P,X,Y));
    return tot;
  }
  double totPreacherDamage(int x, int y) {
    double res = 0;
    for (int i = x-5; i <= x+5; ++i) for (int j = y-5; j <= y+5; ++j)
    if (enemyRobot(i,j,PREACHER))
    res += maxPreacherVal(robotMap[j][i],x,y);
    return res;
  }
  double totDamage(int x, int y) { // sum of damage of all enemy units that can attack this position
    double res = totPreacherDamage(x,y);
    for (int i = -8; i <= 8; ++i) for (int j = -8; j <= 8; ++j)
    if (enemyAttacker(x+i,y+j)) {
      Robot2 R = robotMap[y+j][x+i];
      if (R.unit == 5) continue;
      if (inAttackRange(R,x,y)) res += DAMAGE[R.unit];
    }
    return res;
  }
  double totPreacherDamageAfter(int x, int y) {
    robotMapID[CUR.y][CUR.x] = 0; robotMap[CUR.y][CUR.x] = null;
    CUR.x = x; CUR.y = y;
    robotMapID[CUR.y][CUR.x] = CUR.id; robotMap[CUR.y][CUR.x] = CUR;

    double t = totPreacherDamage(x,y);

    robotMapID[CUR.y][CUR.x] = 0; robotMap[CUR.y][CUR.x] = null;
    CUR.x = ORI.x; CUR.y = ORI.y;
    robotMapID[CUR.y][CUR.x] = CUR.id; robotMap[CUR.y][CUR.x] = CUR;

    return t;
  }
  double totDamageAfter(int x, int y) {
    robotMapID[CUR.y][CUR.x] = 0; robotMap[CUR.y][CUR.x] = null;
    CUR.x = x; CUR.y = y;
    robotMapID[CUR.y][CUR.x] = CUR.id; robotMap[CUR.y][CUR.x] = CUR;

    double t = totDamage(x,y);

    robotMapID[CUR.y][CUR.x] = 0; robotMap[CUR.y][CUR.x] = null;
    CUR.x = ORI.x; CUR.y = ORI.y;
    robotMapID[CUR.y][CUR.x] = CUR.id; robotMap[CUR.y][CUR.x] = CUR;

    return t;
  }

  int totEnemy(int x, int y) {
    int ret = 0;
    for (int X = x-1; X <= x+1; ++X) for (int Y = y-1; Y <= y+1; ++Y)
    if (teamRobot(X,Y,1-CUR.team)) ret ++;
    return ret;
  }
  boolean containsEnemyStruct(int x, int y) {
    for (int X = x-1; X <= x+1; ++X) for (int Y = y-1; Y <= y+1; ++Y)
    if (teamRobot(X,Y,1-CUR.team))
    if (robotMap[Y][X].isStructure()) return true;
    return false;
  }
  int mostDangerousPreacher(Robot2 R) {
    if (R == null || R.unit != CHURCH) return MOD;
    double bestVal = 0; int bestPos = MOD;
    for (int i = R.x-1; i <= R.x+1; ++i) for (int j = R.y-1; j <= R.y+1; ++j) if (passable(i,j)) {
      Robot2 P = makeRobot(PREACHER,CUR.team,i,j);
      double d = preacherDanger(P);
      if (d > bestVal) { bestVal = d; bestPos = 64*i+j; }
    }
    if (bestVal < 60) bestPos = MOD;
    return bestPos;
  }
  int activePreachers() {
    int ret = 0;
    for (int i = -10; i <= 10; ++i) for (int j = -10; j <= 10; ++j) if (i*i+j*j <= 100) {
      int x = CUR.x+i, y = CUR.y+j;
      if (teamRobot(x,y,CUR.team) && robotMap[y][x].unit == PREACHER) ret ++;
    }
    return ret;
  }
  int activeProphets() {
    int ret = 0;
    for (int i = -10; i <= 10; ++i) for (int j = -10; j <= 10; ++j) if (i*i+j*j <= 100) {
      int x = CUR.x+i, y = CUR.y+j;
      if (teamRobot(x,y,CUR.team) && robotMap[y][x].unit == PROPHET) ret ++;
    }
    return ret;
  }
  int newPreachers() {
    int ret = 0;
    for (int i = -10; i <= 10; ++i) for (int j = -10; j <= 10; ++j) if (i*i+j*j <= 100) {
      int x = CUR.x+i, y = CUR.y+j;
      if (teamRobot(x,y,CUR.team) && mostDangerousPreacher(robotMap[y][x]) != MOD) ret ++;
    }
    return ret;
  }
  int newProphets() {
    int ret = 0;
    for (int i = -10; i <= 10; ++i) for (int j = -10; j <= 10; ++j) if (i*i+j*j <= 100) {
      int x = CUR.x+i, y = CUR.y+j;
      if (teamRobot(x,y,CUR.team) &&
      robotMap[y][x].unit == CHURCH &&
      euclidDist(fdiv(destination,64),destination%64,x,y) <= 100 &&
      mostDangerousPreacher(robotMap[y][x]) != MOD)
      ret ++;
    }
    return ret;
  }
  int countNearbyChurches(int pos) {
    int x = fdiv(pos,64); int y = pos%64;
    int res = 0;

    for(int dx = -6; dx <= 6; dx++) for (int dy = -6; dy <= 6; dy++) {
      if (dx*dx + dy*dy > 40) continue;
      int x1 = x+dx; int y1 = y+dy;
      if (yourRobot(x1,y1) && robotMap[y1][x1].unit == CHURCH) res++;
    }

    return res;
  }

  // BUILD
  boolean canBuild(int t) {
    int F = CONSTRUCTION_F[t]; if (t == PILGRIM) F += 2;
    if (!(fuel >= F && karbonite >= CONSTRUCTION_K[t])) return false;
    for (int dx = -1; dx <= 1; ++dx) for (int dy = -1; dy <= 1; ++dy) {
      int x = CUR.x+dx, y = CUR.y+dy;
      if (t == CHURCH && containsResource(x,y)) continue;
      if (passable(x,y)) return true;
    }
    return false;
  }
  boolean firstHit(Robot2 R) {
    for (int i = -8; i <= 8; ++i) for (int j = -8; j <= 8; ++j) {
      int d = i*i+j*j;
      if (d >= MIN_ATTACK_R[R.unit] && d <= MAX_ATTACK_R[R.unit] && enemyRobot(R.x+i,R.y+i)) return true;
    }
    return false;
  }
  Action2 buildLeastDamage(int t) { // first minimize damage, try to build closer to enemy
    int bestVal = 2*MOD; Action2 A = null;
    for (int dx = -1; dx <= 1; ++dx) for (int dy = -1; dy <= 1; ++dy) {
      int x = CUR.x+dx, y = CUR.y+dy;
      if (passable(x,y)) {
        int val = enemyDist[y][x][0];
        val = Math.max(val,5-val);
        val += 100*totDamage(x,y);
        Robot2 R = makeRobot(t,CUR.team,x,y);
        if (firstHit(R)) val -= MOD;
        if (val < bestVal) {
          bestVal = val;
          A = buildAction(t, dx, dy);
        }
      }
    }
    return A;
  }
  boolean shouldStopChain() {
    int a = activePreachers(), n = newPreachers(), pr = newProphets();
    if (countNearbyChurches(destination) >= 10 || fuel <= 300+50*(n+pr)+15*(a+n)+25*pr || karbonite <= 30*(n+5)+25*pr) return true;
    if (euclidDist(destination) <= 36 && countNearbyChurches(destination) > Math.max(5,U.closeEnemyAttackers())) return true;
    return false;
  }
  int churchSquare(int x, int y) {
    int ret = 0;
    for (int i = x-1; i <= x+1; ++i) for (int j = y-1; j <= y+1; ++j)
    if (teamRobot(i,j,CUR.team) && robotMap[j][i].unit == CHURCH)
    ret ++;
    return ret;
  }
  Action2 buildClose(int t) {
    // if close enough, stay in r^2 in [17,36], and as close as possible to destination
    // if already enough to kill or running out of resources, stop building
    int bestVal = 2*MOD; Action2 A = null;
    for (int dx = -1; dx <= 1; dx++) for (int dy = -1; dy <= 1; dy++) {
      int x = CUR.x+dx, y = CUR.y+dy;
      if (passable(x,y)) {
        int dis = euclidDist(fdiv(destination,64),destination%64, x, y), val = 0;
        val += Math.abs(dis-10);
        if (numOpen(x,y) <= 2) val += 20*(2-numOpen(x,y));
        val += 10*churchSquare(x,y);
        if (val < bestVal) { bestVal = val; A = buildAction(t, dx, dy); }
      }
    }
    return A;
  }
  Action2 tryBuildSecret(int t) {
    if (!isSuperSecret || !canBuild(t)) return null;
    // log("SECRET "+CUR.x+" "+CUR.y+" "+t);
    if (t == PREACHER) {
      if (fuel <= 15*activePreachers()+25*activeProphets()+100) return null;
      int x = mostDangerousPreacher(CUR);
      if (x != MOD) {
        if (activePreachers() > Math.max(5,U.closeEnemyAttackers())) return null;
        Robot2 P = makeRobot(PREACHER,CUR.team,fdiv(x,64),x%64);
        // log("DANGEROUS PREACHER: "+CUR.x+" "+CUR.y+" "+P.x+" "+P.y+" "+preacherDanger(P));
        return buildAction(t,fdiv(x,64)-CUR.x,(x%64)-CUR.y);
      }
      return null;
    }
    if (t == PROPHET) {
      if (euclidDist(destination) > 100) return null;
      if (karbonite <= 90*newPreachers() || fuel <= 15*activePreachers()+25*activeProphets()+100*newPreachers()+100) return null;
      return buildLeastDamage(t);
    }
    if (euclidDist(destination) <= 36) return buildClose(t);
    pi A = nextFuzzy(destination); if (A.f == MOD) return null;
    if (CUR.turn > 1 && (isAttacked(CUR.x+A.f,CUR.y+A.s) || seeEnemyStruct()))
      return buildLeastDamage(t); // if first in chain, don't let the next get attacked
    return buildAction(t,A.f,A.s);
  }

  int nearbyAttackers(int x, int y) {
    int ret = 0;
    for (int i = -10; i <= 10; ++i) for (int j = -10; j <= 10; ++j)
    if (i*i+j*j <= 100 && enemyAttacker(x+i,y+j)) ret ++;
    return ret;
  }
  boolean nearbyEnemyChurch(int x, int y) {
    for (int i = -10; i <= 10; ++i) for (int j = -10; j <= 10; ++j)
    if (i*i+j*j <= 100 && enemyRobot(x+i,y+j) && robotMap[y+j][x+i].unit == CHURCH)
    return true;
    return false;
  }
  Action2 tryBuildChurch() {
    if (!canBuild(CHURCH)) return null;
    int bestDx = MOD, bestDy = MOD, bestCnt = -MOD; // try to build adjacent to as many as possible
    for (int dx = -1; dx <= 1; dx++) for (int dy = -1; dy <= 1; dy++) {
      int x = CUR.x+dx; int y = CUR.y+dy;
      if (passable(x,y) && !karboniteMap[y][x] && !fuelMap[y][x]) {
        int cnt = nearbyAttackers(x,y);
        if (nearbyEnemyChurch(x,y)) cnt ++;
        if (cnt > 2+U.closeAttackers()) continue;
        cnt *= -100;
        for (int dx2 = -1; dx2 <= 1; dx2++) for(int dy2 = -1; dy2 <= 1; dy2++)
        if(!(dx2 == 0 && dy2 == 0)) {
          int x2 = x+dx2; int y2 = y+dy2;
          if (valid(x2,y2) && (karboniteMap[y2][x2] || fuelMap[y2][x2])) cnt += 10;
        }
        cnt += enemyDist[y][x][0];
        if (cnt > bestCnt) {
          bestDx = dx;
          bestDy = dy;
          bestCnt = cnt;
        }
      }
    }
    if (bestDx == MOD) return null;
    return buildAction(CHURCH, bestDx, bestDy);
  }
  Action2 tryBuild(int t) {
    if (!canBuild(t)) return null;
    if (t == PILGRIM) myPilgrim++;
    if (t == CHURCH) return tryBuildChurch();
    return buildLeastDamage(t);
  }
  Action2 tryBuildNoSignal(int t) {
    if (!canBuild(t)) return null;
    for (int dx = -1; dx <= 1; ++dx) for (int dy = -1; dy <= 1; ++dy)
    if (passable(CUR.x + dx, CUR.y + dy)) return buildAction(t, dx, dy);
    return null;
  }
  Action2 tryBuildEconSpam(int t) {
    if (!canBuild(t)) return null;
    for (int dx = -1; dx <= 1; ++dx) for (int dy = -1; dy <= 1; ++dy)
      if (passable(CUR.x + dx, CUR.y + dy)) {
        nextSignal = new pi(25432,2);
        return buildAction(t, dx, dy);
      }
    return null;
  }

  int getSignal(Robot2 R) {
    return 625*R.unit+25*(R.x-CUR.x+12)+(R.y-CUR.y+12)+30000;
  }

  boolean clearVision(Robot2 R) {
    if (CUR.unit == CASTLE && !seesEnemy(R.castle_talk)) return false;
    for (int i = -10; i <= 10; ++i) for (int j = -10; j <= 10; ++j) {
      if (i*i+j*j > VISION_R[R.unit]) continue;
      if (enemyRobot(R.x+i,R.y+j)) return false;
    }
    for (Robot2 A: robots) if (A.team == CUR.team && 30000 <= A.signal && A.signal < 40000)
    if (euclidDist(R,A) <= A.signal_radius) return false;
    return true;
  }

  boolean clearVisionStruct(Robot2 R) {
    for (int i = -10; i <= 10; ++i) for (int j = -10; j <= 10; ++j) if (i*i+j*j <= 100) {
      if (i*i+j*j > VISION_R[R.unit]) continue;
      if (enemyRobot(R.x+i,R.y+j)) return false;
    }
    return true;
  }

  void checkSignal() {
    for (Robot2 R: robots) {
      if (R.team == CUR.team && 30000 <= R.signal && R.signal < 40000) { // enemy locations
        int tmp = R.signal-30000;
        int type = fdiv(tmp,625); tmp %= 625;
        int x = fdiv(tmp,25)-12; x += R.x;
        int y = (tmp%25)-12; y += R.y;
        // log("ADDED "+CUR.coordinates()+" "+R.coordinates()+" "+x+" "+y);
        robotMapID[y][x] = MOD; robotMap[y][x] = makeRobot(type,1-CUR.team,x,y);
        lastTurn[y][x] = CUR.turn;
      } else if (R.team == CUR.team && R.unit == CASTLE && R.signal >= 7000 && R.signal < 20000) { // enemy castle locations
        if (CUR.unit == CASTLE) continue;
        decodeCastleLocations(R.signal);
        attackMode = true;
      }
    }
  }

  boolean superseded(int x, int y) {
    for (int i = -6; i <= 6; ++i) for (int j = -6; j <= 6; ++j)
    if (yourRobot(x+i,y+j)) {
      if (i == 0 && j == 0) continue;
      Robot2 R = robotMap[y+j][x+i];
      if (Math.sqrt(VISION_R[me.unit])+Math.sqrt(i*i+j*j) <= Math.sqrt(VISION_R[R.unit])) return true;
    }
    return false;
  }

  // PATROL

  boolean adjImpassable(int x, int y) {
    int[] xd = {0,1,0,-1}, yd = {1,0,-1,0};
    for (int i = 0; i < 4; ++i) {
      int X = x+xd[i], Y = y+yd[i];
      if (X % 2 == 0 && Y % 2 == 0) {
        if (!valid(X,Y)) return true;
        if (containsResource(X,Y)) return true;
      }
    }
    return false;
  }
  int patrolVal(int X, int Y, int x, int y) {
    if (!valid(X,Y) || (X % 2 == 0 && Y % 2 == 0)) return MOD;

    int big = 123456, val = 0;
    if (adjImpassable(X,Y)) val += big;
    if (containsResource(X,Y)) val += 2*big;
    if (euclidDist(X,Y,x,y) < 4) val += 4*big; // avoid congestion
    if (enemyDist[Y][X][0] <= Math.min(14,enemyDist[y][x][0])) val += 8*big;

    val += Math.abs(X-x)+Math.abs(Y-y)+2*Math.abs(enemyDist[y][x][0]-enemyDist[Y][X][0]-4);
    return val;
  }
  int patrolValOccupied(int X, int Y, int x, int y) {
    if (!(X == CUR.x && Y == CUR.y))
    if (!passable(X,Y)) return MOD;
    return patrolVal(X,Y,x,y);
  }

  // COMMUNICATION

  boolean canSeeYou(Robot2 R) {
    return euclidDist(R) <= VISION_R[R.unit];
  }
  int needRadius(Robot2 R) {
    int numEnemies = Math.max(U.closeEnemyAttackers(),1);
    // try to activate around 2*numEnemies allies
    // count number allies already activated
    int cnt = 0;
    for (int dx = -10; dx <= 10; dx++) for(int dy = -10; dy <= 10; dy++) {
      int x = CUR.x+dx; int y = CUR.y+dy;
      if (yourAttacker(x, y) && !clearVision(robotMap[y][x])) cnt++;
    }
    int necessary = Math.max(2*numEnemies - cnt, 0);
    // activate as much as necessary

    ArrayList<pi> allies = new ArrayList<>();
    for(int dx = -8; dx <= 8; dx++) for(int dy = -8; dy <= 8; dy++) {
      int x = CUR.x+dx, y = CUR.y+dy;
      if (yourAttacker(x,y) && canSeeYou(robotMap[y][x]) && clearVision(robotMap[y][x]))
      allies.add(new pi(dx,dy));
    }
    sortClose(allies);

    int ind = Math.min(necessary-1, allies.size()-1); if (ind == -1) return 0;
    int dx = allies.get(ind).f; int dy = allies.get(ind).s;
    return dx*dx+dy*dy;
  }
  int needRadiusStruct(Robot2 R, Action2 A) {
    int numEnemies = Math.max(U.closeEnemyAttackers(),1);
    // try to activate around 2*numEnemies allies
    // count number allies already activated

    int necessary = 2*numEnemies;
    // activate as much as necessary

    ArrayList<pi> allies = new ArrayList<>();
    for(int dx = -8; dx <= 8; dx++) for(int dy = -8; dy <= 8; dy++) {
      int x = CUR.x+dx, y = CUR.y+dy;
      if (yourAttacker(x,y) && canSeeYou(robotMap[y][x]) && clearVisionStruct(robotMap[y][x]))
      allies.add(new pi(dx,dy));
    }
    sortClose(allies);

    int ind = Math.min(necessary-1, allies.size()-1);
    if (ind == -1) {
      if (A != null && A.type == 4) return 2;
      return 0;
    }
    int dx = allies.get(ind).f; int dy = allies.get(ind).s;
    return dx*dx+dy*dy;
  }
  void warnOthers(Action2 A) { // CUR.x, CUR.y are new pos, not necessarily equal to me.x, me.y;
    if (fuel < 100 || superseded(CUR.x,CUR.y) || nextSignal != null) return;
    Robot2 R = closestNotPilgrim(ORI,1-CUR.team);
    // if (euclidDist(ORI,R) > VISION_R[CUR.unit]) R = closestRobot(ORI,1-CUR.team);
    if (euclidDist(ORI,R) > VISION_R[CUR.unit]) return;

    int r = 0;
    if (CUR.isStructure()) r = needRadiusStruct(R,A);
    else r = needRadius(R);
    if (r > 0) {
      // log("SIGNAL ENEMY: OPOS "+ORI.coordinates()+", CPOS "+CUR.coordinates()+", EPOS "+R.coordinates()+" "+getSignal(R));
      nextSignal = new pi(getSignal(R),r);
    }
  }

  void pr() {
    for(int i = 0; i < h; i++) {
      String s = "";
      for(int j = 0 ; j < w; j++) {
        s += " " + robotMapID[i][j];
      }
      log(s);
    }
  }

  boolean seenAllyDie() { // inaccurate if current robot is moving
    if (posLastTurn != 64*CUR.x + CUR.y) return false;
    for (int id: nearbyAllies) {
      boolean see = false;
      for (Robot2 R: robots) if (R.id == id) see = true;
      if (!see) return true;
    }
    return false;
  }
  void remNearbyAllies() {
    nearbyAllies.clear();
    for (int dx = -2; dx <= 2; dx++) for (int dy = -2; dy <= 2; dy++)
    if (yourRobot(CUR.x+dx, CUR.y+dy))
    nearbyAllies.add(robotMapID[CUR.y+dy][CUR.x+dx]);
  }
  void remAtkToPatrolPrev() {
    if (!IS_STRUCT[CUR.unit] || atkToPatrol == null) return;
    if (atkToPatrolPrev == null) atkToPatrolPrev = new int[4097];
    for (int i = 0; i < 4097; i++) atkToPatrolPrev[i] = atkToPatrol[i];
  }

  boolean isSignalSecret(int sig) {
    return sig >= 50000 && sig < 60000;
  }
  int decodeSecretSignal(int s) { // returns signaled destination
    s -= 50000;
    return s;
  }
  int encodeSecretSignal() {
    return destination+50000;
  }
  boolean enoughResourcesSecret() {
    int needKarbonite = fdiv(50+10,2)*64 + 1000; // path there + leftovers
    int needFuel = fdiv(200+50,2)*64 + 3000;
    int num = Math.min(30,Math.max(totResource+3,10));
    needKarbonite = fdiv(needKarbonite*num,30);
    needFuel = fdiv(needFuel*num,30);
    // 4 squares -> 60
    // # resources squares over 24
    if (karbonite > needKarbonite && fuel > needFuel) return true;
    if (karbonite > needKarbonite/2 && fuel > needFuel/2 && CUR.turn > 900) return true;
    return false;
  }
  int getDestination() {
    int bestBlock = MOD, bestDest = MOD;
    for (int t: castleX.keySet()) {
      int x = castleX.get(t), y = castleY.get(t);
      if (wsim) x = w-1-x;
      else y = h-1-y;
      int dest = 64*x+y;
      if (seenSuccesses.contains(100+((dest^12345)%100))) continue;
      int o = surround(dest);
      if (o < bestBlock) {
        bestBlock = o;
        bestDest = dest;
      }
    }
    for (int t: castleX.keySet()) if (myCastleID.contains(t))
    if (euclidDist(castleX.get(t),castleY.get(t),fdiv(bestDest,64),bestDest%64) < euclidDist(bestDest)) return MOD;
    return bestDest;
  }
  void recalcDestination() {
    for (Robot2 R: robots)
    if (enemyStruct(R) && Math.sqrt(euclidDist(R))+10 <= Math.sqrt(euclidDist(destination)))
    destination = MOD;

    if (destination == MOD) {
      for (Robot2 R: robots)
      if (enemyStruct(R) && euclidDist(R) < euclidDist(destination))
      destination = 64*R.x+R.y;
      // log("RESET DESTINATION TO "+coordinates(destination));
    }
  }
  void checkSecretUnit() { // determine if this is a super secret unit
    // if (CUR.team == 1) return;
    if (isSuperSecret) return;

    if (CUR.unit == CASTLE) {
      if ((enoughResourcesSecret() || CUR.turn > 3000) && lastSecretAttack <= CUR.turn-50) { // true
        if (myCastleID.size() > survivingOtherCastles()) return;
        destination = getDestination(); if (destination == MOD) return;
        // log("WHAT "+coordinates(destination));
        isSuperSecret = true;
        lastSecretAttack = CUR.turn; castle_talk = 254;
      }
    } else {
      if (CUR.turn != 1) return;
      for (Robot2 R: robots) if (adjacent(CUR,R) && R.team == CUR.team && isSignalSecret(R.signal)) {
        isSuperSecret = true;
        destination = decodeSecretSignal(R.signal);
        int x = fdiv(destination,64), y = destination%64;
        addStruct(makeRobot(CASTLE,1-CUR.team,x,y));
      }
    }

    // isSuperSecret = false;
    if (!isSuperSecret) return;
    // log("I AM SUPER SECRET!");
    recalcDestination();
    // log("KARBONITE: "+karbonite+" FUEL: "+fuel+" TURN: "+CUR.turn+" UNIT: "+CUR.unit+" IS SUPER SECRET! "+fdiv(destination,64)+" "+(destination%64));
  }

  void checkValid(ArrayList<Integer> A) {
    ArrayList<Integer> res = new ArrayList<Integer>();
    for (Robot2 R: robots) for (int j: A) if (R.id == j) res.add(j);
    A.clear();
    for (int i: res) A.add(i);
  }
  void signalSuccessfulAttack() {
    if (!isSuperSecret) return;
    if (!inVisionRange(destination)) return;
    if (signaledSuccessfulAttack) return;

    boolean dead = false;
    if (!containsRobot(destination)) dead = true;
    else if (robotMap[destination%64][fdiv(destination,64)].unit != CASTLE) dead = true;
    if (!dead) return;

    // log("DEAD! "+destination);
    signaledSuccessfulAttack = true;
    castle_talk = 100+((destination^12345)%100);
  }
  void updateSuccessfulAttacks() {
    if (CUR.unit != CASTLE) return;
    for (Robot2 R: robots) if (R.team == CUR.team)
    if (100 <= R.castle_talk && R.castle_talk < 200)
    seenSuccesses.add(R.castle_talk);
  }

  void checkSpam() {
    if (lastSpam != -MOD) {
      lastSpam ++;
      return;
    }
    for (Robot2 R: robots)
      if (R.signal == 25432 && (R.team == CUR.team || R.signal_radius == w*w+h*h-7)) {
        shouldSpam = true;
        lastSpam = 0;
      }
  }

  int survivingOtherCastles() {
    int ret = 0;
    for (int t: castleX.keySet()) {
      int x = castleX.get(t), y = castleY.get(t);
      if (wsim) x = w-1-x;
      else y = h-1-y;
      int dest = 64*x+y;
      if (seenSuccesses.contains(100+((dest^12345)%100))) continue;
      ret ++;
    }
    return ret;
  }

  void setClosestEnemy() {
		enex = -1;
		eney = -1;
		besx = -1;
		besy = -1;
		for(int i = 0; i < 4096; i++) patrolscore[i] = MOD;
		if(CUR.unit == CHURCH) return;
		if(wsim) {
			enex = w-1-CUR.x;
			eney = CUR.y;
		} else {
			enex = CUR.x;
			eney = h-1-CUR.y;
		}
		besx = CUR.x; besy = CUR.y;
    double d = realdis(enex,eney,CUR.x,CUR.y);
    double dx = (enex-CUR.y)/d; double dy = (eney-CUR.y)/d;
    besx += 1.5*dx; besy += 1.5*dy;
	}

  // TURN
  void updateVars() {
    castle_talk = -1; nextSignal = null;

    // if (CUR.team == 1) shouldSave = false;
    robots = new Robot2[getVisibleRobots().length];
    for (int i = 0; i < robots.length; ++i) robots[i] = new Robot2(getVisibleRobots()[i]);
    if (CUR.turn == 1) {
      for (int i = 0; i < robots.length; ++i)
        if (robots[i].team == CUR.team && robots[i].unit == CASTLE && adjacent(CUR,robots[i]))
      producedByCastle = true;
    }

    for (int i = 0; i < robots.length; ++i)
      if (robots[i].team == CUR.team && myCastleID.contains(robots[i].id))
        if (robots[i].castle_talk == 254) {
          // log("SECRET ATTACK!!!!");
          lastSecretAttack = CUR.turn; // update secret attacks
          shouldSave = false;
        }

    posRecord[me.turn] = new pi(me.x,me.y);
    for (int i = 1; i <= 4096; ++i) lastPos[i] = null;
    for (int i = 0; i < h; ++i) for (int j = 0; j < w; ++j)
      if (robotMapID[i][j] > 0 && robotMapID[i][j] < MOD)
        lastPos[robotMapID[i][j]] = new pi(j,i);

    checkSignal(); // info might not be accurate: some troops may be dead already
    checkSecretUnit();
    checkSpam();

    for (int i = 0; i < h; ++i) for (int j = 0; j < w; ++j) {
      int t = getVisibleRobotMap()[i][j]; if (t == -1) continue;
      lastTurn[i][j] = CUR.turn;
      robotMapID[i][j] = t;
      if (robotMapID[i][j] == 0) robotMap[i][j] = null;
      else {
        Robot2 R = getRobot2(t);
        if (lastPos[t] != null && robotMapID[lastPos[t].s][lastPos[t].f] == t) {
          robotMapID[lastPos[t].s][lastPos[t].f] = -1;
          robotMap[lastPos[t].s][lastPos[t].f] = null;
          robotMapID[i][j] = t;
        }
        lastPos[t] = new pi(j,i); robotMap[i][j] = R;
        addStruct(R);
      }
    }
    rem(myCastle); rem(otherCastle); rem(myChurch); rem(otherChurch);

    if (CUR.unit == CASTLE) {
      if (fuel > 2000) shouldSave = true;
      if (myCastleID.size() > survivingOtherCastles()) shouldSave = false;
      if (lastSecretAttack <= CUR.turn-48) {
        isSuperSecret = false;
        continuedChain = false;
      }
      checkValid(myStructID); checkValid(myCastleID);
    }

    bfs.upd(); // if (CUR.unit == CRUSADER) bfsShort.upd();
    if (isSuperSecret) {
      if (sm == null) sm = new secretMap(this);
      sm.upd();
    }
    U = new unitCounter(this);
    genEnemyDist();
    if (CUR.unit == PILGRIM) genDanger();
    if (CUR.turn > 5) {
      signalSuccessfulAttack();
      updateSuccessfulAttacks();
    }
    setClosestEnemy();
  }

  public Action2 chooseAction() {
    Action2 A = null;
    switch (CUR.unit) {
      case CASTLE: {
        Castle C = new Castle(this);
        A = C.run();
        break;
      }
      case CHURCH: {
        Church C = new Church(this);
        A = C.run();
        break;
      }
      case PILGRIM: {
        Pilgrim C = new Pilgrim(this);
        A = C.run();
        break;
      }
      case CRUSADER: {
        Crusader C = new Crusader(this);
        A = C.run();
        break;
      }
      case PROPHET: {
        Prophet C = new Prophet(this);
        A = C.run();
        break;
      }
      case PREACHER: {
        Preacher C = new Preacher(this);
        A = C.run();
        break;
      }
    }
    if (A == null) A = new Action2();
    if (A.type == 0) {
      robotMap[CUR.y][CUR.x] = null; robotMapID[CUR.y][CUR.x] = 0;
      CUR.x += A.dx; CUR.y += A.dy;
      robotMap[CUR.y][CUR.x] = CUR; robotMapID[CUR.y][CUR.x] = CUR.id;
    }
    return A;
  }
  boolean seeEnemy() {
    boolean b = false;
    for (int i = -14; i <= 14; ++i) for (int j = -14; j <= 14; ++j)
    if (i*i+j*j <= 196 && enemyRobot(CUR.x+i,CUR.y+j) && lastTurn[CUR.y+j][CUR.x+i] >= CUR.turn-30) {
      b = true;
    }
    return b;
  }
  void finish() { // 0 to 5: unit,
    posLastTurn = 64*CUR.x + CUR.y;
    lastHealth = CUR.health;
    if (castle_talk == -1) {
      if (CUR.unit == CASTLE) {
        castle_talk = Math.min(U.closeAttackers(),253);
      } else {
        if (CUR.turn == 1) castle_talk = CUR.unit;
        else {
          castle_talk = 6;
          if (seeEnemy()) castle_talk += 1;
          if (attackMode) castle_talk += 2;
          if (castle_talk == 6 && giveup) castle_talk = 10;
        }
      }
    }
    castleTalk(castle_talk);
    if (nextSignal != null) signal(nextSignal.f,nextSignal.s);
    remAtkToPatrolPrev();
  }

  boolean checkOccupiedSpam(int x, int y) {
		for(Robot2 r: robots) if(r.x == x && r.y == y) return true;
		return false;
	}

  boolean runSpam() {
		if(CUR.unit != CHURCH && CUR.unit != PILGRIM) return false;
		if(CUR.turn != 1) return false;
		checkSpam(); if(!shouldSpam) return false;
		for (int i = 0; i < robots.length; ++i) {
      if (robots[i].team == CUR.team && robots[i].unit == CASTLE && adjacent(CUR,robots[i])) {
				producedByCastle = true;
				return false;
			}
		}

		// just build in a random direction
		if(fuel < 2) return false;
		signal(25432, 2);
		if(me.unit == CHURCH) {
			if(karbonite < CONSTRUCTION_K[PILGRIM] || fuel-2 < CONSTRUCTION_F[PILGRIM]) return false;
		} else {
			if(karbonite < CONSTRUCTION_K[CHURCH] || fuel-2 < CONSTRUCTION_F[CHURCH]) return false;
		}

		boolean done = false;
		for(int dx = -1; dx <= 1; dx++) {
			for(int dy = -1; dy <= 1; dy++) {
				if(dx == 0 && dy == 0) continue;
				if(!valid(me.x+dx, me.y+dy)) continue;
				if(checkOccupiedSpam(me.x+dx, me.y+dy)) continue;
				done = true;
				build = buildAction(3-me.unit, dx, dy);
				break;
			}
		}
		return done;
	}

	pi nextFuzzy(int des) {
		int x = fdiv(des,64); int y = des%64;
		int bestDist = MOD; pi bestNext = new pi(MOD, MOD);
		for(int dx = -1; dx <= 1; dx++) {
			for(int dy = -1; dy <= 1; dy++) {
				if(dx == 0 && dy == 0) continue;
				if(!valid(me.x+dx, me.y+dy)) continue;
				if(checkOccupiedSpam(me.x+dx, me.y+dy)) continue;
				if(euclidDist(me.x+dx,me.y+dy, x,y) < bestDist) {
					bestDist = euclidDist(me.x+dx,me.y+dy, x,y);
					bestNext = new pi(dx,dy);
				}
			}
		}
		return bestNext;
	}

	boolean runSecret() {
		if (CUR.unit != CHURCH && CUR.unit != PILGRIM || CUR.turn != 1) return false;
		for (int i = 0; i < robots.length; ++i)
      if (robots[i].team == CUR.team && robots[i].unit == CASTLE && adjacent(CUR,robots[i])) {
				producedByCastle = true;
				return false;
			}

    robotMap = new Robot2[h][w]; robotMapID = new int[h][w];
    for (int i = 0; i < h; ++i) for (int j = 0; j < w; ++j) robotMapID[i][j] = -1;
    lastTurn = new int[h][w];
    for (int i = 0; i < h; ++i) for (int j = 0; j < w; ++j) lastTurn[i][j] = -MOD;

		for (int i = 0; i < h; ++i) for (int j = 0; j < w; ++j) {
      int t = getVisibleRobotMap()[i][j]; if (t == -1) continue;
      lastTurn[i][j] = CUR.turn;
      robotMapID[i][j] = t;
      if (robotMapID[i][j] == 0) robotMap[i][j] = null;
      else {
        Robot2 R = getRobot2(t);
        if (lastPos[t] != null && robotMapID[lastPos[t].s][lastPos[t].f] == t) {
          robotMapID[lastPos[t].s][lastPos[t].f] = -1;
          robotMap[lastPos[t].s][lastPos[t].f] = null;
          robotMapID[i][j] = t;
        }
        lastPos[t] = new pi(j,i); robotMap[i][j] = R;
        addStruct(R);
      }
    }

    checkSecretUnit(); if (!isSuperSecret) return false;
    if (CUR.unit == PILGRIM) {
			if (shouldStopChain()) return false;
			build = tryBuildSecret(CHURCH); return true;
		} else {
			if (shouldStopChain()) return false;
			Church temp = new Church(this);
			build = temp.runSuperSecret(); return true;
		}
	}

  public Action turn() {
		w = map[0].length; h = map.length;
		ORI = new Robot2(me); CUR = new Robot2(me);
		robots = new Robot2[getVisibleRobots().length];
		for (int i = 0; i < robots.length; ++i) robots[i] = new Robot2(getVisibleRobots()[i]);

		if (runSpam()) return conv(build);
		/*if (runSecret()) {
      if (isSuperSecret && build.type == 4)
        if (!(CUR.unit == CASTLE && continuedChain)) {
          nextSignal = new pi(encodeSecretSignal(),2);
          continuedChain = true;
          log("OOPS TRY SIGNAL");
          // log(CUR.x+" "+CUR.y+" MAKE SECRET UNIT "+A.type+" "+A.unit+" "+A.dx+" "+A.dy);
        }
      log("HUHHH "+CUR.unit+" "+build.type);
      return conv(build);
    }*/
    initVars();
    updateVars();
    /*if (CUR.unit == CASTLE) {
      String t = ""; for (int i: myCastleID) t += i+" ";
      log("CASTLE "+t);
    }*/
    // log("TIME "+me.turn+" "+me.time);
    // if (me.team == 1) return null;
    // if (me.team == 1) attackMode = true;
    // if (me.team == 1) shouldSave = false;
    // if (me.turn == 1) log("UNIT: "+CUR.unit);


    Action2 A = chooseAction();
    if (isSuperSecret && A.type == 4)
      if (!(CUR.unit == CASTLE && continuedChain)) {
        nextSignal = new pi(encodeSecretSignal(),2);
        continuedChain = true;
        log(CUR.x+" "+CUR.y+" MAKE SECRET UNIT "+A.type+" "+A.unit+" "+A.dx+" "+A.dy);
      }

    warnOthers(A); startEconSpam(); finish(); // startAttack();
    if (A.type == 3 && CUR.unit != PREACHER)
      hits[robotMap[CUR.y+A.dy][CUR.x+A.dx].id] ++;
    return conv(A);
  }
}
