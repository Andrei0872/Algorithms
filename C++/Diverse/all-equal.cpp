

/**
 * Given an array of unsigned numbers, determine the minimum number of
 *  moves need to be made such that all the elements become equal 
*/
/*

Example:

5
4 2 1 7 1
Output:

3
4 3 2
4 5 2
1 2 1

*/
#include <fstream>
#include <vector>
using namespace std;
ifstream fin("date.in");

ofstream fout("date.out");
pair<int,int> maxim(vector<int> a) {
  pair<int, int> value_index;
  int maxa = a[0];
  for (unsigned int i = 1; i < a.size(); i++)
    if (a[i] > maxa) maxa = a[i],value_index.first = a[i], value_index.second = i;
  return value_index;
}

pair<int,int> minim(vector<int> a) {
  pair<int, int> value_index;
  int mina = a[0];
  for (unsigned int i = 1; i < a.size(); i++)
    if (a[i] < mina) mina = a[i],value_index.first = a[i], value_index.second = i;

  return value_index;
}
int f(vector<int>a, int N) {
  for (unsigned int i = 0; i < a.size(); i++)
    if (a[i] != N) return 1;
  
  return 0;
}

int main() {

  int n, M=0, S, D ,k;
  double J, s = 0;
  vector<int>a;

  vector<pair<pair<int, int>, int> > result;
  int item;

  fin >> n;
  for (unsigned int i = 0; i < n; i++) {
    fin >> item;
    a.push_back(item);
    s += item;
  }

  
  fin.close();
  J = s / n;
  int j = s / n;
  
  if (j != J) fout << "-1";
  else {
    while (f(a, J) != 0) {
      pair<int, int> max_info = maxim(a);
      pair<int, int> min_info = minim(a);
      int index_min = min_info.second;  
      int index_max = max_info.second;       
      k = J - min_info.first;
      a[index_min] += k;
      a[index_max] -= k;
      result.push_back(make_pair(make_pair(index_max + 1, index_min + 1), k));
    }
    int size = result.size(); 

    fout  << size << '\n';
    for(int i = 0; i < size; i++) {
      fout << result[i].first.first << " " << result[i].first.second << " " << result[i].second << '\n';
    }    
  }
  fout.close();
  return 0;
}

