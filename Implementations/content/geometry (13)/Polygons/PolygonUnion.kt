/**
 * Description: Compute union or intersection of two polygons and
    * compute the area of the resulting figure.
 * Time: Runs quite quickly for two convex polygons with $10^5$ vertices each.
 * Source: Nick Wu
 * Verification: 
    * https://open.kattis.com/problems/abstractart
    * https://probgate.org/viewproblem.php?pid=249
 */

import java.awt.geom.* // at beginning of file
fun loadPoly(): DoubleArray {
    val n = rInt() // read n points
    return rDbs(2*n).toDoubleArray()
}
fun makeArea(ps: DoubleArray): Area {
    val p = Path2D.Double()
    p.moveTo(ps[0],ps[1])
    for (i in 0..ps.size/2-1) p.lineTo(ps[2*i],ps[2*i+1])
    p.closePath()
    return Area(p)
}
fun computeArea(a: Area): Double {
    val iter = a.getPathIterator(null)
    val buf = DoubleArray(6,{0.0})
    var ret = 0.0
    val ps = ArrayList<Double>()
    while (!iter.isDone()) {
        when(iter.currentSegment(buf)) {
            PathIterator.SEG_MOVETO,PathIterator.SEG_LINETO->{
                ps.add(buf[0])
                ps.add(buf[1])
            }
            PathIterator.SEG_CLOSE -> {
                ps.add(ps[0])
                ps.add(ps[1])
                for (i in 0..ps.size/2-2) ret -= ps[2*i]*ps[2*i+3]-ps[2*i+1]*ps[2*i+2]
                ps.clear()
            }
        }
        iter.next()
    }
    assert(ret >= 0)
    return ret/2
}
fun intersectArea(a: DoubleArray, b: DoubleArray): Double {
    val ret = makeArea(a)
    ret.intersect(makeArea(b)) // or .add for union
    return computeArea(ret)
}