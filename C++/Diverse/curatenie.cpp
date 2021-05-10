#include <fstream>
#include <vector>

// https://www.infoarena.ro/problema/curatenie

/* 
7
4 2 5 1 3 7 6
1 2 4 5 3 6 7

2 3
4 5
0 6
0 0
0 0
7 0
0 0
*/

using namespace std;

ifstream f("curatenie.in");
ofstream g("curatenie.out");

int N;
vector<int> preorder, inorder;

struct Node {
  int value;
  Node* right;
  Node* left;
};

void readFromInput () {
  f >> N;
  int val;

  for (int i = 0; i < N; i++) {
    f >> val;
    inorder.push_back(val);
  }

  for (int i = 0; i < N; i++) {
    f >> val;
    preorder.push_back(val);
  }

  f.close();
}

int indexOf (vector<int>& arr, int len, int elem) {
  for (int i = 0; i < len; i++) {
    if (arr[i] == elem) {
      return i;
    }
  }

  return -1;
}

// This is essentially what the problem asks for.
// We're given the 2 traversals(inorder and preorder) and we then
// need to construct the binary tree.
// We'll use `preoder` array to determine the roots and `inorder`
// do determine the left and right subtrees of a given node.
Node* constructBinaryTreeFromPreoderAndInorder (
  int inOrderStartIdx,
  int inOrderEndIdx,
  int preOrderCurrentIdx
) {
  if (preOrderCurrentIdx > N - 1 || inOrderStartIdx > inOrderEndIdx) {
    return NULL;
  }

  int crtRoot = preorder[preOrderCurrentIdx];
  int inOrderRootIdx = indexOf(inorder, N, crtRoot);

  // Basically the amount of nodes in the left subtree
  int distExclusive = inOrderRootIdx - inOrderStartIdx;

  Node *node = new Node();
  node->value = crtRoot;

  node->left = constructBinaryTreeFromPreoderAndInorder(
    inOrderStartIdx,
    inOrderRootIdx - 1,
    preOrderCurrentIdx + 1
  );

  node->right = constructBinaryTreeFromPreoderAndInorder(
    inOrderRootIdx + 1,
    inOrderEndIdx,
    // distExclusive - skipping the nodes from the left subtree
    distExclusive + preOrderCurrentIdx + 1
  );

  return node;
}

void printResultsToOutput () {
  for (int i = 0; i < N; i++) {
    g << inorder[i] << ' ' << preorder[i] << '\n';
  }

  g.close();
}

// At this point, after the tree has been built correctly
// the initial orders arrays are useless.
// So, we can use them to simulate a `pair<int, int>`
void recycleOrdersArrays (Node* root) {
  // We'll use `inoder` array for the left children
  // and the `preorder` array for the right children

  if (root == NULL) {
    return;
  }

  int rootVal = root->value;

  inorder[rootVal - 1] = root->left ? root->left->value : 0;
  preorder[rootVal - 1] = root->right ? root->right->value : 0;

  recycleOrdersArrays(root->left);
  recycleOrdersArrays(root->right);
  
  delete root;
}

int main () {
  readFromInput();

  Node* root = constructBinaryTreeFromPreoderAndInorder(0, N - 1, 0);
  recycleOrdersArrays(root);

  printResultsToOutput();

  return 0;
}