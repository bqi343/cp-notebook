/**
 * Description: solve for min on functions which are strictly decreasing then strictly increasing
 * Source: own
 */

double eval(double x) { 
    return (x-5)*(x-5);
}

double ternary(double l, double r) {
    if (abs(r-l) <= 1e-9) return (l+r)/2;
    double l1 = (2*l+r)/3, r1 = (l+2*r)/3;
    return eval(l1) < eval(r1) ? ternary(l,r1) : ternary(l1,r);
} // ternary(-100,100) = 5