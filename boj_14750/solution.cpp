#include <bits/stdc++.h>
#include <algorithm>
#define all(x) (x).begin(), (x).end()

using namespace std;
using LL = long long;

class Vec2
{
public:
  using T = LL;

public:
  T x;
  T y;

public:
  inline Vec2& operator= (const Vec2& rhs)
  {
    x = rhs.x;
    y = rhs.y;
    return *this;
  }

public:
  inline bool operator==(const Vec2& rhs) const
  {
    return ((x == rhs.x) && (y == rhs.y));
  }

  inline bool operator!=(const Vec2& rhs) const
  {
    return !(operator==(rhs));
  }

  inline Vec2 operator+ (const Vec2& rhs) const
  {
    return Vec2(x + rhs.x, y + rhs.y);
  }

  inline Vec2 operator- (const Vec2& rhs) const
  {
    return Vec2(x - rhs.x, y - rhs.y);
  }

  inline Vec2 operator* (T rhs) const
  {
    return Vec2(T(x * rhs), T(y * rhs));
  }

  inline Vec2 operator/ (T rhs) const
  {
    return Vec2(T(x / rhs), T(y / rhs));
  }

  inline Vec2 operator- () const
  {
    return Vec2(-x, -y);
  }

  inline Vec2& operator+= (const Vec2& rhs)
  {
    x += rhs.x;
    y += rhs.y;
    return *this;
  }

  inline Vec2& operator-= (const Vec2& rhs)
  {
    x -= rhs.x;
    y -= rhs.y;
    return *this;
  }

  inline Vec2& operator*= (T rhs)
  {
    x = T(x * rhs);
    y = T(y * rhs);
    return *this;
  }

  inline Vec2& operator/= (T rhs)
  {
    x = T(x / rhs);
    y = T(y / rhs);
    return *this;
  }

public:
  inline double norm() const
  {
    return sqrt(squaredNorm());
  }

  inline T squaredNorm() const
  {
    return ((x * x) + (y * y));
  }

  inline double length() const 
  {
    return norm();
  }

  inline double length(const Vec2& pos) const
  {
    return sqrt(squaredLength(pos));
  }

  inline T squaredLength() const 
  {
    return squaredNorm();
  }

  inline T squaredLength(const Vec2& pos) const
  {
    return (((x - pos.x) * (x - pos.x)) + ((y - pos.y) * (y - pos.y)));
  }
  
  inline T l1length() const {
    return abs(x) + abs(y);
  }

  inline T l1length(const Vec2& pos) const {
    return abs(x - pos.x) + abs(y - pos.x);
  }

  inline void normalize()
  {
    double l = norm();
    if (l < numeric_limits<double>::epsilon()) {
      x = 0;
      y = 0;
    }
    else {
      x = (T)(x / l);
      y = (T)(y / l);
    }
  }

  inline Vec2 normalized() const
  {
    Vec2 n(*this);
    n.normalize();
    return n;
  }

  inline T dot(const Vec2& rhs) const
  {
    return x * rhs.x + y * rhs.y;
  }

  inline T cross(const Vec2& rhs) const
  {
    return x * rhs.y - y * rhs.x;
  }

  inline double angle(const Vec2& rhs) const
  {
    double sqlen = squaredLength();
    double sqlen2 = rhs.squaredLength();

    if (sqlen == 0.0 || sqlen2 == 0.0) {
      return 0.0;
    }

    double val = dot(rhs) / sqrt(sqlen) / sqrt(sqlen2);
    val = std::max(-1.0, min(val, 1.0));
    return acos(val);
  }

public:
  static const Vec2& xAxis() { static Vec2 vec(1, 0); return vec; }
  static const Vec2& yAxis() { static Vec2 vec(0, 1); return vec; }
  static const Vec2& zero() { static Vec2 vec(0, 0); return vec; }
  friend ostream& operator<< (ostream& ostr, const Vec2& rhs) {
    ostr << setprecision(15) << rhs.x << " " << rhs.y;
    return ostr;
  }

  friend istream& operator>> (istream& istr, Vec2& rhs) {
    istr >> rhs.x >> rhs.y;
    return istr;
  }

  friend bool operator< (const Vec2& lhs, const Vec2& rhs) {
    return lhs.x != rhs.x ? lhs.x < rhs.x : lhs.y < rhs.y;
  }

public:
  Vec2() : x(T(0)), y(T(0)) {}

  Vec2(T x_, T y_) : x(x_), y(y_) {}

  Vec2(const Vec2& rhs) : x(rhs.x), y(rhs.y) {}

  ~Vec2() {}

public:
  // To find orientation of ordered triplet (p, q, r). 
  // The function returns following values 
  // 0 --> p, q and r are colinear 
  // +1 --> Clockwise 
  // -1 --> Counterclockwise 
  static int orientation(const Vec2& p, const Vec2& q, const Vec2& r)
  {
    T a = (q.y - p.y) * (r.x - q.x);
    T b = (q.x - p.x) * (r.y - q.y);
    if (a == b) return 0;
    return a > b ? 1 : -1;
  }

  // Given three colinear points p, q, r, the function checks if 
  // point q lies on line segment 'pr' 
  static bool onSegment(const Vec2 p, const Vec2 q, const Vec2 r)
  {
    return q.x <= max(p.x, r.x) 
      && q.x >= min(p.x, r.x) 
      && q.y <= max(p.y, r.y) 
      && q.y >= min(p.y, r.y);
  }
};

class Seg2
{
public:
  Vec2 start;
  Vec2 end;

public:
  Vec2 center() const { return (start + end) / 2;}

  Vec2 direction() const { return end - start; }

  Vec2 normalizedDirection() const { return direction().normalized(); }

  double length() const { return (end - start).length(); }

public:
  bool contains(const Vec2& point) const {
    static constexpr double epsilon = 1e-10;
    return Vec2::onSegment(start, point, end) && 
      (start - point).cross(point - end) < epsilon;
  }

  bool contains(const Seg2& rhs) const {
    return contains(rhs.start) && contains(rhs.end);
  }

  bool intersects(const Seg2& rhs) const {
    const auto& p1 = this->start;
    const auto& q1 = this->end;
    const auto& p2 = rhs.start;
    const auto& q2 = rhs.end;

    int o1 = Vec2::orientation(p1, q1, p2); 
    int o2 = Vec2::orientation(p1, q1, q2); 
    int o3 = Vec2::orientation(p2, q2, p1); 
    int o4 = Vec2::orientation(p2, q2, q1); 

    if (o1 * o2 < 0 && o3 * o4 < 0) 
      return true; 

    if (o1 == 0 && Vec2::onSegment(p1, p2, q1)) return true; 
    if (o2 == 0 && Vec2::onSegment(p1, q2, q1)) return true; 
    if (o3 == 0 && Vec2::onSegment(p2, p1, q2)) return true; 
    if (o4 == 0 && Vec2::onSegment(p2, q1, q2)) return true; 
    return false;
  }

  bool colinear(const Seg2& rhs) const {
    // https://stackoverflow.com/a/565282
    const auto& p = this->start;
    const auto r = this->end - this->start;
    const auto& q = rhs.start;
    const auto s = rhs.end - rhs.start;

    auto a = r.cross(s);
    auto b = (q - p).cross(r);
    return a == 0 && b == 0;
  }
  
  Vec2 intersection(const Seg2& rhs) const {
    // https://stackoverflow.com/a/565282
    const auto& p = this->start;
    const auto r = this->end - this->start;
    const auto& q = rhs.start;
    const auto s = rhs.end - rhs.start;

    auto a = r.cross(s);
    auto b = (q - p).cross(r);
    if (a == 0 && b == 0) {
      // case1: colinear
      if (this->contains(rhs.start)) {
        return rhs.start;
      }
      else {
        return rhs.end;
      }
    } else if (a == 0 && b != 0) {
      // case2: parallel
      throw runtime_error("case 2. should be checked using intersects() before");
    }
    double t = (double)(q - p).cross(s) / (double)a;
    double u = (double)(q - p).cross(r) / (double)a;
    if (0 <= t && t <= 1.0 && 0 <= u && u <= 1.0) {
      // case3: intersects
      return p + r * t;
    }
    else {
      // case 4: not parallel but do not intersects
      throw runtime_error("case 4. should be checked using intersects() before");
    }
  }

public:
  friend ostream& operator<< (ostream& ostr, const Seg2& rhs) {
    ostr << "Seg2(" << rhs.start << ", " << rhs.end << ")";
    return ostr;
  }

  friend istream& operator>> (istream& istr, Seg2& rhs) {
    istr >> rhs.start >> rhs.end;
    return istr;
  }
  

public:
  Seg2() {};

  Seg2(const Vec2& start, const Vec2& end) 
    : start(start), end(end) {};

  Seg2(Vec2::T startX, Vec2::T startY, Vec2::T endX, Vec2::T endY) 
    : start{startX, startY}, end{endX, endY} {};

  Seg2(const Seg2& rhs) 
    : start(rhs.start), end(rhs.end) {};

public:
  ~Seg2() {}
};

class BipartiteMatching {
 public:
  const vector<vector<int>>& edges_;
  size_t nDst_;
  vector<int> matches_;
  vector<bool> visited_;

 public:
  BipartiteMatching(const vector<vector<int>>& edges, int nDst = -1)
      : edges_(edges), nDst_(nDst) {
    if (nDst == -1) {
      nDst_ = 0;
      for (int i = 0; i < edges.size(); ++i) {
        for (int w : edges[i]) {
          nDst_ = max(nDst_, (size_t)(w+1));
        }
      }
    }
    matches_.resize(nDst_, -1);
    visited_.resize(nDst_, false);
  }

  size_t solve(int k) {
    size_t res = 0;
    for (size_t i = 0; i < edges_.size(); ++i) {
      for (int j = 0; j < k; ++j) {
        fill(all(visited_), false);
        res += dfs(i);
      }
    }
    return res;
  }

  std::vector<std::pair<int, int>> matches() const {
    std::vector<std::pair<int, int>> res;
    for (size_t dst = 0; dst < matches_.size(); ++dst) {
      const auto& src = matches_[dst];
      if (src != -1) {
        res.push_back({src, dst});
      }
    }
    return res;
  }

 private:
  bool dfs(int src) {
    for (int dst : edges_[src]) {
      if (visited_[dst]) {
        continue;
      }
      visited_[dst] = true;
      if (matches_[dst] == -1 || dfs(matches_[dst])) {
        matches_[dst] = src;
        return true;
      }
    }
    return false;
  }
};

int main() {
  int n, k, h, m;
  scanf("%d %d %d %d", &n, &k, &h, &m);

  vector<Vec2> corners(n);
  for (int i = 0; i < n; ++i) {
    cin >> corners[i];
  }
  
  vector<Seg2> wallSegs;
  wallSegs.reserve(n);
  for (int i = 0; i < n; ++i) {
    wallSegs.push_back({corners[i], corners[(i+1)%n]});
  }

  vector<Vec2> holes(h);
  for (int i = 0; i < h; ++i) {
    cin >> holes[i];
  }

  vector<Vec2> mice(m);
  for (int i = 0; i < m; ++i) {
    cin >> mice[i];
  }
  
  vector<vector<int>> graph(h);
  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < m; ++j) {
      const auto& hole = holes[i];
      const auto& mouse = mice[j];
      Seg2 hmSeg(hole, mouse);
      bool ok = true;
      for (const auto& wallSeg : wallSegs) {
        if (Vec2::orientation(wallSeg.start, hole, wallSeg.end) == 0) continue;
        if (Vec2::orientation(wallSeg.start, wallSeg.end, hole) * Vec2::orientation(wallSeg.start, wallSeg.end, mouse) > 0) continue;
        if (Vec2::orientation(hole, mouse, wallSeg.start) * Vec2::orientation(hole, mouse, wallSeg.end) > 0) continue;
        ok = false;
        break;
      }
      if (ok) {
        graph[i].push_back(j);
      }
    }
  }
  
  BipartiteMatching bm(graph);
  if (bm.solve(k) == m) {
    printf("Possible\n");
  }
  else {
    printf("Impossible\n");
  }

  return 0;
}
