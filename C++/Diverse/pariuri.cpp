#include <iostream>
#include <fstream>
#include <unordered_map>

// https://www.infoarena.ro/problema/pariuri

using namespace std;

/* 
3
2 1 10 3 -60
1 3 50
3 1 -5 3 15 2 -5

3
2 -5 3 5 1 5
*/

ifstream f("./pariuri.in");
ofstream g("./pariuri.out");

unordered_map<int, int> timestampAndMoney;

int N;

void readFile()
{
  f >> N;
  int M, timestamp, money;

  for (int i = 0; i < N; i++)
  {
    f >> M;

    for (int j = 0; j < M; j++)
    {
      f >> timestamp >> money;
      int profit;
      auto it = timestampAndMoney.find(timestamp);

      if (it == timestampAndMoney.end())
      {
        profit = 0;
      }
      else
      {
        profit = it->second;
      }

      profit += money;

      if (it != timestampAndMoney.end())
      {
        it->second = profit;
      }
      else
      {
        timestampAndMoney.insert({timestamp, profit});
      }
    }
  }

  f.close();
}

void printResults()
{
  g << timestampAndMoney.size() << '\n';

  for (auto const &item : timestampAndMoney)
  {
    g << item.first << ' ' << item.second << ' ';
  }

  g.close();
}

int main()
{
  readFile();
  printResults();
}