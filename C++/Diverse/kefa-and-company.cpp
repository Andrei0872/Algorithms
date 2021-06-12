#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// https://codeforces.com/contest/580/problem/B

struct Friend {
  long long money;
  long long friendshipFactor;
};

int main () {
  long long nrFriends, maxAllowedDiff;
  vector<Friend> friends;

  cin >> nrFriends >> maxAllowedDiff;

  for (long long i = 0; i < nrFriends; i++) {
    Friend f;
    cin >> f.money >> f.friendshipFactor;

    friends.push_back(f);
  }

  // Sorting in ASC order by `money` so that we can use the `Two Pointers Technique`
  // By sorting them first, we make sure we find the money differences faster
  sort(friends.begin(), friends.end(), [&](Friend f1, Friend f2) {
    return f1.money < f2.money;
  });

  long long accumulatedFriendshipFactor = 0;
  long long maxFriendshipFactor = - 1;
  for (int start = 0, end = 0; end < nrFriends;) {
    while (end < nrFriends && friends[end].money - friends[start].money < maxAllowedDiff) {
      accumulatedFriendshipFactor += friends[end].friendshipFactor;
      // Enlarging the window
      end++;
    }

    // At this point, the money difference exceed the `maxAllowedDiff` limit
    maxFriendshipFactor = max(maxFriendshipFactor, accumulatedFriendshipFactor);
    // Going one step rightwards, so we must not leave anything in `accumulatedFriendshipFactor`
    accumulatedFriendshipFactor -= friends[start++].friendshipFactor;
  }

  cout << maxFriendshipFactor;

  return 0;
}