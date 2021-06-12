#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// https://csacademy.com/contest/interview-archive/task/largest-concat-number/statement

string largestConcat(vector<string>& v) {
  sort(v.begin(), v.end(), [&](string s1, string s2) {
    // A base case: `s1 = 4`, `s2 = 49`(the array would be [s1, s2])
    // `s1 + s2 = 449`
    // `s2 + s1 = 494` X
    // So, in this case, we'd want to take `s2` before `s1`

    return s1 + s2 > s2 + s1;
  });

  string res = "";
  for (auto& str : v) {
    res += str;
  }

  return res[0] == '0' ? "0" : res;
}

int main() {
  int N;
  cin >> N;
  vector<string> v;
  for (int i = 0; i < N; ++i) {
    string number;
    cin >> number;
    v.push_back(number);
  }

  cout << largestConcat(v) << "\n";
  return 0;
}
