#include <fstream>
#include <unordered_map>

// https://www.infoarena.ro/problema/muzica

/* 
3 4
1 1 1 1 1000000000
1 2 7

2
*/

using namespace std;

int main () {
  ifstream f("muzica.in");
  ofstream g("muzica.out");

  int N, M;
  long A, B, C, D, E;
  unordered_map<int, bool> songsMap(100001);

  f >> N >> M;
  f >> A >> B >> C >> D >> E;

  int nrCommonSongs = 0;

  int elem;
  for (int i = 0; i < N; i++) {
    f >> elem;
    songsMap[elem] = 0;
  }

  if (songsMap.count(A)) {
    ++nrCommonSongs;
    songsMap.erase(A);
  }

  if (songsMap.count(B)) {
    ++nrCommonSongs;
    songsMap.erase(B);
  }

  for (int i = 2; i < M; i++) {
    int crt = (C * B + D * A) % E;

    A = B;
    B = crt;

    if (songsMap.count(B)) {
      ++nrCommonSongs;
      songsMap.erase(B);
    }
  }

  g << nrCommonSongs;

  f.close();
  g.close();

  return 0;
}