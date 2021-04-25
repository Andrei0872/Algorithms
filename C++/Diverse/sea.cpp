#include <iostream>

#include <fstream>
#include <algorithm>
#include <vector>
#include <math.h>
#include <iomanip>

/* 
https://www.infoarena.ro/problema/sea

3 5
-0.5 0.5
-2 5
3 4
-1 1
0 1
0 2
0 1
5 1

5.0990
0.7071
5.3852
0.7071
4.4721
*/

using namespace std;

ifstream f("sea.in");
ofstream g("sea.out");

struct Boat {
  double x, y;
  double dist;
};

void readInputFile () {
  // It is known that the lighthouses are read from the file
  // in ascending order based on their `x` value.
  // So, **if** we have the boats sorted by `x` value(the boats are read in random order)
  // then, for a given lighthouse, we can determine the minimum largest distance.
  int nrBoats, nrLighthouses;
  vector<Boat> boats;

  f >> nrBoats >> nrLighthouses;
  
  for (int i = 0; i < nrBoats; i++) {
    Boat b;
    f >> b.x >> b.y;

    b.dist = b.x;

    boats.push_back(b);
  }

  sort(boats.begin(), boats.end(), [](Boat& b1, Boat& b2) -> bool { return b1.dist < b2.dist; });

  int lastBoatIndexWithinLighthouseX = 0;

  double lighthouseX;
  int boatsReachedByLighthouse;
  for (int i = 0; i < nrLighthouses; i++) {
    f >> lighthouseX >> boatsReachedByLighthouse;

    while (lastBoatIndexWithinLighthouseX < nrBoats && boats[lastBoatIndexWithinLighthouseX].x < lighthouseX) {
      lastBoatIndexWithinLighthouseX++;
    }

    for (int j = 0; j < lastBoatIndexWithinLighthouseX; j++) {
      // The distance between the boat and the lighthouse.
      boats[j].dist = boats[j].y * boats[j].y + (lighthouseX - boats[j].x) * (lighthouseX - boats[j].x);

      // Checking whether we can rearrange the boats based on the new computed distance
      // so that the boat with the **smallest** distance comes first.
      int currentBoatIndex = j;
      while (currentBoatIndex > 0 && boats[currentBoatIndex -1 ].dist > boats[currentBoatIndex].dist) {
        swap(boats[currentBoatIndex - 1], boats[currentBoatIndex]);
        currentBoatIndex--;
      }
    }

    // At this points, the boats are properly arranged.
    g << fixed << setprecision(4) << sqrt(boats[boatsReachedByLighthouse -1].dist) << '\n';
  }

  f.close();
  g.close();
}

int main () {
  readInputFile();

  return 0;
}