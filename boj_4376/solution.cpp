#include <bits/stdc++.h>
using namespace std;

class Vec2
{
public:
  using T = double;

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
    // https://www.geeksforgeeks.org/orientation-3-ordered-points/
    T val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0) {
      return 0;
    }
    return val > 0 ? 1 : -1;
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

class BipartiteMatching {
 public:
  const vector<vector<int>>& graph_;
  size_t nDst_;
  vector<int> matches_;

 public:
  BipartiteMatching(const vector<vector<int>>& graph, size_t nDst = 0)
      : graph_(graph), nDst_(nDst), matches_() {
    if (nDst_ == 0) {
      nDst_ = 0;
      for (size_t i = 0; i < graph.size(); ++i) {
        for (size_t w : graph[i]) {
          nDst_ = max(nDst_, (size_t)(w + 1));
        }
      }
    }
    matches_.resize(nDst_, -1);
  }

  size_t solve() {
    size_t res = 0;
    for (size_t i = 0; i < graph_.size(); ++i) {
      vector<bool> visited(nDst_, false);
      res += dfs(i, visited);
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
  bool dfs(int src, vector<bool>& visited) {
    for (int dst : graph_[src]) {
      if (visited[dst]) {
        continue;
      }
      visited[dst] = true;
      if (matches_[dst] == -1 || dfs(matches_[dst], visited)) {
        matches_[dst] = src;
        return true;
      }
    }
    return false;
  }
};

bool solve() {
  int N, M;
  double S, V;
  if (!(cin >> N)) {
    return false;
  }
  cin >> M >> S >> V;

  double SSVV = S * S * V * V;

  vector<Vec2> mice(N);
  for (int i = 0; i < N; ++i) {
    cin >> mice[i];
  }

  vector<Vec2> holes(M);
  for (int i = 0; i < M; ++i) {
    cin >> holes[i];
  }

  vector<vector<int>> graph(N);
  for (int i = 0; i < N; ++i) {
    const auto& m = mice[i];
    for (int j = 0; j < M; ++j) {
      const auto& h = holes[j];
      const double sqDistance = m.squaredLength(h);
      // D / V <= S <=> D <= S * V <=> D * D <= S * S * V * V
      if (sqDistance <= SSVV) {
        graph[i].push_back(j);
      }
    }
  }

  BipartiteMatching bm(graph, M+1);
  int ans = N - bm.solve();
  printf("%d\n", ans);
  
  return true;
}

int main() {
  
  while (solve()) {
  }

  return 0;
}
