
package bc19;

import java.util.*;
import java.math.*;

public class Consts {
    public static final int MOD = 1000000007;
    public static final int[] DX_EDGE_ONLY = {1, 0, -1, 0}, DY_EDGE_ONLY = {0, 1, 0, -1};
    public static final int[] DX = {1, 1, 0, -1, -1, -1, 0, 1}, DY = {0, 1, 1, 1, 0, -1, -1, -1};
    public static final int[] smDX = {1, -1, 0, 0, 1, 1, -1, -1};
    public static final int[] smDY = {0, 0, 1, -1, 1, -1, 1, -1};

    public static final int CASTLE = 0;
    public static final int CHURCH = 1;
    public static final int PILGRIM = 2;
    public static final int CRUSADER = 3;
    public static final int PROPHET = 4;
    public static final int PREACHER = 5;

    public static final int RED = 0;
    public static final int BLUE = 1;

    public static final int[] CONSTRUCTION_K = {-1, 50, 10, 15, 25, 30};
    public static final int[] CONSTRUCTION_F = {-1, 200, 50, 50, 50, 50};

    public static final int K_CARRY_CAP = 20;
    public static final int F_CARRY_CAP = 100;

    public static final boolean[] CAN_MOVE = {false, false, true, true, true};
    public static final int[] MOVE_SPEED = {-1, -1, 4, 9, 4, 4};
    public static final int[] MOVE_F_COST = {-1, -1, 1, 1, 2, 3};

    public static final int[] START_HEALTH = {200, 100, 10, 40, 20, 60};

    public static final int[] VISION_R = {100, 100, 100, 49, 64, 16};

    public static final int[] DAMAGE = {10, -1, -1, 10, 10, 20};

    public static final boolean[] CAN_ATTACK = {true, false, false, true, true, true};
    public static final boolean[] IS_ATTACKER = {false, false, false, true, true, true};
    public static final boolean[] IS_STRUCT = {true, true, false, false, false, false};

    public static final int[] MIN_ATTACK_R = {1, -1, -1, 1, 16, 1};
    public static final int[] MAX_ATTACK_R = {64, -1, -1, 16, 64, 16};
    public static final int[] ATTACK_F_COST = {10, -1, -1, 10, 25, 15};

    public static final int churchThreshold = 1; // min distance from nearest struct
}
