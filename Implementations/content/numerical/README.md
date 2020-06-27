# Numerical

### 6

  * More Matrices
    * Gaussian Elimination
      * Tutorial
        * [Wikipedia](https://en.wikipedia.org/wiki/Gaussian_elimination)
      * Problems
        * [Linear Equation Solver](https://open.kattis.com/problems/equationsolver)
        * [Xor Cycle](https://csacademy.com/contest/archive/task/xor_cycle/statement/) [](78)
        * [A2OJ](https://a2oj.com/category?ID=59)
    * Kirchhoff's Matrix Tree Theorem
      * Tutorial
        * [Wikipedia](https://en.wikipedia.org/wiki/Kirchhoff%27s_theorem)
      * Problems
        * [Hierarchies Count](https://codefights.com/interview-practice/task/TJ7hGeey6JYNFjBBg)
        * [Stranger Trees](http://codeforces.com/contest/917/problem/D)
  * Polynomials
    * Karatsuba
      * [Wikipedia](https://en.wikipedia.org/wiki/Karatsuba_algorithm)
      * [Implementation](http://codeforces.com/contest/623/submission/15807539)
      * Typically not needed due to FFT / NTT.
  * Simplex
    * [Goat Ropes](https://open.kattis.com/contests/fvfhq4/problems/goatropes)
  	* [Red & Black Tree](http://codeforces.com/contest/375/problem/E)
    * [ECNA 2019 C](https://open.kattis.com/contests/ecna19open/problems/cheeseifyouplease)
	  * USACO Training cowwars
    
### Interesting Task(s)

  * [Power Towers](https://open.kattis.com/problems/towers)
    * [Solution](https://petr-mitrichev.blogspot.com/2019/06/power-towers-solution.html)
  * [ODE](https://codeforces.com/blog/entry/76447)
    * EGF, D&C, Poly Inverse, Power Method
  * [P-Recursive](https://min-25.hatenablog.com/entry/2018/05/10/212805)
    * For a sequence $S_1,S_2,S_3,\ldots$ and $D\ge 0$, find the minimum $B>0$ such that there exist (nontrivial) coefficients $c_{ij}$ such that $\sum_{i=0}^{B-1}S_{y+i}\sum_{j=0}^{D}c_{ij}y^j=0$ for all $y>0$.
    * Ignore leading zeroes, use Gaussian Elim to find coefs. 
    * Can be used to extend sequence.
    * [Good Permutations](https://codeforces.com/group/ZFgXbZSjvp/contest/273473/problem/J)
