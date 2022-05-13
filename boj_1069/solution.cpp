#include <bits/stdc++.h>
using namespace std;

int main() {
  double x, y, D, T;
  cin >> x >> y >> D >> T;

  double distance = sqrt(x * x + y * y);

  // case1: 걸어감.
  double cost = distance;

  // case2: 집 직전까지 점프하고 나머지는 걸어감.
  int step = distance / D;
  cost = min(cost, step * T + (distance - step * D));

  // case3: 목적지를 지나쳐 한 번 더  점프하고 나머지는 걸어감.
  cost = min(cost, (step + 1) * T + (step + 1) * D - distance);

  // case4: 점프만 사용해서 집에 감.
  cost = min(cost, max(2.0, step + 1.0) * T);

  cout << setprecision(10) << cost << "\n";
  return 0;
}
