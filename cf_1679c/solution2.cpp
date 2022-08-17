#include <bits/stdc++.h>
using namespace std;


int main() {
  int N, Q;
  scanf("%d %d", &N, &Q);

  set<int> x_set;
  set<int> y_set;
  vector<int> x_count(N+1, 0);
  vector<int> y_count(N+1, 0);

  for (int i = 0; i < Q; ++i) {
    int query;
    cin >> query;
    switch (query) {
      case 1: {
        int x, y;
        scanf("%d %d", &x, &y);
        x_count[x]++;
        y_count[y]++;
        x_set.insert(x);
        y_set.insert(y);
      } break;
      case 2: {
        int x, y;
        scanf("%d %d", &x, &y);
        x_count[x]--;
        y_count[y]--;
        if (x_count[x] == 0) {
          x_set.erase(x);
        }
        if (y_count[y] == 0) {
          y_set.erase(y);
        }
      } break;
      case 3: {
        int x1, y1, x2, y2;
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        auto x1it = x_set.find(x2);
        auto x2it = x_set.find(x1);
        bool x_covered = x1it != x_set.end() && x2it != x_set.end() && distance(x2it, x1it) == x2 - x1;
        if (x_covered) {
          cout << "Yes\n";
          continue;
        }
        auto y1it = y_set.find(y2);
        auto y2it = y_set.find(y1);
        bool y_covered = y1it != y_set.end() && y2it != y_set.end() && distance(y2it, y1it) == y2 - y1;
        if (y_covered) {
          cout << "Yes\n";
          continue;
        }
        cout << "No\n";
      } break;
      default:
        break;
    }
  }

  return 0;
}
