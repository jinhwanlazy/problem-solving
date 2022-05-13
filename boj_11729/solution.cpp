#include <bits/stdc++.h>
using namespace std;

int hanoi(int from, int to, int empty, int n, vector<pair<int, int>>& report) {
  if (n == 1) {
    report.push_back({from, to});
    return 1;
  }

  int count = 1;
  count += hanoi(from, empty, to, n - 1, report);
  report.push_back({from, to});
  count += hanoi(empty, to, from, n - 1, report);
  return count;
}

int main() {
  int N;
  cin >> N;
  vector<pair<int, int>> report;
  cout << hanoi(1, 3, 2, N, report) << "\n";
  for (auto& res : report) {
    cout << res.first << " " << res.second << "\n";
  }
  return 0;
}
