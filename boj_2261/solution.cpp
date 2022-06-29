#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()

using namespace std;
using LL = long long;
constexpr static int INF = numeric_limits<int>::max();

struct Point {
  int x; 
  int y;

  int sqDist(const Point& rhs) const {
    return (x - rhs.x) * (x - rhs.x) + (y - rhs.y) * (y - rhs.y);
  }

  friend istream& operator>> (istream& is, Point& rhs) {
    is >> rhs.x >> rhs.y;
    return is;
  }

  friend bool operator< (const Point& lhs, const Point& rhs) {
    return lhs.y != rhs.y ? lhs.y < rhs.y : lhs.x < rhs.x;
  }

  static bool cmpX(const Point& lhs, const Point& rhs) {
    return lhs.x != rhs.x ? lhs.x < rhs.x : lhs.y < rhs.y;
  }
};


int main() {
  int N;
  scanf("%d", &N);
  
  vector<Point> points(N);
  for (int i = 0; i < N; ++i) {
    cin >> points[i];
  }

  sort(all(points), Point::cmpX);
  set<Point> candidates;
  int l = 0;
	int ans = INF;
  for (int i = 0; i < points.size(); ++i) {
    const auto& p = points[i];
    while (l < i) {
      auto leftIt = candidates.find(points[l]);
      int d = leftIt->x - p.x;
      if (d * d >= ans) {
        candidates.erase(*leftIt);
        l++;
      }
      else {
        break;
      }
    }
    int d = sqrt(ans) + 1;
    auto lowerIt = candidates.lower_bound({-INF, p.y-d});
    auto upperIt = candidates.upper_bound({INF, p.y+d});
    for (auto it = lowerIt; it != upperIt; ++it) {
      ans = min(ans, it->sqDist(p));
    }
    candidates.insert(p);
  }
  printf("%d\n", ans);
  return 0;
}
