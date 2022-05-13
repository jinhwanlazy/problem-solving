#include <bits/stdc++.h>
using namespace std;

bool solution(string str) {
  const static string paranthesis = "([])";
  vector<char> s;
  for (char c : str) {
    if (find(paranthesis.begin(), paranthesis.end(), c) == paranthesis.end()) {
      continue;
    }
    if (c == '(' || c == '[') {
      s.push_back(c);
    } else if (s.empty()) {
      return false;
    } else if (s.back() == '(' && c == ')') {
      s.pop_back();
    } else if (s.back() == '[' && c == ']') {
      s.pop_back();
    } else {
      return false;
    }
  }
  return s.empty();
}

int main() {
  while (true) {
    string str;
    getline(cin, str);

    if (str == ".") {
      break;
    }
    cout << (solution(str) ? "yes" : "no") << "\n";
  }
  return 0;
}
