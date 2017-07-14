// http://www.geeksforgeeks.org/multiplicative-inverse-under-modulo-m/
 
#include<iostream>
using namespace std;
  
int gcdExtended(int a, int b, int *x, int *y);
  
int modInverse(int a, int m) { 
    int x, y;
    int g = gcdExtended(a, m, &x, &y); // 
    if (g != 1) return 0;
    else return (x%m + m) % m;
}
 
int gcdExtended(int a, int b, int *x, int *y) {
    if (a == 0) {
        *x = 0, *y = 1;
        return b;
    }
  
    int x1, y1; 
    int gcd = gcdExtended(b%a, a, &x1, &y1); 
     
    // (b%a)*x1+a*y1=1
    // now substitute b%a=b-(b/a)*a
  
    *x = y1 - (b/a) * x1; 
    *y = x1;
  
    return gcd;
}
 
int main() {
    int a = 3, m = 11;
    cout << modInverse(a, m);
    return 0;
}
