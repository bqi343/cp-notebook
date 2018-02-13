import bc.*;

public class CumSum extends Globals {
	static int[][] cOp = new int[51][51];
	static int[][] cFriend = new int[51][51];
	static int[][] cYourDamageAttacker = new int[51][51];
	static int[][] cYourAttacker = new int[51][51];
	static int[][] cYourHealer = new int[51][51];
	static int[][] weight = new int[51][51];
	static pii[][] op = new pii[51][51];
	
	static void fill(int[][] arr) {
		for (int i = 1; i <= 50; ++i)
			for (int j = 1; j <= 50; ++j)
				arr[i][j] += arr[i-1][j]+arr[i][j-1]-arr[i-1][j-1];
	}
	
	static void reset(int[][] arr) {
		for (int i = 1; i <= 50; ++i)
			for (int j = 1; j <= 50; ++j)
				arr[i][j] = 0;
	}
	
	static int getSum(int[][] arr, int x1, int x2, int y1, int y2) {
		x1 = Math.max(x1,0); x2 = Math.min(x2, (int)C.getWidth()-1);
		y1 = Math.max(y1,0); y2 = Math.min(y2, (int)C.getHeight()-1);
		return arr[x2+1][y2+1]-arr[x1][y2+1]-arr[x2+1][y1]+arr[x1][y1];
	}
	
	static void genWeight(int i, int j) {
		weight[i][j] = 4*getSum(cYourDamageAttacker,i-2,i+2,j-2,j+2);
		weight[i][j] -= 2*getSum(cYourHealer,i-2,i+2,j-2,j+2);
		weight[i][j] += getSum(cYourAttacker,i-2,i+2,j-2,j+2);
		weight[i][j] *= 4;
	}
	
	static void gen() {
		reset(cOp);
		reset(cFriend);
		reset(cYourDamageAttacker);
		reset(cYourAttacker);
		reset(cYourHealer);
		
		for (int i = 0; i < C.getWidth(); ++i) 
			for (int j = 0; j < C.getHeight(); ++j) {
				if (tmp[i][j] == null) continue;
				
				if (tmp[i][j].team() == oteam) cOp[i+1][j+1] = 1;
				else {
					cFriend[i+1][j+1] = 1;
					if (tmp[i][j].unitType() == UnitType.Healer) cYourHealer[i+1][j+1] = 1;
					else if (fastGC.isAttacker(tmp[i][j])) {
						cYourAttacker[i+1][j+1] = 1;
						if (tmp[i][j].health() < tmp[i][j].maxHealth()) cYourDamageAttacker[i+1][j+1] = 1;
					}
				}
			}
		
		fill(cOp);
		fill(cFriend);
		fill(cYourDamageAttacker);
		fill(cYourAttacker);
		fill(cYourHealer);

		for (int i = 0; i < C.getWidth(); ++i) 
			for (int j = 0; j < C.getHeight(); ++j) 
				genWeight(i,j);
	}

}
