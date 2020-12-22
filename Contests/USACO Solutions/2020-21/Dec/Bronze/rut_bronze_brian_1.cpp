// N^4

#include <iostream>
using namespace std;
 
const int MAX_N = 50;
 
int N, x[MAX_N], y[MAX_N], tstop[MAX_N];
char dir[MAX_N];
 
struct Intersection {
  int i, j, time_i, time_j, active;
};
Intersection I[MAX_N*MAX_N];
 
void find_all_intersections(void)
{
  int current = 0;
  for (int i=0; i<N; i++)
    for (int j=0; j<N; j++) {
 
      if (dir[i] == dir[j]) continue; // no intersection if same direction (or same cow)
 
      // Possibly flip coordinates so that for simpllicity, we can
      // assume without loss of generality that cow i is moving north, and cow j east
      int xi = x[i], yi = y[i], xj = x[j], yj = y[j];
      if (dir[i] == 'E') { swap(xi,yi); swap(xj,yj); } 
      
      if (yi > yj) continue; // cow i already north of cow j?
      if (xi < xj) continue; // cow i already west of cow j?
      if (xi >= xj + yj - yi) continue; // cow i passes before cow j can cut her off
 
      Intersection Inew = { i, j, yj-yi, xi-xj, 1 };
      I[current] = Inew;
      current++;
    }
}
 
int main(void)
{
  cin >> N;
  for (int i=0; i<N; i++) cin >> dir[i] >> x[i] >> y[i];
 
  find_all_intersections();
  
  // Repeatedly find earliest remaining intersection and process it
  while (1) {
    int earliest = -1;
    for (int i=0; i<MAX_N*MAX_N; i++)
      if (I[i].active)
	if (earliest == -1 || I[i].time_i < I[earliest].time_i) earliest = i;
    if (earliest == -1) break;
    Intersection &E = I[earliest];
    if (tstop[E.i] == 0 && (tstop[E.j] == 0 || tstop[E.j] > E.time_j))
      tstop[E.i] = E.time_i;
    E.active = 0;
  }
  
  for (int i=0; i<N; i++)
    if (tstop[i] == 0) cout << "Infinity\n";
    else               cout << tstop[i] << "\n";
}