#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

/**
 * Task. You are given a description of a rooted tree. Your task is to compute and output its height. Recall
that the height of a (rooted) tree is the maximum depth of a node, or the maximum distance from a
leaf to the root. You are given an arbitrary tree, not necessarily a binary tree.
Input Format. The first line contains the number of nodes 𝑛. The second line contains 𝑛 integer numbers
from −1 to 𝑛 − 1 — parents of nodes. If the 𝑖-th one of them (0 ≤ 𝑖 ≤ 𝑛 − 1) is −1, node 𝑖 is the root,
otherwise it’s 0-based index of the parent of 𝑖-th node. It is guaranteed that there is exactly one root.
It is guaranteed that the input represents a tree.
Note that it is not necessarily a binary tree i.e. a node can have more than two children

Constraints. 1 ≤ 𝑛 ≤ 10pow(5)
Output Format. Output the height of the tree.
 * 
*/

class Node;

class Node {
public:
    int key;
    Node *parent;
    std::vector<Node *> children;

    Node() {
      this->parent = NULL; // by default parent is null i.e. when resize creates node elements
    }

    void setParent(Node *theParent) {
      // having parent as a pointer allows it to be referenced/modified wherever it is i.e. updating its children
      parent = theParent;
      parent->children.push_back(this); // updating its children
    }
};

int getMaxHeightNaive(int n, std::vector<Node> nodes);
int getMaxHeight(Node root);


int main_with_large_stack_space() {
  std::ios_base::sync_with_stdio(0);
  int n;
  std::cin >> n;

  std::vector<Node> nodes; // will hold the tree
  nodes.resize(n); // this constructs n new nodes in the vector
  int rootIndex;

  // build the tree
  for (int child_index = 0; child_index < n; child_index++) {
    int parent_index;
    std::cin >> parent_index;
    if (parent_index == -1) rootIndex = child_index;
    if (parent_index >= 0)
      nodes[child_index].setParent(&nodes[parent_index]); // this is a non-root node, set its parent; will also add this node as a child of this parent
    nodes[child_index].key = child_index;
  }

  // int maxHeightNaive = getMaxHeightNaive(n, nodes);
  Node root = nodes[rootIndex];
  int maxHeight = getMaxHeight(root);
    
  std::cout << maxHeight << std::endl;
  return 0;
}

// g++ 2_tree-height.cpp -o bin/2_tree-height && bin/2_tree-height
int main (int argc, char **argv)
{
#if defined(__unix__) || defined(__APPLE__)
  // NOTE: not using recursion, so needn’t worry about stack overflow problems
  // Allow larger stack space
  const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
  struct rlimit rl;
  int result;

  result = getrlimit(RLIMIT_STACK, &rl);
  if (result == 0)
  {
      if (rl.rlim_cur < kStackSize)
      {
          rl.rlim_cur = kStackSize;
          result = setrlimit(RLIMIT_STACK, &rl);
          if (result != 0)
          {
              std::cerr << "setrlimit returned result = " << result << std::endl;
          }
      }
  }

#endif
  return main_with_large_stack_space();
}

int getMaxHeight(Node root) {
  /**
   *  NOTE: this implementation supports non-binary trees
   * Determines the number of nodes in each level beforehand and increments the height when it 
   * gets to the last node, while going through each level
   * Breadth First Search goes through each node sequentially, level by level
   * */

  int height = 0;
  std::queue<Node> nodeQueue; // queue for the breadth first search
  nodeQueue.push(root);
  // levelSize is the number of nodes in a given level; used as a counter to check if we have reached the last node in a level, whereby height is incremented
  // levelSize is decremented as we traverse the level i.e. if 5 nodes in level, levelSize decremented from 5 to 1
  // levelSize is initially 1 to account for the root node, tempSize holds the size of the next level
  int levelSize = 1, tempSize = 0; 

  while (!nodeQueue.empty()) {
    Node node = nodeQueue.front();
    nodeQueue.pop();

    int size = node.children.size();
    // add the children of current node to the queue, this will be done for each node in the level
    // nodes in the same level will follow each other in the queue
    for (int i = 0; i < size; i++) {
      Node child = *node.children[i];
      nodeQueue.push(child);
    }

    // tempSize first needs to account for the current node's children since they are yet to be added
    // tempSize holds the number of nodes in the next level; from adding the size of each of the current level's children i.e. tempSize += size
    if (levelSize == 1) {
      // levelSize 1 implies that we have reached the last node in the level
      // so make levelSize the size of the next level (tempSize), increment the height, reset tempSize
      tempSize += size;
      levelSize = tempSize;
      height ++;
      tempSize = 0;
    }
    else {
      // for any other node (non-last), add its children no. to the tempSize and decrement levelSize 
      tempSize += size;
      levelSize--;
    }

  }
  return height;
}

// probably shouldn't pass vector by value, use const & (by reference)
int getMaxHeightNaive(int n, std::vector<Node> nodes) {
  // Replace this code with a faster implementation
  // evaluates the height of each node, large test cases fail e.g. est case 21 in tests folder
  int maxHeight = 0;
  for (int leaf_index = 0; leaf_index < n; leaf_index++) {
    int height = 0;
    for (Node *v = &nodes[leaf_index]; v != NULL; v = v->parent) {
      // v is NULL when the node has no parent i.e. we have arrived at the root node
      height++; // corresponds to nodes
    }
    // if the height evaluated for this leaf_index is larger, make it the new maxHeight
    maxHeight = std::max(maxHeight, height);
  }
  return maxHeight;
}
