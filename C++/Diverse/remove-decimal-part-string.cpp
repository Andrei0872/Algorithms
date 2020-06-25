#include <iostream>
#include <cstring>

using namespace std;

int main () {
  char s[] = "abc 5,75121 def 5,25 foo 5 bar 5 beer";

  int len = strlen(s);

  int intLastDigitIdx = -1;
  for (int i = len - 1; i >= 0; i--) {
    if (s[i] >= '0' && s[i] <= '9') {
      if (intLastDigitIdx == -1) {
        intLastDigitIdx = i;
      }

      continue;
    }

    if (intLastDigitIdx != -1 && s[i] == ',') {

      strcpy(s + i, s + i + (intLastDigitIdx - i) + 1);
      intLastDigitIdx = -1;

      continue;
    }

    if (intLastDigitIdx != -1) { intLastDigitIdx = -1; }
  }

  cout << s << "\n";
}