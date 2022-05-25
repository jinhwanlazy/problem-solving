#include <bits/stdc++.h>
using namespace std;

struct Node {
  map<string, Node> children;
};

void insert(Node& node, deque<string>& path) {
  if (path.empty()) {
    return;
  }
  const string front = path.front(); 
  path.pop_front();
  auto it = node.children.find(front);
  if (it == node.children.end()) {
    node.children.insert({front, {}});
  }
  insert(node.children[front], path);
}

void traverse(const Node& node, int depth = 0) {
  for (const auto& [s, nxt] : node.children) {
    for (int i = 0; i < depth; ++i) {
      cout << "--";
    }
    cout << s << "\n";
    traverse(nxt, depth+1);
  }
}


int main() {
  int T;
  cin >> T;

  Node root;
  
  while (T--) {
    int N;
    cin >> N;
    deque<string> path;
    while (N--) {
      string room;
      cin >> room;
      path.push_back(room);
    }
    insert(root, path);
  }

  traverse(root);
  return 0;
}
