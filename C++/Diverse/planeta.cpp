#include <fstream>
#include <vector>

// https://www.infoarena.ro/problema/planeta

/*
15 14023

1 2 3 4 5 15 8 7 6 14 9 12 10 11 13 

---

2 2

2 1
*/

using namespace std;

ifstream f("planeta.in");
ofstream g("planeta.out");

int N;

// 64 bits
long long K;
long long nrOfBSTs[32];

// Generating the number of Binary Seach Trees(BSTs)
// for a given number `N`.
// Assuming there are `N` nodes, the reasoning behind it is
// to take each node from `1...N` as a root and see what happens.
// For example, if `N = 6` and we start with node `1` as root
// we'd have a tree that has `1` as root and on its right there will
// be the remaining 5 nodes(there are no nodes <1 for now, so nothing on the left side).
// Now, there we must work on the right subtree(the only subtree for now) and determine
// how many BSTs can be formed with 5 nodes. We apply the same reasoning and then we'd have
// to determine how many BSTs with 4 nodes and so forth.
// Because of this, we could generate in a `bottom-up` fashion.
// Way better explained here: https://www.youtube.com/watch?v=YDf982Lb84o.
void generateNrOfBSTsForN (int nrNodes) {
   // Base case
  nrOfBSTs[0] = 1;
  
  for (int nodeIdx = 1; nodeIdx <= nrNodes; nodeIdx++) {
      for (int prevNodeIdx = 1; prevNodeIdx <= nodeIdx; prevNodeIdx++) {
         // `nrOfBSTs[prevNodeIdx - 1]`: referring to what's on left subtree
         // `nrOfBSTs[nodeIdx - prevNodeIdx]`: referring to what's on the right subtree
         // With `+=` we accumulate that results of previous computations.
         nrOfBSTs[nodeIdx] += nrOfBSTs[prevNodeIdx - 1] * nrOfBSTs[nodeIdx - prevNodeIdx];
      }
  }
}

void readFromInput () {
  f >> N >> K;

  f.close();
}

void findKthTravesal (int startingNode, int nrOfNodes, long long kthTraversal) {
   // Nothing on the left/right subtree.
  if (nrOfNodes == 0) {
      return;
  }

   // Similar to the above scenario,
   // but in this case there is exactly **one node** in in the left/right subtree.
  if (nrOfNodes == 1) {
      g << startingNode + 1 << ' ';
      return;
  }
  
  for (int nodeIdx = 1; nodeIdx <= nrOfNodes; nodeIdx++) {
      // For a given root node, there are a number of permutations that take place
      // in both subtrees(left & right). If that number is < `kthTraversal`
      // then we know for sure we need to look for the next roots.
      long long nrPermutationOnLeftSubtree = nrOfBSTs[nodeIdx - 1];
      long long nrPermutationOnRightSubtree = nrOfBSTs[nrOfNodes - nodeIdx];
      long long nrOfPermutations = nrPermutationOnLeftSubtree * nrPermutationOnRightSubtree;
      if (nrOfPermutations < kthTraversal) {
         // Trying the next node as root
        kthTraversal -= nrOfPermutations;
      } else {
         // We're dealing with **preorder** traversals
         // so we print the root first, then we traverse
         // the left subtree, and then the right subtree.

        g << startingNode + nodeIdx << ' ';

         // Left subtree
        findKthTravesal(
            // We keep the same node, because on the right we only have
            // nodes with smaller values than the root's value.
            startingNode,
            nodeIdx - 1,
            (kthTraversal - 1) / nrPermutationOnRightSubtree + 1
        );

         // Right subtree
        findKthTravesal(
            // The following nodes will have a bigger value than the root's value.
            startingNode + nodeIdx,
            // How many nodes are on the right
            nrOfNodes - nodeIdx,
            // What remained*(i.e the rest) after traversing the left subtree
            (kthTraversal - 1) % nrPermutationOnRightSubtree + 1
        );

         // We found the root we've been looking for
         // So, no need to search further.
        return;
      }
  }
}

int main () {
  readFromInput();
  generateNrOfBSTsForN(N);
  findKthTravesal(0, N, K);

  g.close();

  return 0;
}