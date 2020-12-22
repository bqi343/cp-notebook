// N^4

#include <iostream>
using namespace std;
 
struct Cow {
  int time_stopped; // time at which stopped (0 if never stopped)
  int x, y;         // current location
  char dir;         // N or E
};
 
int N;
Cow C[50];
 
// At what time would cow i hit the rut carved out by cow j and stop?
// (only considering these two cows for the moment)
int when_hits(int i, int j, int current_time)
{
  Cow I = C[i], J = C[j];
  if (I.time_stopped != 0) return 0; // has I already stopped?
  if (I.dir == J.dir) return 0; // never hits if moving same direction (or same cow)
 
  // Possibly flip coordinates so that for simpllicity, we can
  // assume without loss of generality that I is moving north, and J east
  if (I.dir == 'E') { swap (I.x, I.y); swap (J.x, J.y); } 
  
  if (J.y <= I.y) return 0; // J isn't north of I?
 
  if (J.time_stopped != 0) {
    if (I.x > J.x || I.x < J.x - J.time_stopped) return 0;
  } else {
    if (I.x < J.x - current_time || I.x >= J.x + J.y - I.y) return 0;
  }
 
  return current_time + J.y - I.y;
}
 
// Returns the next time after current_time at which a cow hits a rut and stops
// Move cows forward until that time and update which cows are stopped
int advance_to_next_event(int current_time)
{
  int T[50] = {0}, minT = 0;
  for (int i=0; i<N; i++) {
    for (int j=0; j<N; j++) {
      int t = when_hits(i, j, current_time);
      if (t != 0 && (T[i] == 0 || t < T[i])) T[i] = t; 
    }
    if (T[i] != 0 && (minT == 0 || T[i] < minT)) minT = T[i]; 
  }
  // T[i] is the next time something happens to cow i; minT is the earliest of these
 
  if (minT == 0) return 0;
 
  // Advance cows, stopping those that hit a rut
  for (int i=0; i<N; i++) {
    if (C[i].time_stopped == 0)
      if (C[i].dir == 'N') C[i].y += (minT - current_time);
      else                 C[i].x += (minT - current_time);
    if (T[i] == minT) C[i].time_stopped = minT;
  }
 
  return minT;
}
 
int main(void)
{
  cin >> N;
  for (int i=0; i<N; i++) cin >> C[i].dir >> C[i].x >> C[i].y;
 
  int current_time = 0;
  do { current_time = advance_to_next_event(current_time); }
  while (current_time != 0);
 
  for (int i=0; i<N; i++)
    if (C[i].time_stopped == 0) cout << "Infinity\n";
    else                        cout << C[i].time_stopped << "\n";
}