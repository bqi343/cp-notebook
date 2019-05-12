package bc19;

import java.util.*;
import java.math.*;

import static bc19.Consts.*;

public class secretMap extends moveMap {
  public secretMap(MyRobot Z) {
    super(Z,2); dirs.clear();
    for (int i = 0; i < 8; ++i) dirs.add(new pi(smDX[i],smDY[i]));
  }
	boolean ok(int x, int y) {
    return Z.passable(x,y);
		// return true;
	}
}
