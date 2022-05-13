#include <bits/stdc++.h>
using namespace std;

struct UnionFindSet {
  UnionFindSet(int size) : root_(size), rank_(size, 0), size_(size, 1) {
    for (int i = 0; i < size; ++i) {
      root_[i] = i;
    }
  }

  int find(int i) {
    if (root_[i] == i) {
      return i;
    }
    int root = find(root_[i]);
    root_[i] = root;
    return root;
  }

  int merge(int i, int j) {
    int i_root = find(i);
    int j_root = find(j);
    if (i_root == j_root) {
      return size_[i_root];
    }
    if (rank_[i_root] < rank_[j_root]) {
      root_[i_root] = j_root;
      size_[j_root] += size_[i_root];
      size_[i_root] = 0;
      return size_[j_root];
    }
    root_[j_root] = i_root;
    size_[i_root] += size_[j_root];
    size_[j_root] = 0;
    if (rank_[i_root] == rank_[j_root]) {
      rank_[i_root]++;
    }
    return size_[i_root];
  }

  bool resize(size_t size) {
    size_t size_before = root_.size();

    if (size_before >= size) {
      return false;
    }
    root_.resize(size);
    rank_.resize(size, 0);
    size_.resize(size, 1);
    for (int i = size_before; i < size; ++i) {
      root_[i] = i;
    }
    return true;
  }

  size_t size() const { return root_.size(); }

  vector<int> root_;
  vector<int> rank_;
  vector<int> size_;
};

struct Edge {
  int u;
  int v;
  double w; /* cost */

  friend bool operator<(const Edge& lhs, const Edge& rhs) {
    return lhs.w > rhs.w;
  }
};

class Point2 {
  using T = double;

 public:
  T x;
  T y;

 public:
  inline Point2& operator=(const Point2& rhs) {
    x = rhs.x;
    y = rhs.y;
    return *this;
  }

 public:
  inline bool operator==(const Point2& rhs) const {
    return ((x == rhs.x) && (y == rhs.y));
  }

  inline bool operator!=(const Point2& rhs) const { return !(operator==(rhs)); }

  inline Point2 operator+(const Point2& rhs) const {
    return Point2(x + rhs.x, y + rhs.y);
  }

  inline Point2 operator-(const Point2& rhs) const {
    return Point2(x - rhs.x, y - rhs.y);
  }

  inline Point2 operator*(T rhs) const {
    return Point2(T(x * rhs), T(y * rhs));
  }

  inline Point2 operator/(T rhs) const {
    return Point2(T(x / rhs), T(y / rhs));
  }

  inline Point2 operator-() const { return Point2(-x, -y); }

  inline Point2& operator+=(const Point2& rhs) {
    x += rhs.x;
    y += rhs.y;
    return *this;
  }

  inline Point2& operator-=(const Point2& rhs) {
    x -= rhs.x;
    y -= rhs.y;
    return *this;
  }

  inline Point2& operator*=(T rhs) {
    x = T(x * rhs);
    y = T(y * rhs);
    return *this;
  }

  inline Point2& operator/=(T rhs) {
    x = T(x / rhs);
    y = T(y / rhs);
    return *this;
  }

 public:
  inline double norm() const { return sqrt(squaredNorm()); }

  inline double squaredNorm() const { return ((x * x) + (y * y)); }

  inline double length(const Point2& pos) const {
    return sqrt(squaredLength(pos));
  }

  inline double squaredLength(const Point2& pos) const {
    return (((x - pos.x) * (x - pos.x)) + ((y - pos.y) * (y - pos.y)));
  }

  inline void normalize() {
    double l = norm();
    if (l < numeric_limits<double>::epsilon()) {
      x = 0;
      y = 0;
    } else {
      x = (T)(x / l);
      y = (T)(y / l);
    }
  }

  inline Point2 normalized() const {
    Point2 n(*this);
    n.normalize();
    return n;
  }

 public:
  static const Point2& xAxis() {
    static Point2 vec(1, 0);
    return vec;
  }
  static const Point2& yAxis() {
    static Point2 vec(0, 1);
    return vec;
  }
  static const Point2& zero() {
    static Point2 vec(0, 0);
    return vec;
  }
  friend ostream& operator<<(ostream& ostr, const Point2& rhs) {
    ostr << "Point2[" << rhs.x << ", " << rhs.y << "]";
    return ostr;
  }

  friend istream& operator>>(istream& istr, Point2& rhs) {
    istr >> rhs.x >> rhs.y;
    return istr;
  }

 public:
  Point2() : x(T(0)), y(T(0)) {}

  Point2(T x_, T y_) : x(x_), y(y_) {}

  Point2(const Point2& rhs) : x(rhs.x), y(rhs.y) {}

  ~Point2() {}
};

int main() {
  int N;
  scanf("%d", &N);

  vector<Point2> points(N);
  for (int i = 0; i < N; ++i) {
    cin >> points[i];
  }

  priority_queue<Edge> edges;
  for (int i = 0; i < N - 1; ++i) {
    for (int j = i + 1; j < N; ++j) {
      double len = points[i].length(points[j]);
      edges.push({i, j, len});
    }
  }

  double ans = 0;
  UnionFindSet ufs(N);
  while (!edges.empty()) {
    auto [u, v, w] = edges.top();
    edges.pop();

    if (ufs.find(u) == ufs.find(v)) {
      continue;
    }
    ufs.merge(u, v);
    ans += w;
  }

  printf("%lf\n", ans);

  return 0;
}
